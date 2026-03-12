/**
 * SERVOS.CPP - Implémentation du contrôle des actionneurs
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère le déploiement des mécanismes physiques.
 * On utilise la bibliothèque Servo d'Arduino pour générer les signaux PWM.
 */

#include "Servos.h"

// Déclaration des objets Servo (liés aux variables 'extern' du .h)
Servo servoGauche;
Servo servoDroit;

/**
 * Initialisation des servomoteurs
 */
void initServos() {
    // Association des objets aux broches physiques (S1 et S2 définies dans Config.h)
    servoGauche.attach(S1);
    servoDroit.attach(S2);
    
    // Optionnel : Position de sécurité au démarrage (ex: bras repliés)
    // servoGauche.write(90); 
    // servoDroit.write(90);
}

/**
 * Séquence de déploiement de la Banderole
 * Cette action est déclenchée pour marquer des points en fin de match.
 */
void banderole() {
    // 1. On place les servos à l'angle 0 (Position initiale ou ouverture)
    servoGauche.write(0);
    servoDroit.write(0);
    
    // 2. Temporisation : On laisse 3,5 secondes au mécanisme pour se déployer
    // C'est une phase critique où le robot ne doit pas faire d'autre mouvement brusque
    delay(3500);
    
    // 3. On remet les servos à l'angle 92 (Position finale ou verrouillage)
    // Cette valeur de 92 a été choisie après calibration mécanique précise
    servoGauche.write(92);
    servoDroit.write(92);
}