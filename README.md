# SI5_langage_c
I.INTRODUCTION

Ce projet consiste à développer un malware permettant d’extraire les données (identifiants et mot de passe) d’une machine et de cacher un fichier sur le système et à implémenter un outil commande et contrôle (C2) multi-thread. Le malware détournera les fonctions légitimes du système en ajoutant des taches souhaitées.

II.FONCTIONNALITES
1.Les différents types de threads
Un thread appelé aussi processus léger ou activité est un fil d'instructions à l'intérieur d'un processus. Contrairement aux processus, les threads d’un même processus partagent le même espace d’adressage, le même environnement (par exemple les mêmes variables d’environnement, des mêmes données...). Les programmes qui utilisent plusieurs threads sont dits multithreads.
Le thread principal crée des types différents de threads pour une session :
a.Thread de mappage
Le thread de mappage extrait les informations de session et de mappage, compile le mappage, et effectue le nettoyage après l'exécution de la session.
b.Threads pré-session et post-session
Les threads pré-session et post-session sont créés pour effectuer les opérations correspondantes.
c.Threads de lecture
Les threads de lecture permettent d’extraire des données sources.
d.Threads de transformation
Les threads de transformation traitent les données selon la logique de transformation dans le mappage.
e.Threads d’écriture
Les threads d'écriture permettent de charger des données cibles.

2.Ordre de la mémoire
L'ordre de la mémoire est l'ordre des accès à la mémoire de l'ordinateur par l'unité centrale. Il dépend à la fois de l'ordre des instructions générées par le compilateur au moment de la compilation et de l'ordre d'exécution du CPU au moment de l'exécution. Cependant, il est peu important en dehors du multithreading et des E/S en mémoire, car si le compilateur ou le CPU modifie l'ordre des opérations, il doit nécessairement s'assurer que le réordonnancement ne modifie pas la sortie du code ordinaire à un seul thread.
En C, memory_order est utilisé comme argument dans les fonctions qui requièrent des opérations atomiques. Il spécifie comment les opérations sur des threads distincts sont synchronisées. Le compilateur ou l'unité centrale peuvent réorganiser l'accès à la mémoire. Ils peuvent exécuter dans des ordres différents lorsqu'un thread distinct tente de communiquer, et observer une hiérarchie d'accès à la mémoire qui rompt les invariants du code.
Pour y remédier, memory_order spécifie les types de réorganisation qu'un compilateur doit interdire. Les opérations de memory_order en C sont spécifiées par l’inclusion de la bibliothèque intégrée <stdatomic.h> dans le fichier de code.

3.LD_PRELOAD et liens dynamiques
a.LD_PRELOAD
LD_PRELOAD est une variable d’environnement qui nous permet de spécifier une bibliothèque partagée qui sera chargée au démarrage d’un programme.
Lorsque cette variable est définie, l’éditeur de liens chargera cette bibliothèque avant toutes les autres. Ce qui permet de modifier des fonctions qui appartiennent normalement à la librairie C (libc.so).
b.Liens dynamiques
Le lien dynamique est la partie du système d'exploitation qui charge et lie les bibliothèques partagées nécessaires à un programme à l'exécution, en copiant le contenu des bibliothèques vers la RAM, en remplissant les tables de saut et en relocalisant les pointeurs.
Le système d'exploitation et le format de l'exécutable déterminent le fonctionnement et la mise en œuvre des liens dynamiques.


III.Mise en œuvre du malware
1.Port Knocking
Le port knocking est une méthode permettant de lancer des commandes ou programmes sur une machine cible en temps réel grâce au lancement préalable d'une suite de connexions sur des ports distincts dans le bon ordre.
Je vais détourner la fonction rand pour installer et configurer le port knocking sur la machine cible pour me permettre d’ouverture et de fermer le port SSH à distance.
L’installation des packages nécessite les droits sudo/root sur la cible.



La configuration par défaut du port knocking permet l’ouverture et la fermeture du port SSH (22) à distance. 



Je crée ensuite un programme permettant d’appeler la fonction rand et afficher cinq valeurs aléatoires.


2.Compilation des programmes et passage en variable d’environnement LD_PRELOAD
a.Pour compiler les programmes, il faut installer le compilateur GCC

b.Le compilateur GCC que j’ai installé est la version 13.3.0

c.Ci-dessous les commandes pour compiler ma fonction rand en librairie et mon programme nb_rand

d.Le résultat du lancement de nb_rand sans la librairie rand détourner :

e.Le résultat du programme nb_rand avec la librairie lib-rand.so

f.Après l’exécution, le package knockd a été installé, activé au démarrage du système et redémarrer

g.Liste des règles du pare-feu avant l’ouverture du port SSH à distance

h.Liste des règles du pare-feu après l’ouverture du port SSH à distance


3.SSH et recréation d’un backdoor
a. Le programme ci-dessous permet de récupérer et afficher les identifiants saisis en paramètre de la commande SSH




Après compilation et exécution, voici le résultat de chaque commande ssh lancé.
 

b.Programme permettant la création d’un backdoor sur le système.

Ce programme (librairie) ci-dessus permet l’acceptation et accorde les droits d’accès à la machine cible suite à la réception de communication sur le port 2025.
 

Ensuite, j’ai créé ce programme qui met le port 2222 en écoute et appeler la fonction accept de mon précèdent programme. Si le port envoyé matche avec le port défini de la fonction accept, il connecte la machine émettrice à la cible. 
Les résultats de ces programmes :
i.Compilation

ii.Exécution sur la machine cible
iii.Exploitation du backboor

4.Cacher les fichiers sur la machine cible
Ci-dessous mon programme permettant de cacher les fichiers sur la cible. 

i.Compilation

ii.Résultats avant passage en variable d’environnement LD_PRELOAD

iii.Résultats après passage en variable d’environnement LD_PRELOAD


5.Programme main du malware
J’ai créé un programme permettant de lancer les différentes fonctionnalités du malware et réadapter la fonction rand et nb_rand pour permettre de lancer les différentes parties du malware à distance.




Les différentes commandes du port knocking permettant d’activer les différentes parties du malware :
a.Ouvrir le port SSH


b.Fermer le port SSH


c.Installer et configurer le port knocking

d.Cacher les fichiers du malware 


e.Activer le backdoor


f.Libérer la variable d’environnement


6.Installation et configuration du commande et contrôle (C2)
Le serveur de commande et contrôle (C2) permet d'interagir avec les machines compromises et d'exécuter des instructions à distance. Cette section décrit l’installation et la configuration en ligne de commande.
6.1 Installation des dépendances
sudo apt update && sudo apt upgrade -y
sudo apt install -y gcc make python3 python3-pip ufw
