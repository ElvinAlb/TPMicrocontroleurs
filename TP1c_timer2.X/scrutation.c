#include "scrutation.h"

void scrutation(void){
    while (1) {
        LATD = 0x01;
        LATB = 0x00;
        delay_with_timer2();
        while (LATD != 0x08) {
            LATD <<= 1;
            delay_with_timer2();
        }
        LATD = 0x00;
        LATB = 0x01;
        delay_with_timer2();
        while (LATB != 0x08) { // Pour couvrir toutes les LEDs D5-D8
            LATB <<= 1;
            delay_with_timer2();
        }
        LATB = 0x00;
    }
}

void delay_with_timer2(void) {
    // Réinitialisation du compteur du Timer2 et attente de débordement
    for(int i=0;i<125;i++){
        while (!PIR1bits.TMR2IF);
        PIR1bits.TMR2IF = 0;
    }
}