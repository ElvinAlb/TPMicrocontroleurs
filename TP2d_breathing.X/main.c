/*
 * File:   main.c
 * Author: edche
 *
 * Created on February 10, 2025, 8:49 PM
 */


#include <xc.h>
#include "configbits.h"

// Direction de variation (1 = augmenter, 0 = diminuer)
volatile unsigned int direction = 1;
volatile unsigned int interruptCounter = 0; // Compteur d'interruptions
volatile unsigned int level = 0; // Niveau de luminosité (0-255)
char position = 0;
int nb_flag =0;
//Configurer les LEDS
void setupLEDS(){
    TRISD = 0b00; //Toutes les broches du port D en sortie
    LATD = 0b0000; //Laisser les LEDS éteintes
}

// Configurer le Timer
void setupTimer(){
    // Toverflow de 1ms
    PR2 = 249; //période du Timer 2
    T2CONbits.T2CKPS = 0b10; //Prescaler de 1:16
    T2CONbits.T2OUTPS = 0b00;//Postscaler de 1:1
    T2CONbits.TMR2ON = 1; // Activer le Timer 2

    
    
    PIE1bits.TMR2IE = 1; // Activer l'interruption Timer2
    INTCONbits.PEIE = 1; // Activer les interruptions périphériques
    INTCONbits.GIE = 1;  // Activer les interruptions globales
}

//Configurer la Pulse Width Modulation
void setupPWM() {
    //Mapper PWM4 sur RD0 via Peripheral Pin Select (PPS)
    RD0PPS = 0b00001111;  //Configurer la broche RD0 pour qu'elle reçoive le signal PWM4

    //Initialiser le duty cycle à 0%
    PWM4DCH = 0xff;    // Partie haute
    PWM4DCL = 0;      // Partie basse

    //Activer le module PWM4
    PWM4CON = 0b11000000;  // PWM activé, signal en mode PWM
}

// Fonction pour ajuster le duty cycle du PWM pour la LED D1
void updatePWM() {
    // Mettre à jour le duty cycle du PWM pour la LED D1
    PWM4DCH = level >> 2;      // 8 bits de poids fort
    PWM4DCL = (level & 0x03) << 6; // 2 bits de poids faible dans les bits 7:6
}

// Routine d'interruption
void __interrupt() ISR() {
    if (PIR1bits.TMR2IF) { //Vérifier si le timer 2 a généré une interrruption
        // Effacer le flag d'interruption Timer2
        PIR1bits.TMR2IF = 0;

        // Incrémenter le compteur d'interruptions
        interruptCounter++;

        // Mettre à jour le niveau de luminosité toutes les deux interruptions
        if (interruptCounter >= 2) {
            interruptCounter = 0; // Réinitialiser le compteur
            // Mettre à jour le niveau de luminosité
            if (direction) {
                level++;
                if (level >= 255) {
                    direction = 0;
                }
            } else {
                level--;
                if (level == 0) {
                    direction = 1;
                }
            }
            // Mettre à jour le PWM
            updatePWM();
        }
    }
}

void main(void) {
    setupLEDS();
    setupPWM(); // Initialisation du PWM sur RD0
    setupTimer(); // Initialisation du Timer2 pour les interruptions
    while(1){
        
    }
    return;
}
