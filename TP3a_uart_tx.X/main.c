/*
 * File:   main.c
 * Author: edche
 *
 * Created on February 11, 2025, 9:24 AM
 */


#include <xc.h>
#include "configbits.h"
#include "config_logicielle_microcontroleur.h"
#include <stdio.h>

#define _XTAL_FREQ 8000000

// Fonction pour envoyer un caract�re via UART
void UART_SendChar(char c) {
    while (!TXIF);  // Attendre que le buffer de transmission soit pr�t
    TX1REG = c;      // Envoyer le caract�re
}

// Fonction pour envoyer une cha�ne de caract�res
void UART_SendString(const char *table, int len) {
    for(int i=0;i<len;i++){
        UART_SendChar(table[i]);
    }
    /*
    while (*str) { //tant qu'on a un caract�re
        UART_SendChar(*str); //envoyer le caract�re
        str++; //incr�menter le pointeur
    }
    */
}

// Programme principal
void main(void) {
    config_logicielle();          // Initialiser l'UART
    const char table[] = "Hello, World !\n\r";
    int len = sizeof(table)-1;

    while (1) {
        UART_SendString(table,len);  // Envoyer la cha�ne
        __delay_ms(1000);  // Attendre 1 seconde avant le prochain envoi
    }
}