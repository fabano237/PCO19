/**
  \file mythread.h
  \author Yann Thoma
  \date 07.02.2017
  \brief Classe pour la mise en évidence du problème de concurrence.


  Ce fichier contient la définition de la classe MyThread, qui permet de
  mettre en avant le problème d'accès concurrent à une variable partagée.
*/


#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

/**
 * \brief The MyThread class
 *
 * Cette classe est un thread qui lance une boucle incrémentant un compteur.
 * Celui-ci est partagé par l'ensemble des threads de la classe et doit
 * être protégé.
 */
class MyThread : public QThread
{
    Q_OBJECT
public:
    /**
     * \brief MyThread Constructeur simple
     * \param paramNbIterations Nombre d'itérations à effectuer
     * \param threadName Nom du thread. Utile pour le debug
     * \param parent Objet parent du thread
     */
    explicit MyThread(long unsigned int paramNbIterations,const QString &threadName, QObject *parent = 0);

    //! Compteur partagé par l'ensemble des threads
    static long unsigned int counter;

    /**
     * @brief initialize Méthode statique appelée avant le lancement des threads
     * @param nbThreads Nombre de threads qui seront créés
     * Cette méthode est appelée avant que les différents threads ne soient créés.
     * Elle modifie la valeur de nbThreads, mais pourrait être modifiée pour y
     * placer d'autres éléments.
     */
    static void initialize(unsigned int nbThreads);

signals:
    
public slots:

protected:

    /**
     * \brief run Méthode lancée par le thread
     */
    void run() Q_DECL_OVERRIDE;

private:

    //! nbIterations Nombre d'itérations que le thread doit effectuer
    long unsigned int nbIterations;

    //! nbThreads Nombre de threads, utilisé en lecture seule par les threads
    static unsigned int nbThreads;

};

#endif // MYTHREAD_H
