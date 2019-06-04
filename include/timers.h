#ifndef TIMERS_H_
#define TIMERS_H_

#include "gpio.h"

inline void delay_miliseconds(uint16_t delay){
    TA2CTL = (TASSEL__ACLK | MC__UP | ID__8);

    TA2EX0 = TAIDEX_4;

    TA2CCR0 = delay;

    SET_REG(TA2CTL, TACLR);

    while(!READ_REG(TA2CCTL0,CCIFG));
    CLEAR_REG(TA2CCTL0, CCIFG);
}

inline void delay_microseconds(uint16_t delay){
    TA2CTL = (TASSEL__SMCLK | MC__UP);

    TA2CCR0 = delay;

    SET_REG(TA2CTL, TACLR);

    while(!READ_REG(TA2CCTL0,CCIFG));
    CLEAR_REG(TA2CCTL0, CCIFG);
}



#endif /* TIMERS_H_ */
