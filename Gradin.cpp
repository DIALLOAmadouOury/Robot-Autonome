/**
 * GRADINS.CPP - Implémentation de la stratégie de match
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier contient les séquences de mouvements complexes
 * pour marquer des points selon le règlement.
 */

#include "Gradins.h"
#include "Moteurs.h"

/**
 * Séquence de construction du premier gradin
 * @param p : Orientation du terrain (1 = Côté jaune, 2 = Côté Bleu)
 */
void construire_gradin1(int p) {
    // 1. Approche de la zone de construction
    deplacer_robot(AVANCER, 55);
    
    // 2. Pivotement adaptatif selon le côté du terrain
    if(p==1) deplacer_robot(TOURNER_DROITE, 94);
    else deplacer_robot(TOURNER_GAUCHE, 93);
    
    // 3. Alignement et poussée des éléments de jeu
    deplacer_robot(AVANCER, 45);
    
    if(p==1) deplacer_robot(TOURNER_DROITE, 94);
    else deplacer_robot(TOURNER_GAUCHE, 94);
    
    // 4. Manœuvre de précision pour caler le gradin
    deplacer_robot(AVANCER, 43);
    deplacer_robot(RECULER, 31);
    
    // 5. Dégagement pour passer à l'action suivante
    if(p==1) deplacer_robot(TOURNER_GAUCHE, 94);
    else deplacer_robot(TOURNER_DROITE, 94);
    
    deplacer_robot(AVANCER, 19);
    
    if(p==1) deplacer_robot(TOURNER_GAUCHE, 94);
    else deplacer_robot(TOURNER_DROITE, 94);
    
    Serial.println("Statut : Gradin 1 terminé");
}

/**
 * Navigation vers la zone Fosse 1 (Collecte)
 */
void Aller_fosse1(int p) {
    deplacer_robot(AVANCER, 25);
    
    // Virage pour éviter les bordures
    if(p==1) deplacer_robot(TOURNER_GAUCHE, 45);
    else deplacer_robot(TOURNER_DROITE, 45);
    
    deplacer_robot(AVANCER, 20);
    
    if(p==1) deplacer_robot(TOURNER_DROITE, 45);
    else deplacer_robot(TOURNER_GAUCHE, 45);
    
    // Longue ligne droite vers l'objectif
    deplacer_robot(AVANCER, 85);
    Serial.println("Statut : Robot arrivé Fosse 1");
}

/**
 * Navigation vers la zone Fosse 2 (Collecte alternative)
 */
void Aller_fosse2(int p) {
    deplacer_robot(AVANCER, 25);
    
    if(p==1) deplacer_robot(TOURNER_GAUCHE, 45);
    else deplacer_robot(TOURNER_DROITE, 45);
    
    deplacer_robot(AVANCER, 30);
    
    if(p==1) deplacer_robot(TOURNER_DROITE, 45);
    else deplacer_robot(TOURNER_GAUCHE, 45);
    
    deplacer_robot(AVANCER, 80);
    Serial.println("Statut : Robot arrivé Fosse 2");
}

/**
 * Positionnement sur la scène pour la fin de match
 */
void Aller_scene(int p) {
    deplacer_robot(AVANCER, 110);
    
    if(p==1) deplacer_robot(TOURNER_GAUCHE, 45);
    else deplacer_robot(TOURNER_DROITE, 45);
    
    deplacer_robot(AVANCER, 30);
    Serial.println("Statut : Robot positionné sur la Scène");
}

/**
 * Retour final en zone d'arrivée (Sécurité de fin de match)
 * @param tempsDebut : Moment du lancement du match
 */
void aller_arriver(int p, unsigned long tempsDebut) {
    deplacer_robot(AVANCER, 83);
    
    // Vérification critique : arrêt total obligatoire à 95 secondes
    if(millis() - tempsDebut >= 95000) {
        arreter();
        Serial.println("Match terminé : Arrêt d'urgence activé");
        while(1); // Bloque toute action ultérieure (Règlement Eurobot)
    }
    
    Serial.println("Statut : Robot en zone d'arrivée, mission accomplie");
}