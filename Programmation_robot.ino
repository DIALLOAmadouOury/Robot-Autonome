/**
 * PROJET : EUROBOT 2024/2025 - "The Show Must In"
 * FICHIER : Programmation_robot.ino (Fichier Principal)
 * AUTEUR : Amadou Oury DIALLO
 * DESCRIPTION : Orchestration du match de 95 secondes. 
 * Gestion de la chronologie, des actions de jeu et de l'arrêt de sécurité.
 */

#include "Config.h"         // Définitions des pins et constantes
#include "Moteurs.h"        // Fonctions de déplacement (avancer, reculer, etc.)
#include "Capteurs.h"       // Gestion des ultrasons
#include "Servos.h"         // Contrôle des bras servomoteurs
#include "Electroaimants.h" // Gestion de la préhension des PAMIs
#include "Gradins.h"        // Algorithmes spécifiques aux actions de jeu
#include "TFT.h"            // Fonctions d'affichage graphique

// Variable de temps pour respecter la durée réglementaire de 95 secondes
unsigned long tempsDebut;

/**
 * Initialisation du système
 */
void setup() {
    Serial.begin(9600); // Communication série pour le débug

    // Initialisation des différents modules matériels
    initMoteurs();         // Configuration des PWM et directions
    initServos();          // Positionnement initial des bras
    initElectroaimants();  // Mise hors tension des aimants au départ
    initTFT();             // Allumage et configuration de l'écran

    // On enregistre le temps exact de début de match (au retrait de la tirette)
    tempsDebut = millis();
}

/**
 * Boucle principale : Chronologie du match
 */
void loop() {
    
    // --- Phase 1 : Déplacement initial ---
    // On quitte la zone de départ en marche arrière sur environ 4 unités
    deplacer_robot_sans_capteur(RECULER, 4);

    // --- Phase 2 : Actions de jeu ---
    banderole();            // Déploiement de la banderole (points de fin de match)
    construire_gradin1(1);  // Premier cycle de construction des gradins
    construire_gradin2(1);  // Deuxième cycle de construction

    // --- Phase 3 : Attente et sécurité (Zone Critique) ---
    // Le match doit durer 95s maximum. Ici on gère l'attente jusqu'à 89s
    // pour s'assurer de ne pas faire d'action interdite après la fin.
    while (millis() - tempsDebut < 89000) {
        arreter();          // On immobilise le robot
        delay(50);          // Petite pause pour stabiliser le CPU
    }

    // --- Phase 4 : Fin de match ---
    score();                // Affichage du score estimé sur l'écran TFT
    
    // Retour à la zone d'arrivée avant la fin du temps réglementaire
    aller_arriver(1, tempsDebut);

    // --- Phase 5 : Arrêt Total Obligatoire ---
    // À 95 secondes, tout doit être coupé selon le règlement Eurobot
    if (millis() - tempsDebut >= 95000) {
        arreter();          // Coupure des moteurs
        while(1);           // Boucle infinie pour bloquer le robot jusqu'au reset manuel
    }
}