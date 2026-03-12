/**
 * ELECTROAIMANTS.CPP - Implémentation du contrôle de puissance
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère l'état logique des broches commandant les 
 * électro-aimants via l'interface de puissance (transistors/MOSFETs).
 */

#include "Electroaimants.h"

/**
 * Configuration initiale des ports de sortie
 */
void initElectroaimants() {
    // Définition des broches A1 à A4 comme sorties numériques
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(A3, OUTPUT);
    pinMode(A4, OUTPUT);

    // Initialisation à l'état BAS (0V) pour éviter toute consommation
    // d'énergie ou activation accidentelle au démarrage.
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(A3, LOW);
    digitalWrite(A4, LOW);
}

/**
 * Activation des électro-aimants
 * @param A : Pin de l'aimant 1 (ex: A1)
 * @param B : Pin de l'aimant 2 (ex: A2)
 */
void activerAimant(int A, int B) {
    // Envoi d'un signal HAUT (5V) pour fermer le circuit de puissance
    if (A != 0) digitalWrite(A, HIGH);
    if (B != 0) digitalWrite(B, HIGH); 
    
    if (debug) Serial.println("Action : Électro-aimants ACTIVÉS");
}

/**
 * Désactivation des électro-aimants
 * @param A : Pin de l'aimant 1
 * @param B : Pin de l'aimant 2
 */
void desactiverAimant(int A, int B) {
    // Envoi d'un signal BAS (0V) pour couper le champ magnétique
    if (A != 0) digitalWrite(A, LOW);
    if (B != 0) digitalWrite(B, LOW);
    
    if (debug) Serial.println("Action : Électro-aimants DÉSACTIVÉS");
}