#include "mythread.h"
#include <QVector>
#include <QCoreApplication>

bool MyThread::passwordFound = false;

MyThread::MyThread(QString charset, QString salt, QString hash, unsigned int charsetIndex,
                   unsigned int nbChars, long long unsigned int nbToCompute, QObject *parent) :
    QThread(parent) {
    this->charset = charset;
    this->salt = salt;
    this->hash = hash;

    this->charsetIndex = charsetIndex;
    this->nbChars = nbChars;
    this->nbToCompute = nbToCompute;
}

MyThread::~MyThread() {
}

void MyThread::run() {

    unsigned long long int nbComputed = 0;
    unsigned int i;
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

    nbValidChars = unsigned(charset.length());


    currentPasswordString.fill(charset.at(int(charsetIndex)),int(nbChars));
    currentPasswordArray.fill(charsetIndex, int(nbChars));


    while (nbComputed < nbToCompute && !passwordFound) {

        if(this->passwordFound){
            return;
        }
        /* On vide les données déjà ajoutées au générateur */
        md5.reset();
        /* On préfixe le mot de passe avec le sel */
        md5.addData(salt.toLatin1());
        md5.addData(currentPasswordString.toLatin1());
        /* On calcul le hash */
        currentHash = md5.result().toHex();

        /*
         * Si on a trouvé, on retourne le mot de passe courant (sans le sel)
         */
        if (currentHash == hash){
            emit passwordComputed(currentPasswordString);
            passwordFound = true;
        }

        /*
         * Tous les 1000 hash calculés, on notifie qui veut bien entendre
         * de l'état de notre avancement (pour la barre de progression)
         */
        if (!(nbComputed % 1000)){
            emit incrementPercentComputed(double(1000.0)/nbToCompute);
        }


        /*
         * On récupère le mot de passe à tester suivant.
         *
         * L'opération se résume à incrémenter currentPasswordArray comme si
         * chaque élément de ce vecteur représentait un digit d'un nombre en
         * base nbValidChars.
         *
         * Le digit de poids faible étant en position 0
         */
        i = 0;

        while (i < unsigned(currentPasswordArray.size())) {
            currentPasswordArray[int(i)]++;

            if (currentPasswordArray[int(i)] >= nbValidChars) {
                currentPasswordArray[int(i)] = 0;
                i++;
            } else
                break;
        }

        /*
         * On traduit les index présents dans currentPasswordArray en
         * caractères
         */
        for (i=0;i<nbChars;i++)
            currentPasswordString[int(i)]  = charset.at(int(currentPasswordArray.at(int(i))));

        nbComputed++;
    }
}

void MyThread::passwordIsFound(bool passwordFound) {
    MyThread::passwordFound = passwordFound;
}
