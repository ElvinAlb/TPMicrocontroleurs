/*
 * File:   main.c
 * Author: edche
 *
 * Created on February 10, 2025, 3:43 PM
 */


#include <xc.h>
#include "configbits.h"

//Configurer les diodes
void setupLEDS(){
    TRISD = 0x00;   // Configure PORTD en sortie (LEDs D1-D4)
    TRISB = 0x00;  // Configure PORTB en sortie (LEDs D5-D8)
    LATD = 0b0001;  //La led D1 est allumée
    LATB = 0b0000; 
}

//Configurer le potentiomètre
void setupPotentiometer(){
    TRISAbits.TRISA0 = 1;  // Configurer RA0 en entrée
    ANSELAbits.ANSA0 = 1;  // Activer AN0 comme entrée analogique
}

//Configurer le convertisseur analogique numérique
void setupADC(){
    ADCON0bits.CHS = 0b00000;  // Sélectionne AN0 comme canal d'entrée ADC
    ADCON0bits.ADON = 1;       // Active le module ADC
    ADCON1bits.ADFM = 1;       // Format du résultat à droite

}

// Fonction pour lire la valeur retournée par l'ADC sur AN0
unsigned int get_potentiometer_value() {
    ADCON0bits.CHS = 0b00000; // Sélectionner AN0
    ADCON0bits.GO = 1;        // Démarrer la conversion
    while(ADCON0bits.GO);     // Attendre la fin de conversion

    return ((ADRESH << 8) + ADRESL); // Retourner la valeur 10 bits
}

//Allumer les diodes selon la manipulation du potentiomètre
void displayLEDs(unsigned int adcValue) {
   adcValue = adcValue >> 7;
   char r = 1 << adcValue;
   LATD = r & 0b1111;
   LATB = r >> 4;
}

void main(void) {
    //Faire toutes les configurations
    setupLEDS();
    setupPotentiometer();
    setupADC();
    
    while (1){
        unsigned int adcValue = get_potentiometer_value();
        displayLEDs(adcValue);
    }
}
