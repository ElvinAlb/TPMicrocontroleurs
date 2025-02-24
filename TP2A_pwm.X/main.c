/*
 * File:   main.c
 * Author: edche
 *
 * Created on February 7, 2025, 9:54 PM
 */

#define BUTTON_PORT PORTBbits.RB0  // Bouton S1 connecté à RB1
#define LED_PWM_PIN 0x0C        // Numéro du PPS pour PWM4
#include <xc.h>
#include "configbits.h"

//Configurer les ports B et D
void setupPorts(void) {
    TRISD = 0x00; // Configure PORTD en sortie (LEDs D1-D4)
    TRISB = 0xFF;  // Configure PORTB en entrée (bouton S1)
    LATD = 0b0001;  
    LATB = 0b0000; 
}

//Configurer la Pulse Width Modulation
void setupPWM() {
    // 2. Mapper PWM4 sur RD0 via Peripheral Pin Select (PPS)
    RD0PPS = 0b00001111;  // Mapper PWM4 sur RD0

    // 5. Initialiser le duty cycle à 0%
    PWM4DCH = 3;     // Rapport cyclique initial (10%)
    PWM4DCL = 0;      // Partie basse

    PWM4CONbits.PWM4EN = 1; // Activer le module PWM4
    PWM4CONbits.PWM4POL = 0;
    PWM4CONbits.PWM4OUT = 0; // Module PWM Actif à l'état haut
    
    RC2PPS = LED_PWM_PIN; // Associe la broche RC2 à PWM4
}

//Configurer le timer
void setupTimer(){
    PR2 = 124;
    // Configuration de PWM4
    T2CONbits.TMR2ON=1;         // Activer le timer
    T2CONbits.T2CKPS=0b00; 
    T2CONbits.T2OUTPS=0b1111;
}

//Configurer le bouton RB0
void setupButton() {
    TRISBbits.TRISB0 = 1;  // RB0 en entrée
    ANSELBbits.ANSB0 = 0;  // Désactiver le mode analogique sur RB0 si nécessaire
}
void main(void) {
    setupPorts();
    setupPWM();
    setupTimer();
    setupButton();
    while (1){
        if (PORTBbits.RB0 == 0) {
            // Duty cycle à 100%
            PWM4DCH = 0xFF;  // 255
            PWM4DCL = 0x00;  // (3 << 6) = 0xC0  ? (255*4 + 3 = 1023)
        } else {
            // Sinon (bouton relâché) : duty cycle à 10%
            PWM4DCH = 3;    // 25
            PWM4DCL = 0x00;  // (2 << 6) = 0x80  ? (25*4 + 2 = 102)
        }
    }

}
