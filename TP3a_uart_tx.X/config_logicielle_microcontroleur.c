/*
 * File:   config_logicielle_microcontroleur.c
 * Author: edche
 *
 * Created on February 11, 2025, 9:28 AM
 */


#include <xc.h>
#include "configbits.h"
#include "config_logicielle_microcontroleur.h"

void assign_pins(){
        // Assignation des pins de réception (RX) et de transmission (TX)
    RC6PPS = 0b10100;
    RXPPS = 0b10111;
}

void config_pins(){
    // RC6 en sortie et RC7 en entrée
    TRISCbits.TRISC7 = 1;
    ANSELCbits.ANSC7 = 0;
    ANSELCbits.ANSC6 = 0;

    //passer l'entrée en numérique
    TRISCbits.TRISC6 = 0;
    LATC = 0b10000000;
}

void transmission_speed(){
    TX1STAbits.SYNC = 0; //mode asynchrone
    TX1STAbits.BRGH = 0; //débit en bauds faible
    BAUD1CONbits.BRG16 = 1; //choix du 16 bits
    
    // BRG : Baud Rate Generator
    // Determination de la période
    // n = ((Fosc / Baud Rate) / 16) - 1
    // n = 51.08 -> [SP1BRGH:SP1BRGL] = 51
    SP1BRGH = 0; //registre pas nécessaire
    SP1BRGL = 0b00110011;    
}

void activate_eusart(){
    RC1STAbits.SPEN = 1; // Activation des pins
    RC1STAbits.CREN = 1; //Activation du receiver
    TX1STAbits.TXEN = 1; //Activation du transmitter
}

void use_eusart(){
    
}

void config_logicielle(){
    assign_pins();
    config_pins();
    transmission_speed();
    activate_eusart();
}