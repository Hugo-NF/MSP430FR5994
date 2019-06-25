#include <msp430.h> 
#include "../include/gpio.h"
#include "../include/timers.h"
#include "../include/lcd.h"


void main(void) {

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	// Disable the GPIO power-on default high-impedance mode to activate
	// previously configured port settings
    disableHighZ;

    lcd_init(0x27, UCB2, P7_0, P7_1, 10);
    uint8_t a = 12;
    lcd_printf(1, "V1: %d", a);
    lcd_printf(2, "LCD ADDR: 0x%x", lcd_address);


    while(1);
}
