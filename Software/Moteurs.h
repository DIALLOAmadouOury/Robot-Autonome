/**
 * MOTEURS.H - Gestion de la locomotion et de l'asservissement
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier définit les commandes de mouvement du robot.
 * Il utilise un algorithme PID pour garantir des trajectoires droites.
 */

#ifndef MOTEURS_H
#define MOTEURS_H

#include <Arduino.h>
#include <PID_v1.h>
#include "Config.h"

/**
 * Énumération des mouvements possibles
 * Permet de rendre le code plus lisible (ex: deplacer_robot(AVANCER, 10))
 */
enum MouvementType { AVANCER, RECULER, TOURNER_GAUCHE, TOURNER_DROITE };

/**
 * Initialise les broches moteurs (PWM et Direction) 
 * ainsi que les interruptions pour les encodeurs.
 */
void initMoteurs();

/**
 * Arrête immédiatement les deux moteurs (freinage ou roue libre selon le driver).
 */
void arreter();

/**
 * Déplace le robot avec contrôle par encodeurs et PID.
 * @param type : Direction du mouvement (AVANCER, RECULER, etc.)
 * @param valeur_cm_ou_deg : Distance en cm ou angle en degrés pour la rotation.
 * Note : Cette fonction est sécurisée par les capteurs de distance.
 */
void deplacer_robot(MouvementType type, double valeur_cm_ou_deg);

/**
 * Déplace le robot sans vérification des capteurs de proximité.
 * Utile pour de petits ajustements ou pour quitter une zone encombrée.
 */
void deplacer_robot_sans_capteur(MouvementType type, double valeur_cm_ou_deg);

// ==========================================
// VARIABLES EXTERNES (Partagées avec Moteurs.cpp)
// ==========================================

// Compteurs d'impulsions des encodeurs (mis à jour par les interruptions)
// volatile : indique au compilateur que ces valeurs changent en dehors du flux principal
extern volatile long impulsion_m1; 
extern volatile long impulsion_m2;

// Variables de calcul de l'odométrie
extern volatile double distance1;        // Distance parcourue roue gauche
extern volatile double distance2;        // Distance parcourue roue droite
extern volatile double moyenne_distance; // Moyenne pour le calcul de position

#endif