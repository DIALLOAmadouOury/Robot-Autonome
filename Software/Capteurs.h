/**
 * CAPTEURS.H - Système de perception ultrasonique
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère la détection d'obstacles en temps réel.
 * Il permet d'adapter la sécurité en fonction de la direction du robot.
 */

#ifndef CAPTEURS_H
#define CAPTEURS_H

#include <Arduino.h>
#include "Config.h"
#include "Moteurs.h"

/**
 * Mesure la distance physique séparant le capteur d'un obstacle.
 * Utilise la méthode du temps de vol (Time of Flight) d'une onde ultrasonore.
 * * @param trig : Broche d'émission (Trigger)
 * @param echo : Broche de réception (Echo)
 * @return : Distance en centimètres (long)
 */
long mesurer_distance(int trig, int echo);

/**
 * Analyse si un obstacle est présent sur la trajectoire actuelle.
 * Cette fonction est intelligente : elle ne vérifie que les capteurs 
 * situés dans la direction du mouvement pour éviter les arrêts inutiles.
 * * @param type : Le mouvement actuel (AVANCER, RECULER, etc.)
 * @return : true si un obstacle est sous le SEUIL_OBSTACLE, sinon false.
 */
bool obstacle_present(MouvementType type);

#endif