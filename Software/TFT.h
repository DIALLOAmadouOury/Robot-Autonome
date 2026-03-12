/**
 * TFT.H - Interface Homme-Machine (IHM)
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier gère l'affichage graphique sur l'écran ST7735.
 * Il permet d'afficher des diagnostics, des emojis et le score
 * en temps réel pour une interaction visuelle avec le robot.
 */

#ifndef TFT_H
#define TFT_H

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include "Config.h"

// ==========================================
// OBJET ÉCRAN (Partagé avec TFT.cpp)
// ==========================================
// 'extern' permet d'utiliser l'objet tft dans tous les autres fichiers .cpp
extern Adafruit_ST7735 tft;

/**
 * Initialisation de l'écran TFT :
 * 1. Démarre la communication SPI.
 * 2. Définit l'orientation de l'écran (Paysage).
 * 3. Remplit l'écran avec la couleur de fond par défaut (Noir).
 */
void initTFT();

/**
 * Affiche l'écran de fin de match :
 * 1. Dessine les emojis (Boy/Girl).
 * 2. Affiche l'estimation du score final calculé durant le match.
 * Cette fonction est appelée juste avant la fin des 95 secondes.
 */
void score();

#endif