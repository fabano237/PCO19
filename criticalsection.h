#ifndef CRITICALSECTION_H
#define CRITICALSECTION_H

class CriticalSection
{
public:
    /**
     * @brief Méthode initialisant la section critique
     * @param nbThreads Le nombre de threads maximal géré par la section critique
     * Cette méthode doit être appelée avant l’utilisation de la section critique
     */
    void initialize(unsigned int nbThreads);

    /**
     * @brief Protocole d’entrée dans la section critique
     * @param index Indice de la tâche appelante
     */
    void lock(unsigned int index);

    /**
     * @brief Protocole de sortie de la section critique
     * @param index Indice de la tâche appelante
     */
    void unlock(unsigned int index);
};

#endif // CRITICALSECTION_H
