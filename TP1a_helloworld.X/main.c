#include "xc.h"
#include "configbits.h"

// D�claration de la fonction de d�lai approximatif
void delai_approx(void);

int main(void) {
    // Configuration des ports comme sorties pour les LEDs
    TRISB = 0x00; // Supposons que les LEDs sont connect�es au port B
    TRISD = 0x00;
    LATB = 0x00;  // Initialisation de l'�tat du port B
    LATD = 0x00;
    while (1) {
                // Allumer les LEDs D1-D4 et �teindre les LEDs D5-D8
        LATB = 0x00;
        LATD = 0x0F;
        delai_approx();
        // Allumer les LEDs D5-D8 et �teindre les LEDs D1-D4
        LATB = 0x0F;
        LATD = 0x00;
        delai_approx();

    }

    return 0;
}

// Impl�mentation de la fonction de d�lai approximatif
void delai_approx(void) {
    // Chaque passage dans la boucle prend environ 0.5�s
    // SOit 200 000 instructions pour 1sec
    for (volatile unsigned long i = 0; i < 200000; ++i) {
    }
}