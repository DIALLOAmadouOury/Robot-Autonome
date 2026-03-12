/**
 * CAPTEURS.CPP - Logique de détection d'obstacles
 * Projet : Eurobot 2024/2025
 * ---------------------------------------------------------
 * Ce fichier implémente la mesure de distance par ultrasons
 * et la gestion intelligente de la sécurité selon le mouvement.
 */

#include "Capteurs.h"

/**
 * Mesure la distance en cm à l'aide d'un capteur HC-SR04.
 * @param trig : Broche d'émission de l'impulsion ultrasonore.
 * @param echo : Broche de réception de l'écho.
 * @return : Distance calculée en centimètres.
 */
long mesurer_distance(int trig, int echo) {
  // 1. On s'assure que le signal Trigger est bien bas au départ
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  // 2. On émet un signal ultrasonore (pulse) pendant 10 microsecondes
  // C'est ce signal qui va rebondir sur l'obstacle
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // 3. Mesure de la durée du signal de retour sur la broche Echo
  // pulseIn() mesure le temps (en µs) pendant lequel la broche Echo reste à l'état HAUT
  long duree = pulseIn(echo, HIGH);

  // 4. Calcul de la distance physique
  // Vitesse du son = 340 m/s ou 0.034 cm/µs
  // On divise par 2 car le son fait un aller-retour (Robot -> Obstacle -> Robot)
  return duree * 0.034 / 2;
}

/**
 * Fonction de sécurité : vérifie si le chemin est libre.
 * Filtre les capteurs à interroger en fonction du sens de marche (Optimisation).
 */
bool obstacle_present(MouvementType type) {
    // Si le robot avance, on surveille les capteurs situés à l'avant
    if (type == AVANCER) {
        // Lecture du capteur Avant-Gauche
        long distAG = mesurer_distance(TRIG_AG, ECHO_AG);
        
        // On compare avec la valeur de sécurité définie dans Config.h
        if (distAG < SEUIL_OBSTACLE) {
            if (debug) Serial.println("! OBSTACLE AVANT GAUCHE !");
            return true;
        }

      
        
        if (mesurer_distance(TRIG_AD, ECHO_AD) < SEUIL_OBSTACLE) return true;
        
    }
    
    // Si on recule
    
    if (type == RECULER) {
        return mesurer_distance(TRIG_RG, ECHO_RG) < SEUIL_OBSTACLE;
    }
    

    // Par défaut, si aucun obstacle n'est détecté ou si on tourne sur place
    return false;
}