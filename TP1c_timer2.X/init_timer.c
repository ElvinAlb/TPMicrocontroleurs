#include <xc.h>

void init_timer2(void) {
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