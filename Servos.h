/**
 * SERVOS.H - Gestion des mécanismes par servomoteurs
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier définit le contrôle des bras et de la banderole.
 * Les servomoteurs permettent des mouvements angulaires précis 
 * pour interagir avec les éléments de jeu.
 */

#ifndef SERVOS_H
#define SERVOS_H

#include <Servo.h>
#include "Config.h"

// ==========================================
// OBJETS SERVOS (Partagés avec Servos.cpp)
// ==========================================
// On utilise 'extern' pour que ces objets soient accessibles 
// depuis le fichier principal ou d'autres modules.
extern Servo servoGauche;
extern Servo servoDroit;

/**
 * Initialise les servomoteurs :
 * 1. Attache les objets aux pins définies dans Config.h (S1, S2).
 * 2. Place les bras dans leur position de repos (sécurité au démarrage).
 */
void initServos();

/**
 * Gère l'action spécifique de la "Banderole".
 * Cette fonction pilote les servos pour déployer le dispositif 
 * de fin de match afin de valider les points bonus.
 */
void banderole();

#endif