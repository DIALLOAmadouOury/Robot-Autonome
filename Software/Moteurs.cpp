/**
 * MOTEURS.CPP - Logique d'asservissement et de contrôle moteur
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère la lecture des encodeurs en temps réel (Interruptions)
 * et la correction de trajectoire par algorithme PID.
 */

#include "Moteurs.h"

// ==========================================
// 1. VARIABLES D'ODOMÉTRIE (États du robot)
// ==========================================
// volatile : nécessaire car ces variables sont modifiées dans les interruptions
volatile long impulsion_m1 = 0; // Compteur de tics roue gauche
volatile long impulsion_m2 = 0; // Compteur de tics roue droite
volatile double tour_r1 = 0, tour_r2 = 0;
volatile double distance1 = 0.0, distance2 = 0.0, moyenne_distance = 0.0;

// ==========================================
// 2. VARIABLES DE RÉGULATION PID
// ==========================================
double angle_erreur = 0;    // Écart de distance entre les deux roues
double angle_correctif = 0; // Valeur de sortie du PID pour corriger la vitesse
double consigne_angle = 0;  // On veut que l'écart (angle_erreur) soit toujours de 0
double vitesseM1 = 0, vitesseM2 = 0;

// Initialisation du contrôleur PID (Bibliothèque PID_v1)
// On cherche à annuler l'angle_erreur en ajustant l'angle_correctif
PID pidAngle(&angle_erreur, &angle_correctif, &consigne_angle, K3p, K3i, K3d, DIRECT);

// ==========================================
// 3. GESTION DES INTERRUPTIONS (Encodeurs)
// ==========================================

/**
 * ISR (Interrupt Service Routine) pour la roue gauche
 * Appelé à chaque front montant sur la phase A de l'encodeur
 */
void compterImpulsions1() {
    // Vérification de la phase B pour déterminer le sens de rotation (Quadrature)
    if (digitalRead(ENCODER1_B) == HIGH) impulsion_m1++;
    else impulsion_m1--;
    
    // Conversion : tics -> nombre de tours -> distance en cm
    tour_r1 = impulsion_m1 / (double)RESOLUTION_ENCODEUR;
    distance1 = abs(tour_r1 * perimetre_roue);
}

/**
 * ISR pour la roue droite
 */
void compterImpulsions2() {
    if (digitalRead(ENCODER2_B) == HIGH) impulsion_m2++;
    else impulsion_m2--;
    
    tour_r2 = impulsion_m2 / (double)RESOLUTION_ENCODEUR;
    distance2 = abs(tour_r2 * perimetre_roue);
    
    // Calcul de la distance moyenne parcourue par le centre du robot
    moyenne_distance = (distance1 + distance2) / 2;
}

// ==========================================
// 4. INITIALISATION ET CONTRÔLE BAS NIVEAU
// ==========================================

void initMoteurs() {
    // Configuration des broches du pont en H
    pinMode(ENA1, OUTPUT); pinMode(INA1, OUTPUT);
    pinMode(ENA2, OUTPUT); pinMode(INA2, OUTPUT);

    // Configuration des encodeurs avec résistances de pull-up internes
    pinMode(ENCODER1_A, INPUT_PULLUP); pinMode(ENCODER1_B, INPUT_PULLUP);
    pinMode(ENCODER2_A, INPUT_PULLUP); pinMode(ENCODER2_B, INPUT_PULLUP);

    // Attachement des interruptions sur les pins A des encodeurs
    attachInterrupt(digitalPinToInterrupt(ENCODER1_A), compterImpulsions1, RISING);
    attachInterrupt(digitalPinToInterrupt(ENCODER2_A), compterImpulsions2, RISING);

    // Paramétrage du PID
    pidAngle.SetMode(AUTOMATIC);
    pidAngle.SetSampleTime(Periode); // Fréquence de calcul (20ms par défaut)
    pidAngle.SetOutputLimits(-50, 50); // Limite l'influence de la correction

    arreter();
}

void arreter() {
    analogWrite(ENA1, 0);
    analogWrite(ENA2, 0);
}

// ==========================================
// 5. FONCTION DE DÉPLACEMENT INTELLIGENT
// ==========================================

/**
 * Gère les trajectoires avec asservissement
 * @param type : AVANCER, RECULER, TOURNER_GAUCHE, TOURNER_DROITE
 * @param valeur_cm_ou_deg : Consigne de distance ou d'angle
 */
void deplacer_robot(MouvementType type, double valeur_cm_ou_deg) {
    // Reset des compteurs pour ce nouveau mouvement
    impulsion_m1 = 0; impulsion_m2 = 0;
    distance1 = 0; distance2 = 0; moyenne_distance = 0;
    
    double consigne_distance1, consigne_distance2;
    
    // --- Phase 1 : Calcul de la consigne et direction ---
    if (type == AVANCER || type == RECULER) {
        consigne_distance1 = consigne_distance2 = valeur_cm_ou_deg;
        digitalWrite(INA1, type == AVANCER ? LOW : HIGH);
        digitalWrite(INA2, type == AVANCER ? LOW : HIGH);
    } else {
        // Pour les rotations : calcul de l'arc de cercle (entraxe)
        double distance_rotation = (valeur_cm_ou_deg / 360.0) * (pi * entraxe_cm);
        consigne_distance1 = consigne_distance2 = distance_rotation;
        if (type == TOURNER_GAUCHE) { digitalWrite(INA1, HIGH); digitalWrite(INA2, LOW); }
        else { digitalWrite(INA1, LOW); digitalWrite(INA2, HIGH); }
    }
    
    // --- Phase 2 : Boucle d'asservissement ---
    // Tant que la cible n'est pas atteinte
    while (distance1 < consigne_distance1 && distance2 < consigne_distance2) {
        
        // Calcul de l'erreur d'alignement (différence entre les roues)
        angle_erreur = distance1 - distance2;
        pidAngle.Compute(); // Le PID calcule "angle_correctif"

        // On part de la vitesse de base
        vitesseM1 = Vitesse1; vitesseM2 = Vitesse2;

        // On ajuste la vitesse de chaque moteur pour compenser la dérive
        // Si angle_erreur > 0, la roue 1 est en avance, on la ralentit et on accélère la roue 2
        if (angle_erreur > 0) { 
            vitesseM1 -= abs(angle_correctif); 
            vitesseM2 += abs(angle_correctif); 
        } else { 
            vitesseM2 -= abs(angle_correctif); 
            vitesseM1 += abs(angle_correctif); 
        }

        // Sécurité : on limite la vitesse entre 0 et 100 (PWM)
        vitesseM1 = constrain(vitesseM1, 0, 100);
        vitesseM2 = constrain(vitesseM2, 0, 100);

        // Application de la puissance aux moteurs
        analogWrite(ENA1, vitesseM1);
        analogWrite(ENA2, vitesseM2);

        // Débuggage série (si activé dans Config.h)
        if (debug) {
            Serial.print("D1: "); Serial.print(distance1);
            Serial.print(" | Err: "); Serial.println(angle_erreur);
        }
        delay(10); // Laisse le temps au processeur de respirer
    }

    arreter(); // Stop final une fois la consigne atteinte
}

void deplacer_robot_sans_capteur(MouvementType type, double valeur_cm_ou_deg) {
    deplacer_robot(type, valeur_cm_ou_deg);
}