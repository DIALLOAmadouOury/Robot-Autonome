/**
 * TFT.CPP - Implémentation de l'Interface Graphique (IHM)
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier contient les fonctions de dessin basse couche
 * et la gestion de l'affichage du score final.
 */

#include "TFT.h"

// Initialisation de l'objet écran avec les pins définies dans Config.h
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

/**
 * Initialisation matérielle de l'écran
 */
void initTFT() {
    // Initialisation du contrôleur ST7735 (version Black Tab)
    tft.initR(INITR_BLACKTAB);
}

/**
 * Affiche du texte en gras par superposition de pixels
 * @param x, y : Coordonnées de départ
 * @param text : Chaîne de caractères à afficher
 */
void drawBoldText(int x, int y, const char* text) {
  // On dessine le texte 4 fois avec un décalage de 1 pixel
  // pour créer un effet d'épaisseur (gras)
  for (int dx = 0; dx <= 1; dx++)
    for (int dy = 0; dy <= 1; dy++) {
        tft.setCursor(x + dx, y + dy);
        tft.print(text);
    }
}

/**
 * Dessine l'emoji "Garçon" (représentant un PAMI)
 * @param x, y : Position sur l'écran
 */
void drawBoy(int x, int y) {
  tft.fillCircle(x + 5, y + 5, 5, ST77XX_YELLOW);    // Visage
  tft.fillCircle(x + 3, y + 3, 1, ST77XX_BLACK);     // Œil gauche
  tft.fillCircle(x + 7, y + 3, 1, ST77XX_BLACK);     // Œil droit
  tft.drawPixel(x + 4, y + 7, ST77XX_BLACK);         // Bouche (pixel 1)
  tft.drawPixel(x + 5, y + 8, ST77XX_BLACK);         // Bouche (pixel 2)
  tft.drawPixel(x + 6, y + 7, ST77XX_BLACK);         // Bouche (pixel 3)
  tft.drawLine(x, y, x + 10, y, ST77XX_BLUE);        // Accessoire (Casquette)
}

/**
 * Dessine l'emoji "Fille"
 * @param x, y : Position sur l'écran
 */
void drawGirl(int x, int y) {
  tft.fillCircle(x + 5, y + 5, 5, ST77XX_YELLOW);    // Visage
  tft.fillCircle(x + 3, y + 3, 1, ST77XX_BLACK);     // Œil gauche
  tft.fillCircle(x + 7, y + 3, 1, ST77XX_BLACK);     // Œil droit
  tft.drawPixel(x + 4, y + 7, ST77XX_BLACK);         // Bouche
  tft.drawPixel(x + 5, y + 8, ST77XX_BLACK);
  tft.drawPixel(x + 6, y + 7, ST77XX_BLACK);
  tft.drawCircle(x + 5, y - 1, 6, ST77XX_RED);       // Accessoire (Bandeau)
}

/**
 * Écran final récapitulatif du match
 */
void score() {
    tft.setRotation(1);               // Passage en mode paysage
    tft.fillScreen(ST77XX_MAGENTA);    // Fond magenta pour la visibilité
    tft.setTextColor(ST77XX_BLACK);
    tft.setTextSize(2);               // Taille de texte lisible
    
    // Affichage des informations de points
    drawBoldText(10, 30, "Estimation :");
    drawBoldText(30, 70, "38 points");
    
    // Affichage de la "famille" de PAMIs (Garçons et Filles)
    drawBoy(10, 10); drawBoy(30, 10); drawGirl(60, 10); drawGirl(80, 10);
    drawBoy(110, 10); drawBoy(130, 10); drawBoy(150, 10);
    
    // Identifiant de l'équipe ou du robot
    tft.setTextColor(ST77XX_RED);
    tft.setCursor(40, 110);
    tft.print("P13 CRIG1");
    
    if (debug) Serial.println("Affichage final effectué.");
}