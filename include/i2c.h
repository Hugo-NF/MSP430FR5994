#ifndef I2C_H
#define I2C_H

#include <msp430.h>
#include <stdint.h>
#include "gpio.h"

#define UCB0 0
#define UCB1 1
#define UCB2 2
#define UCB3 3

#define ucbToCtl(P) ((volatile uint16_t *) (ucb_to_ctl[P]))
#define ucbToBrw(P) ((volatile uint16_t *) (ucb_to_brw[P]))
#define ucbToI2Csa(P) ((volatile uint16_t *) (ucb_to_i2csa[P]))
#define ucbToStat(P) ((volatile uint16_t *) (ucb_to_stat[P]))
#define ucbToIfg(P) ((volatile uint16_t *) (ucb_to_ifg[P]))
#define ucbToTxbuf(P) ((volatile uint16_t *) (ucb_to_txbuf[P]))

uint8_t TX_data;

void I2C_single_master(unsigned int eUSCI_Bx, int SDA_pin, int SCL_pin, int prescale);
void I2C_transmit(uint8_t slave_address, unsigned int eUSCI_Bx);

#endif
