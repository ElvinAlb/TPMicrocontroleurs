#include "configbits.h"
#define _XTAL_FREQ 8000000 // 8 MHz
int compteur = 0;
char position = 0;
int nb_flag =0;

void setupTimer(void) {
    // T2CON : Timer2 activé, Prescaler 1:16, Postscaler 1:1
    //T2CON = 0b00000110; // Bit7 : - , TOUTPS<3:0> = 0000 (1:1), TMR2ON = 1, T2CKPS<1:0> = 11 (1:16)
    T2CON = 0b00001101;
    T2CONbits.TMR2ON=1;
    T2CONbits.T2CKPS=0b00;
    T2CONbits.T2OUTPS=0b1111;
    PR2 = 124;          // Valeur de période (à ajuster selon le délai souhaité)
    PIR1bits.TMR2IF = 0; // Réinitialise le flag d'interruption du Timer2
    PIE1bits.TMR2IE = 1; // Active l'interruption du Timer2
    PEIE = 1;           //Interruption périphérique
    GIE = 1;            //Interruption globale
    TMR2IE = 1;
}

void setupLEDS(void) {
    TRISD = 0x00; // Configure PORTD en sortie (LEDs D1-D4)
    TRISB = 0x00; // Configure PORTB en sortie (LEDs D5-D8)
    LATD = 0x00;  // Éteint toutes les LEDs de PORTD
    LATB = 0x00;  // Éteint toutes les LEDs de PORTB
}

void __interrupt() ISR(void){
    if(TMR2IF){
        nb_flag = (nb_flag + 1)%125;
        if(nb_flag==0){
            if(position<4){
                LATD = 0x01 << position;
                LATB = 0x00;
            }
            else{
                LATB = 0x01 << (position - 4);
                LATD = 0x00;
            }
            position = (position + 1) % 8;
        }
        TMR2IF = 0;

    }
}

int main(void) {
    setupLEDS();
    setupTimer();
    while (1){
        
    }

    return 0;
}