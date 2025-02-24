/*
 * File:   init_ports.c
 * Author: edche
 *
 * Created on 4 février 2025, 12:17
 */


#include "init_ports.h"

void init_ports(void) {
    TRISD = 0x00; // Configure PORTD en sortie (LEDs D1-D4)
    TRISB = 0x00; // Configure PORTB en sortie (LEDs D5-D8)
    LATD = 0x00;  // Éteint toutes les LEDs de PORTD
    LATB = 0x00;  // Éteint toutes les LEDs de PORTB
}
