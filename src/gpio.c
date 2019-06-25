#include "../include/gpio.h"

#ifndef GPIO_PORT_MAPS
const uint16_t port_to_dir[]={
    (uint16_t) &P1DIR,
    (uint16_t) &P2DIR,
    (uint16_t) &P3DIR,
    (uint16_t) &P4DIR,
    (uint16_t) &P5DIR,
    (uint16_t) &P6DIR,
    (uint16_t) &P7DIR,
    (uint16_t) &P8DIR
};

const uint16_t port_to_in[]={
    (uint16_t) &P1IN,
    (uint16_t) &P2IN,
    (uint16_t) &P3IN,
    (uint16_t) &P4IN,
    (uint16_t) &P5IN,
    (uint16_t) &P6IN,
    (uint16_t) &P7IN,
    (uint16_t) &P8IN
};

const uint16_t port_to_out[]={
    (uint16_t) &P1OUT,
    (uint16_t) &P2OUT,
    (uint16_t) &P3OUT,
    (uint16_t) &P4OUT,
    (uint16_t) &P5OUT,
    (uint16_t) &P6OUT,
    (uint16_t) &P7OUT,
    (uint16_t) &P8OUT
};

const uint16_t port_to_ren[]={
    (uint16_t) &P1REN,
    (uint16_t) &P2REN,
    (uint16_t) &P3REN,
    (uint16_t) &P4REN,
    (uint16_t) &P5REN,
    (uint16_t) &P6REN,
    (uint16_t) &P7REN,
    (uint16_t) &P8REN
};

const uint16_t port_to_ies[]={
    (uint16_t) &P1IES,
    (uint16_t) &P2IES,
    (uint16_t) &P3IES,
    (uint16_t) &P4IES,
    (uint16_t) &P5IES,
    (uint16_t) &P6IES,
    (uint16_t) &P7IES,
    (uint16_t) &P8IES
};

const uint16_t port_to_ie[]={
    (uint16_t) &P1IE,
    (uint16_t) &P2IE,
    (uint16_t) &P3IE,
    (uint16_t) &P4IE,
    (uint16_t) &P5IE,
    (uint16_t) &P6IE,
    (uint16_t) &P7IE,
    (uint16_t) &P8IE
};

const uint16_t port_to_ifg[]={
    (uint16_t) &P1IFG,
    (uint16_t) &P2IFG,
    (uint16_t) &P3IFG,
    (uint16_t) &P4IFG,
    (uint16_t) &P5IFG,
    (uint16_t) &P6IFG,
    (uint16_t) &P7IFG,
    (uint16_t) &P8IFG
};

const uint16_t port_to_sel0[]={
    (uint16_t) &P1SEL0,
    (uint16_t) &P2SEL0,
    (uint16_t) &P3SEL0,
    (uint16_t) &P4SEL0,
    (uint16_t) &P5SEL0,
    (uint16_t) &P6SEL0,
    (uint16_t) &P7SEL0,
    (uint16_t) &P8SEL0
};

const uint16_t port_to_sel1[]={
    (uint16_t) &P1SEL1,
    (uint16_t) &P2SEL1,
    (uint16_t) &P3SEL1,
    (uint16_t) &P4SEL1,
    (uint16_t) &P5SEL1,
    (uint16_t) &P6SEL1,
    (uint16_t) &P7SEL1,
    (uint16_t) &P8SEL1
};


#endif //GPIO_PORT_MAPS

inline void setPin(unsigned char pin, unsigned char mode){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *dir = portToDir(port);
    volatile uint8_t *ren = portToRen(port);
    volatile uint8_t *out = portToOut(port);

    switch(mode){
        case OUTPUT:
            *dir |= bit;
            break;
        case INPUT:
            *dir &= ~(bit);
            break;
        case INPUT_PULL_UP:
            *dir &= ~(bit);
            *ren |= bit;
            *out |= bit;
            break;
        case INPUT_PULL_DOWN:
            *dir &= ~(bit);
            *ren |= bit;
            *out &= ~(bit);
            break;
        case PULL_DOWN:
            *ren |= bit;
            *out &= ~(bit);
            break;
        case PULL_UP:
            *ren |= bit;
            *out |= bit;
            break;

        default:
            break;
    }
}

inline void writePin(unsigned char pin, unsigned char value){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *out = portToOut(port);

    if(!value) *out &= ~(bit);
    else       *out |= bit;
}

inline void tooglePin(unsigned char pin){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *out = portToOut(port);

    *out ^= bit;
}

inline uint8_t readPin(unsigned char pin){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *in = portToIn(port);

    return *in & bit;
}

inline void setInterrupt(unsigned char pin, unsigned char mode){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *ies = portToIes(port);
    volatile uint8_t *ie = portToIe(port);

    if(mode == FALLING_EDGE){
        *ies |= bit;
    }else{
        *ies &= ~(bit);
    }

    *ie |= bit;
}

inline void disableInterrupt(unsigned char pin){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *ie = portToIe(port);

    *ie &= ~(bit);
}

inline void selectPin(unsigned char pin, uint8_t function){
    uint8_t bit = Mask(pin);
    uint8_t port = Port(pin);

    volatile uint8_t *sel0 = portToSel0(port);
    volatile uint8_t *sel1 = portToSel1(port);

    switch(function){
    case 0:
        *sel0 &= ~(bit);
        *sel1 &= ~(bit);
        break;
    case 1:
        *sel0 |= bit;
        *sel1 &= ~(bit);
        break;
    case 2:
        *sel0 &= ~(bit);
        *sel1 |= bit;
        break;
    case 3:
        *sel0 |= bit;
        *sel1 |= bit;
        break;
    default:
        break;
    }
}
