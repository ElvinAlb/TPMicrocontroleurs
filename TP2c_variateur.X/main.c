/*
 * File:   main.c
 * Author: edche
 *
 * Created on February 10, 2025, 3:43 PM
 */


#include <xc.h>
#include "configbits.h"
#define LED_PWM_PIN 0x0C 

//Configurer les LEDS
void setupLEDS(){
    TRISD = 0x00;
    LATD = 0b0000;
}

// Configurer le Timer
void setupTimer(){
    // Toverflow de 1ms
    PR2 = 124;
    T2CONbits.T2CKPS = 0b10; //Prescaler de 1:16
    T2CONbits.TMR2ON = 1; // Activer le timer
    T2CONbits.T2OUTPS = 0b00;//Postscaler de 1:1
}

//Configurer le Analog to Digital Converter
void setupADC() {
    //Configurer l'ADC
    ADCON1bits.ADFM = 1;   // Résultat justifié à droite (valeur complète sur 10 bits)
    ADCON1bits.ADCS = 0b110; // Horloge ADC = Fosc/64
    ADCON1bits.ADNREF = 0; // Référence bas = 0V
    ADCON1bits.ADPREF = 0b00; // Référence haut = Vdd (5V)

    //Activer l'ADC
    ADCON0bits.ADON = 1;
}

//Configurer le potentiomètre
void setupPotentiometer(){
    TRISAbits.TRISA0 = 1; // Configurer le potentiomètre en entrée
    ANSELAbits.ANSA0 = 1; // La configurer en analogique
}

//Configurer la Pulse Width Modulation
void setupPWM() {
    // 2. Mapper PWM4 sur RD0 via Peripheral Pin Select (PPS)
    RD0PPS = 0b00001111;  // Mapper PWM4 sur RD0

    // 5. Initialiser le duty cycle à 0%
    PWM4DCH = 0xff;      // Partie haute
    PWM4DCL = 0;      // Partie basse

    // 6. Activer le module PWM4
    PWM4CON = 0b11000000;  // PWM activé, signal en mode PWM
}

// Obtenir la valeur analogique du potentiomètre
unsigned int get_potentiometer_value() {
    ADCON0bits.CHS = 0b00000; // Sélectionner AN0
    ADCON0bits.GO = 1;        // Démarrer la conversion
    while(ADCON0bits.GO);     // Attendre la fin de conversion

    return ((ADRESH << 8) + ADRESL); // Retourner la valeur 10 bits
}

//Attribuer l'intensité lumineuse souhaitée à la LED D1
void displayLEDs(unsigned int adcValue) {
   //adcValue = adcValue >> 7;
   //char r = 1 << adcValue;
   // Valeur entre 0 et 15
   
   unsigned int level = adcValue / 64; // 1024 / 16 = 64
   
   unsigned int dutyCycle = (level * 1023) / 15;
   
   PWM4DCH = dutyCycle >> 2;      // 8 bits de poids fort
   PWM4DCL = (dutyCycle & 0x03) << 6; // 2 bits de poids faible dans les bits 7:6
}



void main(void) {
    setupTimer();
    setupLEDS();
    setupADC();
    setupPWM();
    setupPotentiometer();
    while (1){
        unsigned int adcValue = get_potentiometer_value();
        displayLEDs(adcValue);
        
    }
}
