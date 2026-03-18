# Robot – Coupe de France de Robotique   2024-2025

## Description

Ce projet a été réalisé dans le cadre de la **Coupe de France de Robotique**.
L'objectif était de concevoir un robot autonome capable de se déplacer sur un terrain de jeu et d'effectuer différentes actions comme manipuler des objets et construire des structures.

Le robot est basé sur une **base roulante différentielle** et est contrôlé par un **microcontrôleur Arduino**.
Le logiciel embarqué a été développé en **C/C++ avec une architecture modulaire** pour faciliter la maintenance et la lisibilité du code.

---

## Fonctionnalités principales

* Déplacement du robot avec deux moteurs
* Contrôle de la trajectoire avec **PID et encodeurs**
* Détection d'obstacles avec des capteurs
* Manipulation d'objets avec des **servomoteurs**
* Utilisation d'**électroaimants**
* Construction de gradins sur la zone de jeu
* Affichage d'informations sur un écran **TFT**

---

## Structure du projet

Software/

* `Programmation_robot.ino` : programme principal
* `Moteurs.cpp / Moteurs.h` : contrôle des moteurs
* `Capteurs.cpp / Capteurs.h` : gestion des capteurs
* `Servos.cpp / Servos.h` : contrôle des servomoteurs
* `Electroaimants.cpp / Electroaimants.h` : gestion des électroaimants
* `Gradins.cpp / Gradins.h` : logique de construction des gradins
* `TFT.cpp / TFT.h` : affichage des informations sur écran

---

## Technologies utilisées

* Arduino
* C / C++
* Encodeurs pour le contrôle de vitesse
* Servomoteurs
* Capteurs de distance
* Électroaimants
* Écran TFT

---

## Contexte du projet

Ce projet a été réalisé **en équipe de 6 étudiants** dans le cadre d’un projet de robotique et de participation à la **Coupe de France de Robotique**.

### Ma contribution

* Programmation du robot en **C/C++**
* Implémentation du **contrôle PID pour la base roulante**
* Gestion des capteurs et détection d'obstacles
* Organisation du code en **programmation modulaire**
* Développement de la logique de déplacement et d'actions du robot

---

## Participation à la compétition

![Robot Competition](Media/robot_competition.jpg)

Photo prise lors de la préparation du robot pendant la **Coupe de France de Robotique**.

---

## Auteur

**Amadou Oury Diallo**
Étudiant ingénieur – Instrumentation et Systèmes Embarqués
Sup Galilée – Université Sorbonne Paris Nord

Compétences :

* C / C++
* Arduino
* Robotique
* Systèmes embarqués
* Modélisation (FreeCAD)
