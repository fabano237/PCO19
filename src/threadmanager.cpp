#include <QCryptographicHash>
#include <QVector>
#include <QCoreApplication>
#include <QDebug>

#include "mythread.h"
#include "threadmanager.h"

#ifndef QT_NO_DEBUG
#define CHECK_TRUE(instruction) Q_ASSERT(instruction)
#else
#define CHECK_TRUE(instruction) (instruction)
#endif

QSemaphore* ThreadManager::passwordUpdate = new QSemaphore(0);

/*
 * std::pow pour les long long unsigned int
 */
long long unsigned int intPow (
        long long unsigned int number,
        long long unsigned int index)
{
    long long unsigned int i;

    if (index == 0)
        return 1;

    long long unsigned int num = number;

    for (i = 1; i < index; i++)
        number *= num;

    return number;
}

ThreadManager::ThreadManager(QObject *parent) :
    QObject(parent)
{}
/*
 * Les paramètres sont les suivants:
 *
 * - charset:   QString contenant tous les caractères possibles du mot de passe
 * - salt:      le sel à concaténer au début du mot de passe avant de le hasher
 * - hash:      le hash dont on doit retrouver la préimage
 * - nbChars:   le nombre de caractères du mot de passe à bruteforcer
 * - nbThreads: le nombre de threads à lancer
 *
 * Cette fonction doit retourner le mot de passe correspondant au hash, ou une
 * chaine vide si non trouvé.
 */
QString ThreadManager::startHacking(
        QString charset,
        QString salt,
        QString hash,
        unsigned int nbChars,
        unsigned int nbThreads
        )
{
    this->nbThreads = nbThreads;
    long long unsigned int nbToCompute;

    /*
     * Nombre de caractères différents pouvant composer le mot de passe
     */
    unsigned int nbValidChars;

    /*
     * Mot de passe à tester courant
     */
    QString currentPasswordString;

    /*
     * Tableau contenant les index dans la chaine charset des caractères de
     * currentPasswordString
     */
    QVector<unsigned int> currentPasswordArray;

    /*
     * Hash du mot de passe à tester courant
     */
    QString currentHash;

    /*
     * Object QCryptographicHash servant à générer des md5
     */
    QCryptographicHash md5(QCryptographicHash::Md5);

    /*
     * Calcul du nombre de hash à générer
     */
    nbToCompute     = intPow((unsigned long long int)charset.length(),(unsigned long long int)nbChars);

    /*
     * Nombre de caractères différents pouvant composer le mot de passe
     */
    nbValidChars    = unsigned(charset.length());

    /*
     * On initialise le premier mot de passe à tester courant en le remplissant
     * de nbChars fois du premier caractère de charset
     */
    currentPasswordString.fill(charset.at(0), int(nbChars));
    currentPasswordArray.fill(0, int(nbChars));

    QVector<MyThread*> threads = QVector<MyThread*>(int(nbThreads));

    unsigned long long int nbToComputePerThread = nbToCompute / nbThreads;

    unsigned int charsetIndexScale = nbValidChars / nbThreads;
    for(unsigned int i = 0; i < nbThreads; ++i) {

        // create a new worker thread
        threads[int(i)] = new MyThread(charset, salt, hash, charsetIndexScale * i, nbChars, nbToComputePerThread);

        CHECK_TRUE(connect(
                       threads[int(i)],
                   SIGNAL(passwordComputed(QString)),
                   this,
                   SLOT(passwordComputed(QString))));

        CHECK_TRUE(
                    connect(
                        this,
                        SIGNAL(passwordIsFound(bool)),
                        threads[int(i)],
                    SLOT(passwordIsFound(bool))
                    )
                );
        CHECK_TRUE(
                    connect(
                        threads[int(i)],
                    SIGNAL(incrementPercentComputed(double)),
                    this,
                    SLOT(incrementPercentComputedSlot(double))
                    )
                );
        if(!i){
            emit passwordIsFound(false);
        }
        threads[int(i)]->start();
    }

    for(unsigned int i = 0; i < nbThreads; ++i){
        threads[int(i)]->wait();
    }
    /*
     * Si on arrive ici, cela signifie que tous les mot de passe possibles ont
     * été testés, et qu'aucun n'est la préimage de ce hash.
     */

    passwordUpdate->acquire();

    return passwordFoundStr;
}

void ThreadManager::passwordComputed(QString password)
{
    passwordFound = true;
    passwordFoundStr = password;
    passwordUpdate->release();
}

void ThreadManager::incrementPercentComputedSlot(double percentComputed)
{
    emit incrementPercentComputed(percentComputed / nbThreads);
}


