/**
 * GRADINS.H - Logique métier et stratégie de match
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier définit les fonctions de haut niveau pour les 
 * actions spécifiques du règlement Eurobot.
 */

#ifndef GRADINS_H
#define GRADINS_H

#include "Moteurs.h"

/**
 * Réalise la première séquence de construction des gradins.
 * @param p : Coefficient ou variante de parcours (selon le côté de départ).
 */
void construire_gradin1(int p);

/**
 * Réalise la deuxième séquence de construction.
 * Gère les déplacements précis vers la zone de dépôt des éléments.
 */
void construire_gradin2(int p);

/**
 * Déplacement vers la zone "Fosse 1" pour la collecte d'éléments de jeu.
 */
void Aller_fosse1(int p);

/**
 * Déplacement vers la zone "Fosse 2".
 */
void Aller_fosse2(int p);

/**
 * Positionnement du robot sur la zone de la "Scène" pour les actions finales.
 */
void Aller_scene(int p);

/**
 * Gère le retour à la zone de départ/arrivée avant la fin du temps imparti.
 * @param p : Côté du terrain.
 * @param tempsDebut : Chronomètre du match pour vérifier le temps restant.
 */
void aller_arriver(int p, unsigned long tempsDebut);

#endif