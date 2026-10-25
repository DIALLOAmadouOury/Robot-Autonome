# Robot autonome — Coupe de France de Robotique 2024–2025

**Robotique mobile · C++ embarqué / Arduino · Asservissement PID · Encodeurs · Interruptions · Capteurs · Actionneurs**

## Pourquoi ce projet ?

Dans le cadre de la **Coupe de France de Robotique 2024–2025**, notre équipe de **six étudiants** a travaillé sur un robot capable d'effectuer une série de missions sur un terrain de compétition : **se déplacer jusqu'à différentes zones, réaliser des actions de jeu et gérer un match limité à 95 secondes**.

Le défi n'était pas seulement de faire tourner deux moteurs. Il fallait coordonner **déplacements, positionnement, mécanismes, capteurs et temps de match** dans un programme embarqué suffisamment organisé pour pouvoir modifier les parcours et les actions.

Ce dépôt présente la partie logicielle du projet, développée en **C++ avec l'environnement Arduino**, sur une **base roulante différentielle**.

**[Voir le programme principal](Software/Programmation_robot.ino)** · **[Consulter l'asservissement moteur](Software/Moteurs.cpp)** · **[Explorer le code du robot](Software/)**

## Ce que le robot devait accomplir

Le programme principal organise une succession de phases :

1. **Initialiser le robot** : moteurs, servomoteurs, électroaimants et écran TFT.
2. **Quitter la zone de départ**, puis exécuter des actions de jeu, notamment le déploiement de la banderole et les déplacements associés à la construction de gradins.
3. **Tenir compte du chronomètre** : attendre avant la fin du match et préparer le retour.
4. **Rejoindre la zone d'arrivée** et demander l'arrêt des moteurs en fin de séquence.

Cette logique est visible dans [`Programmation_robot.ino`](Software/Programmation_robot.ino). Les déplacements sont écrits sous forme de commandes de haut niveau comme `deplacer_robot(AVANCER, 55)` ou `deplacer_robot(TOURNER_DROITE, 94)`, plutôt que de multiplier directement les commandes de broches dans le programme principal.

**Architecture du logiciel :**

```text
Séquence de match (Programmation_robot.ino)
            |
            +--> Déplacements / trajectoires (Moteurs.cpp)
            |        +--> PWM des moteurs
            |        +--> Encodeurs / interruptions
            |        +--> Correction PID
            |
            +--> Actions de jeu (Gradin.cpp)
            +--> Servomoteurs / banderole (Servos.cpp)
            +--> Électroaimants (Electroaimant.cpp)
            +--> Affichage sur écran TFT (TFT.cpp)

Module séparé : mesure ultrasonique / obstacles (Capteurs.cpp)
```

## Les choix techniques et ce que j'ai programmé

### 1. Déplacement et asservissement de la base roulante

Le robot utilise **deux moteurs indépendants** et des **encodeurs de roues**. Dans [`Moteurs.cpp`](Software/Moteurs.cpp), les impulsions sont comptées par des routines liées aux interruptions et servent à estimer la distance parcourue par chaque roue.

Lors d'un déplacement, le programme compare les deux distances, calcule une correction avec la bibliothèque **PID_v1** et ajuste les commandes PWM des moteurs. L'idée est de **réduire la dérive entre les roues** pour améliorer la tenue d'une trajectoire.

Le code comprend notamment :

- la gestion des encodeurs par `attachInterrupt()` et des compteurs `volatile` ;
- la conversion **impulsions → tours de roue → distance** ;
- une correction PID appliquée à l'écart de distance entre roues, avec une période de calcul configurée à **20 ms** dans la bibliothèque ;
- les commandes de direction et de vitesse pour avancer, reculer ou tourner, avec limitation des valeurs de PWM.

**[Lire l'implémentation moteur et PID](Software/Moteurs.cpp)** · [Voir les paramètres mécaniques et gains](Software/Config.h)

### 2. Détection d'obstacles et interactions avec l'environnement

Le module [`Capteurs.cpp`](Software/Capteurs.cpp) implémente la mesure par **capteurs ultrasoniques HC-SR04** : émission de l'impulsion, lecture du temps d'écho, calcul de distance et comparaison à un seuil de proximité. Les capteurs à interroger dépendent du sens de déplacement demandé.

**Important :** ce module est présent dans les sources, mais la boucle de déplacement principale publiée ne l'appelle pas encore. Il constitue donc une brique logicielle de perception, **pas une preuve d'évitement autonome d'obstacles en fonctionnement**.

### 3. Commande des mécanismes et stratégie de match

Les actions de jeu sont découpées en modules :

- [`Gradin.cpp`](Software/Gradin.cpp) : séquences de déplacements pour l'approche des zones et le positionnement en fonction du côté du terrain ;
- [`Servos.cpp`](Software/Servos.cpp) : commande de deux servomoteurs et séquence de déploiement de la banderole ;
- [`Electroaimant.cpp`](Software/Electroaimant.cpp) : initialisation et commande des sorties d'électroaimants pour la préhension ;
- [`TFT.cpp`](Software/TFT.cpp) : affichage graphique de fin de match sur un écran **ST7735**.

Cette séparation permet de travailler sur les **actionneurs**, la **locomotion** et la **stratégie** sans concentrer toutes les fonctions dans un seul fichier.

### 4. Organisation du firmware C++

Le programme s'appuie sur des modules `.cpp` et `.h`, et sur un fichier [`Config.h`](Software/Config.h) regroupant les broches, les dimensions du robot, la résolution des encodeurs, les vitesses et les gains du régulateur.

L'objectif de cette architecture est de **séparer la configuration matérielle, les fonctions bas niveau et les actions de haut niveau** : un aspect important du développement de logiciels embarqués maintenables.

## Mon rôle dans le projet

Dans ce projet réalisé en équipe, ma contribution a porté sur la **programmation du robot en C/C++**, en particulier l'**asservissement de la base roulante par PID et encodeurs**, la **gestion des capteurs**, la **structuration modulaire du logiciel** et l'**enchaînement des déplacements et des actions**.

Ce projet m'a permis de travailler à l'interface de plusieurs disciplines : **développement embarqué, automatique, électronique des capteurs et actionneurs, intégration mécanique et robotique mobile**.

## Structure du dépôt

| Fichier | Fonction |
| --- | --- |
| [`Programmation_robot.ino`](Software/Programmation_robot.ino) | Programme principal et chronologie des actions |
| [`Moteurs.cpp`](Software/Moteurs.cpp) | Encodeurs, déplacements, PID et commande des moteurs |
| [`Capteurs.cpp`](Software/Capteurs.cpp) | Mesure ultrasonique et détection de proximité |
| [`Gradin.cpp`](Software/Gradin.cpp) | Parcours et séquences de positionnement |
| [`Servos.cpp`](Software/Servos.cpp) | Commande des servomoteurs |
| [`Electroaimant.cpp`](Software/Electroaimant.cpp) | Commande des électroaimants |
| [`TFT.cpp`](Software/TFT.cpp) | Affichage de l'interface sur écran TFT |
| [`Config.h`](Software/Config.h) | Brochage, paramètres mécaniques et réglages |

Les principaux outils et bibliothèques mobilisés sont **Arduino**, **PID_v1**, **Servo**, **Adafruit_GFX** et **Adafruit_ST7735**.

## État du code et améliorations possibles

Le dépôt permet d'examiner l'**architecture de contrôle du robot** et ses différents modules C++. En revanche, il ne fournit ni résultat de tests de navigation ni rapport de compilation attestant que cette version est directement exécutable telle quelle.

Plusieurs points restent à finaliser ou documenter : **raccorder la détection d'obstacles à la commande de mouvement**, publier l'implémentation manquante de `construire_gradin2()`, revoir certaines définitions de broches dans `Config.h`, vérifier les dépendances de l'écran TFT et sécuriser l'arrêt en fin de match lorsque des mouvements bloquants sont en cours.

Une **photo ou une courte vidéo du robot** permettrait également de relier plus directement les séquences du code aux actions sur le terrain. Le lien vers la photo de l'ancien README a été retiré car le fichier image n'est pas présent dans le dépôt.

---

**Projet d'équipe — Coupe de France de Robotique 2024–2025**  
**Amadou Oury Diallo** — Instrumentation et systèmes embarqués, Sup Galilée · Université Sorbonne Paris Nord
