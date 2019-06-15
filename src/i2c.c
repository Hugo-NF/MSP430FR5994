#include "../include/i2c.h"

#ifndef USCI_B_PORT_MAPS
const uint16_t ucb_to_ctl[]={
    (uint16_t) &UCB0CTLW0,
    (uint16_t) &UCB1CTLW0,
    (uint16_t) &UCB2CTLW0,
    (uint16_t) &UCB3CTLW0
};

const uint16_t ucb_to_brw[]={
    (uint16_t) &UCB0BRW,
    (uint16_t) &UCB1BRW,
    (uint16_t) &UCB2BRW,
    (uint16_t) &UCB3BRW
};

const uint16_t ucb_to_i2csa[]={
    (uint16_t) &UCB0I2CSA,
    (uint16_t) &UCB1I2CSA,
    (uint16_t) &UCB2I2CSA,
    (uint16_t) &UCB3I2CSA
};

const uint16_t ucb_to_stat[]={
    (uint16_t) &UCB0STATW,
    (uint16_t) &UCB1STATW,
    (uint16_t) &UCB2STATW,
    (uint16_t) &UCB3STATW
};

const uint16_t ucb_to_ifg[]={
    (uint16_t) &UCB0IFG,
    (uint16_t) &UCB1IFG,
    (uint16_t) &UCB2IFG,
    (uint16_t) &UCB3IFG
};

const uint16_t ucb_to_txbuf[]={
    (uint16_t) &UCB0TXBUF,
    (uint16_t) &UCB1TXBUF,
    (uint16_t) &UCB2TXBUF,
    (uint16_t) &UCB3TXBUF
};

#endif  //USCI_B_PORT_MAPS

void I2C_single_master(unsigned int eUSCI_Bx, int SDA_pin, int SCL_pin, int prescale) {
    // GPIO Registers configuration
    selectPin(SDA_pin, 1);
    selectPin(SCL_pin, 1);
    setPin(SDA_pin, INPUT_PULL_UP);
    setPin(SCL_pin, INPUT_PULL_UP);

    volatile uint16_t *ctl = ucbToCtl(eUSCI_Bx);
    volatile uint16_t *brw = ucbToBrw(eUSCI_Bx);

    *ctl    = UCSWRST;                          // Enable Software reset
    *ctl    |= UCMST;
    *ctl    |= UCMODE_3;
    *ctl    |= UCSYNC;                          // Setting the interface as I2C master with single master environment, synchronous mode
    *ctl    |= UCSSEL_2;                        // Selecting SMCLK
    *brw    = prescale;                         // Set prescaler - SMCLK/12
    *ctl    &= ~(UCSWRST);                      // Clear Software reset
}

void I2C_transmit(uint8_t slave_address, unsigned int eUSCI_Bx) {
    volatile uint16_t *ctl = ucbToCtl(eUSCI_Bx);
    volatile uint16_t *sa = ucbToI2Csa(eUSCI_Bx);
    volatile uint16_t *stat = ucbToStat(eUSCI_Bx);
    volatile uint16_t *ifg = ucbToIfg(eUSCI_Bx);
    volatile uint16_t *tx = ucbToTxbuf(eUSCI_Bx);

    *sa = slave_address;                                // Setting slave address

    while(READ_REG(*stat, UCBBUSY) !=  0);              // Verifying SDA availability

    *ctl |= UCTR;
    *ctl |= UCTXSTT;                                    // Transmit I2C Start Condition

    while(READ_REG(*ifg, UCTXIFG0) == 0);                // Wait for TXBUFF Interruption (SCL is hold)

    *tx = TX_data;                              // Copy byte to TXBUFF

    while(READ_REG(*ifg, UCTXIFG0) != 0);               // Wait for Slave Answer (Can be ACK or NACK)

    *ctl |= UCTXSTP;                            // Transmit I2C Stop Condition
    while(READ_REG(*ctl, UCTXSTP) != 0);               // Wait for Stop Condition
}
