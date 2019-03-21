
# Cracking md5

**Auteurs:** Fabrice Mbassi, Aurélien Siu

## Description des fonctionnalités du logiciel

Le but de ce logiciel est de cracker le mot de passe chiffré à l'aide de hashs MD5.
Ce procédé est réalisé en hashant chaque possibilité de mot de passe.

L'objectif de ce laboratoire est de multithreadé ce programme afin d'accélérer le calcul.

## Choix d'implémentation

La première étape a consisté à déplacer la boucle de calcul de la classe ThreadManager dans la méthode `run()` de la classe `MyThread`
Il a ensuite fallut déterminer les paramètres à transmettre à nos threads afin que chacun d'eux se partagent le calcul.

Voici donc le constructeur obtenu:

```
MyThread::MyThread(QString charset, QString salt, QString hash, unsigned int charsetIndex,
                   unsigned int nbChars, long long unsigned int nbToCompute, QObject *parent)
```

Les quatres premiers paramètres que nous sont directement donnés par l'entrée utilisateur.

Les paramètres à définir pour chaque thread sont les suivants:

- `charsetIndex`: index du tableau de caractères à partir du quel commence le calcul de chaque thread.
Il est calculé en divisant la taille du charset par le nombre de threads lancés. nbValidChar vaut dans ce laboratoire 67.
`charsetIndexScale = nbValidChars / nbThreads`

	- Pour mieux comprendre voici un exemple avec 2 threads et un nombre de caractères à trouver égal à 4 :
	
		le premier thread démarre à l'index 0. Il va donc démarrer le calcul à partir de la chaine de caractères "aaaa"
	le deuxième thread va démarrer à l'index `nbValidChar` / 2, soit 33. Il démarrera donc avec la chaine de caractère "HHHH".
	
-  `nbToCompute`:  nombre de hashs à calculer pour chaque threads.
Il est calculé en divisant le nombre de hashs total à calculé par le nombre de threads lancés: 
`nbToComputePerThread = nbToComputeTotal / nbThreads;`

Maintenant que nos threads sont définis, il nous faut un moyen de communication entre nos threads et le ThreadManager.

En effet, le premier thread ayant trouvé le bon mot de passe de notifier le `ThreadManager`.
Cette communication est réalisée au moyen de signaux et de slots. (`Signals` et `Slots`)

Le signal permettant de notifier tout thread étant connecté à ce signal au moyen d'un slot servant à réceptionner l'information.

Nous avons donc le signal `passwordComputed` est émis lorsque le mot de passe a été trouvé. Il arrive dans un slot qui va mettre à jour le mot de passe à renvoyer. Cette affectation du mot de passe est protégée par un sémaphore permettant de s'assurer que le mot de passe a bien été affecté à la variable `passwordFoundStr`.

Après avoir émis ce signal, le thread ayant trouvé le bon mot de passe met à jour le booléan `passwordFound` à true afin de stopper tous les autres threads worker concurrents.

En ce qui concerne la barre de progression, le même signal `incrementPercentComputed` est envoyer depuis MyThread vers le ThreadManager.  A ce moment là, la progression donnée est divisée par le nombre de threads afin d'obtenir la progression globale des threads. Cette valeur est renvoyée à travers un signal à la MainWindows afin que la barre de progression soit mise à jour.



## Tests effectués


