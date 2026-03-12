/**
 * ELECTROAIMANTS.H - Contrôle des systèmes de préhension magnétique
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère l'activation des électro-aimants.
 * Ces composants permettent au robot de saisir, maintenir et relâcher
 * les éléments de jeu métalliques ou magnétiques.
 */

#ifndef ELECTROAIMANTS_H
#define ELECTROAIMANTS_H

#include <Arduino.h>
#include "Config.h"

/**
 * Initialise les broches de commande des électro-aimants.
 * Configure les pins (A1 à A4) en mode SORTIE et s'assure
 * qu'ils sont désactivés par défaut pour économiser l'énergie.
 */
void initElectroaimants();

/**
 * Active une paire ou un électro-aimant spécifique.
 * @param A : Numéro du premier aimant à activer.
 * @param B : Numéro du deuxième aimant (ou 0 si un seul est utilisé).
 * Note : Envoie un signal HIGH vers le transistor/relais de puissance.
 */
void activerAimant(int A, int B);

/**
 * Désactive les électro-aimants pour relâcher l'objet.
 * @param A : Numéro du premier aimant à couper.
 * @param B : Numéro du deuxième aimant à couper.
 */
void desactiverAimant(int A, int B);

#endif