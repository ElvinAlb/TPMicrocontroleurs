#include "configbits.h"
#include "scrutation.h"
#include "init_ports.h"
#include "init_timer.h"



#define _XTAL_FREQ 8000000 // 8 MHz

volatile uint8_t mode = 0;
int compteur = 0;
int main(void) {
    init_ports();
    init_timer2();
    
    while (1){
        
    }

    return 0;
}