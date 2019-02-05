#include "mythread.h"

#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    /* Un click sur le bouton start appelera notre méthode startThreads */
    connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startThreads()));
}

void Dialog::startThreads()
{
    long unsigned int i     = 0;

    MyThread *currentThread;

    MyThread::counter      = 0;

    /* Récupère les paramètres */
    long unsigned int nbIterations   = ui->editNbIterations->text().toLong();
    long unsigned int nbThreads      = ui->editNbThreads->text().toLong();

    /* Désactive temporairement le bouton */
    ui->startButton->setEnabled(false);

    /* Affiche une barre de progression animée */
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(0);

    /* Met à jour les champs de texte avec les nombres parsés (un zéro
     * indiquera une erreur). On passe par une QSting pour pouvoir afficher
     * des long */
    ui->editNbIterations->setText(QString::number(nbIterations));
    ui->editNbThreads->setText(QString::number(nbThreads));

    if (nbIterations && nbThreads)
    {
        /* Affiche le résultat escompté */
        ui->lcdNumberResEspere->display(
                    QString::number(nbIterations*nbThreads));

        /* Créé les threads, on ajoutant leur pointeur à la liste.
         * Un appel à la méthode start() apellera la méthode run() de la classe
         * MyThread */
        for (i=0; i<nbThreads; i++)
        {
            currentThread = new MyThread(nbIterations, QString("PCOThread %1").arg(i));
            threadList.append(currentThread);
            currentThread->start();
        }

        /* Attends la fin de chaque thread et libère la mémoire associée.
         * Durant l'attente, l'application est bloquée.
         */
        for (i=0; i<nbThreads; i++)
        {
            currentThread = threadList.at(i);
            currentThread->wait();
            delete currentThread;
        }
        /* Vide la liste de pointeurs de threads */
        threadList.clear();

        /* Affiche le résultat obtenu (on passe par une QSting pour pouvoir
         * afficher des long) */
        ui->lcdNumberResObtenu->display(QString::number(MyThread::counter));
        ui->lcdNumberResRatio->display(QString::number(
                            MyThread::counter * 100 / nbIterations/nbThreads));
    }

    /* Affiche une barre de progression complète */
    ui->progressBar->setMaximum(1);
    ui->progressBar->setValue(1);

    /* Réactive le bouton start */
    ui->startButton->setEnabled(true);
}


Dialog::~Dialog()
{
    delete ui;
}
