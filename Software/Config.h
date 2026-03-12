/**
 * CONFIG.H - Configuration matérielle et logicielle du Robot
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier centralise tous les paramètres physiques et les pins.
 * Il permet une maintenance rapide sans modifier le code source.
 */

#ifndef CONFIG_H
#define CONFIG_H

// ==========================================
// 1. MOTORISATION (Pont en H)
// ==========================================
#define ENA1 9      // Sortie PWM - Moteur Gauche
#define INA1 12     // Direction - Moteur Gauche
#define ENA2 8      // Sortie PWM - Moteur Droit
#define INA2 11     // Direction - Moteur Droit

#define Vitesse1 62 // Vitesse de croisière calibrée Gauche
#define Vitesse2 63 // Vitesse de croisière calibrée Droite

// ==========================================
// 2. GÉOMÉTRIE ET ODOMÉTRIE
// ==========================================
#define Diametre_roue 6.5    // Diamètre physique (cm)
#define perimetre_roue 20.42 // Distance pour 1 tour complet (cm)
#define entraxe_cm 21.79     // Distance entre les deux roues (pour calcul de rotation)
#define degre_per_cm 0.199   // Ratio de conversion pour les trajectoires

// ==========================================
// 3. ENCODEURS (Retour d'information moteur)
// ==========================================
#define RESOLUTION_ENCODEUR 418 // Nombre de tics par tour de roue
#define ENCODER1_A 2            // Pin Interruption A - Encodeur 1
#define ENCODER1_B 3            // Pin B - Encodeur 1
#define ENCODER2_A 18           // Pin Interruption A - Encodeur 2
#define ENCODER2_B 19           // Pin B - Encodeur 2

// ==========================================
// 4. ACTIONNEURS (Servos et Aimants)
// ==========================================
#define S1 4                    // Servomoteur Bras 1
#define S2 13                   // Servomoteur Bras 2
#define A1 39                   // Électroaimant 1 (Récupération PAMI)
#define A2 41                   // Électroaimant 2
#define A3 43                   // Électroaimant 3
#define A4 45                   // Électroaimant 4

// ==========================================
// 5. SYSTÈME DE DÉTECTION (Ultrasons HC-SR04)
// ==========================================
#define SEUIL_OBSTACLE 10       // Distance d'arrêt d'urgence (cm)

// Pins Trigger et Echo pour chaque capteur
#define TRIG_D_bas 36 ; #define ECHO_D_bas 38
#define TRIG_G_bas 26 ; #define ECHO_G_bas 46
#define TRIG_AG 34    ; #define ECHO_AG 32    // Avant Gauche
#define TRIG_AD 52    ; #define ECHO_AD 53    // Avant Droit
#define TRIG_RG 22    ; #define ECHO_RG 24    // Arrière Gauche
#define TRIG_RD 40    ; #define ECHO_RD 42    // Arrière Droit

// ==========================================
// 6. RÉGULATION PID (Asservissement)
// ==========================================
#define Periode 20              // Temps d'échantillonnage (ms)
#define K3p 1.5                 // Gain Proportionnel
#define K3i 0                   // Gain Intégral
#define K3d 0.1                 // Gain Dérivé

// ==========================================
// 7. CONSTANTES GÉNÉRALES
// ==========================================
#define pi 3.14
#define debug 1                 // 1 pour activer les logs Serial, 0 sinon

#endif