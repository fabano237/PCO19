#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QCryptographicHash>
#include <QSemaphore>

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread(QString charset, QString salt, QString hash, unsigned int charsetIndex,
             unsigned int nbChars, long long unsigned int nbToCompute , QObject *parent = 0);
    ~MyThread();

protected:
    void run();

private:
    QString charset;
    QString salt;
    QString hash;

    unsigned int charsetIndex;
    unsigned int nbChars;
    unsigned long long int nbToCompute;

    static bool passwordFound;

public:

signals:
    /**
     * \brief incrementPercentComputed fonction qui indique que le pourcentage
     * de test effectué pour casser le hash md5.
     * \param percentComputed double pourcentage de tests effectués pour
     * reverser le hash md5
     */
    void incrementPercentComputed(double percentComputed);

    /**
     * \brief run Méthode qui incrémente la barre de progression affichée dans
     * l'interface. Cette barre de progression est partagée entre tous les
     * threads.
     */
    void passwordComputed(QString password);

public slots:
    /**
     * \brief passwordFound fonction qui indique à MyThread
     *  que le mot de passe a été trouvé. Stoppe l'execution du thread
     */
    void passwordIsFound(bool password);

};

#endif // MYTHREAD_H
