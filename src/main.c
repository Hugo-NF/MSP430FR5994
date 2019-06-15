#include <msp430.h> 
#include "../include/gpio.h"
#include "../include/timers.h"
#include "../include/lcd.h"


void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
    disableHighZ;

    setPin(P1_0, OUTPUT);
    setPin(P1_1, OUTPUT);
    writePin(P1_1, LOW);

    lcd_init(0x27);

    while(1);
}
