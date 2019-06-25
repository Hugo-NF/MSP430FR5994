#ifndef GPIO_H_
#define GPIO_H_

#include <msp430.h>
#include <stdint.h>

/**
 * Registers manipulation macros:
 * SET_REG(reg, bit)
 *      Turns a bit into '1'.
 *      Bitwise OR between 'reg' and 'bit'
 * CLEAR_REG(reg, bit)
 *      Turns a bit into '0'
 *      Bitwise AND between 'reg' and NOT 'bit'
 * TOOGLE_REG(reg, bit)
 *      Inverts bit value
 *      Bitwise XOR between 'reg' and 'bit'
 * READ_REG(reg, bit)
 *      Read the value of a bit into reg
 *      Bitwise AND between 'reg' and 'bit'
 * */
#define SET_REG(reg, bit)      (reg |= bit)
#define CLEAR_REG(reg, bit)    (reg &= ~(bit))
#define TOOGLE_REG(reg, bit)   (reg ^= bit)
#define READ_REG(reg, bit)     (reg & bit)

/**
 * Macro to Enable GPIO ports
 * Disable the GPIO power-on default high-impedance mode to activate previously configured port settings
 * */
#define disableHighZ           (PM5CTL0 &= ~LOCKLPM5)

/**
 * Macro name definitions to logical levels, aiming to provide better semantic understanding of the code
 * */
#define HIGH    1
#define LOW     0

/**
 * Macro name definitions to GPIO modes, aiming to provide better semantic understanding of the code
 * */
#define OUTPUT          0
#define INPUT           1
#define INPUT_PULL_UP   2
#define INPUT_PULL_DOWN 3
#define PULL_UP         4
#define PULL_DOWN       5

/**
 * Macro name definitions to transition borders, aiming to provide better semantic understanding of the code
 * */
#define RISING_EDGE 0
#define FALLING_EDGE 1

/**
 * Macro name definitions to port numbers
 * Use these macros to refer to a port when calling a function
 * */
#define P1  0
#define P2  1
#define P3  2
#define P4  3
#define P5  4
#define P6  5
#define P7  6
#define P8  7

/**
 * Macro name definitions to pin numbers
 * Use these macros to refer to a pin when calling a function
 * */
#define P1_0    0
#define P1_1    1
#define P1_2    2
#define P1_3    3
#define P1_4    4
#define P1_5    5
#define P1_6    6
#define P1_7    7
#define P2_0    8
#define P2_1    9
#define P2_2    10
#define P2_3    11
#define P2_4    12
#define P2_5    13
#define P2_6    14
#define P2_7    15
#define P3_0    16
#define P3_1    17
#define P3_2    18
#define P3_3    19
#define P3_4    20
#define P3_5    21
#define P3_6    22
#define P3_7    23
#define P4_0    24
#define P4_1    25
#define P4_2    26
#define P4_3    27
#define P4_4    28
#define P4_5    29
#define P4_6    30
#define P4_7    31
#define P5_0    32
#define P5_1    33
#define P5_2    34
#define P5_3    35
#define P5_4    36
#define P5_5    37
#define P5_6    38
#define P5_7    39
#define P6_0    40
#define P6_1    41
#define P6_2    42
#define P6_3    43
#define P6_4    44
#define P6_5    45
#define P6_6    46
#define P6_7    47
#define P7_0    48
#define P7_1    49
#define P7_2    50
#define P7_3    51
#define P7_4    52
#define P7_5    53
#define P7_6    54
#define P7_7    55
#define P8_0    56
#define P8_1    57
#define P8_2    58

/**
 * Macro definitions to retrieve addresses from GPIO port map
 * DO NOT use these directly, internal use only
 * */
#define Port(Pin)    (Pin >> 3)
#define Mask(Pin)    (1 << (Pin & 7))
#define portToDir(P) ((volatile uint8_t *) (port_to_dir[P]))
#define portToIn(P) ((volatile uint8_t *) (port_to_in[P]))
#define portToOut(P) ((volatile uint8_t *) (port_to_out[P]))
#define portToRen(P) ((volatile uint8_t *) (port_to_ren[P]))
#define portToIes(P) ((volatile uint8_t *) (port_to_ies[P]))
#define portToIe(P) ((volatile uint8_t *) (port_to_ie[P]))
#define portToIfg(P) ((volatile uint8_t *) (port_to_ifg[P]))
#define portToSel0(P) ((volatile uint8_t *) (port_to_sel0[P]))
#define portToSel1(P) ((volatile uint8_t *) (port_to_sel1[P]))

/**
 *  \fn inline void setPin(unsigned char pin, unsigned char mode);
 *  \brief Configures a pin to a GPIO mode
 *  \param pin: PIN number
 *  \param mode: Desired GPIO mode (OUTPUT, INPUT, INPUT_PULL_UP, INPUT_PULL_DOWN, PULL_UP, PULL_DOWN)
 *  \warning: Use macro definition to get the correct numbers
 * */
inline void setPin(unsigned char pin, unsigned char mode);

/**
 *  \fn inline void writePin(unsigned char pin, unsigned char value);
 *  \brief Write a logical level to a pin
 *  \param pin: PIN number
 *  \param mode: Logical level to be written (HIGH, LOW)
 *  \warning: Pin must be configured previously.
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline void writePin(unsigned char pin, unsigned char value);

/**
 *  \fn inline void tooglePin(unsigned char pin);
 *  \brief Inverts the logical level of a pin
 *  \param pin: PIN number
 *  \warning: Pin must be configured previously.
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline void tooglePin(unsigned char pin);

/**
 *  \fn inline uint8_t readPin(unsigned char pin);
 *  \brief Reads the logical level of a pin
 *  \param pin: PIN number
 *  \return Logical level of the pin, can be 0 (LOW) or 1 (HIGH)
 *  \warning: Pin must be configured previously.
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline uint8_t readPin(unsigned char pin);

/**
 *  \fn inline void setInterrupt(unsigned char pin, unsigned char mode);
 *  \brief Enables an interruption of a pin
 *  \param pin: PIN number
 *  \param mode: Transition border desired for the interruption, can be (RISING_EDGE) or (FALLING_EDGE)
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline void setInterrupt(unsigned char pin, unsigned char mode);

/**
 *  \fn inline void disableInterrupt(unsigned char pin);
 *  \brief Disable an previously configured interruption of a pin
 *  \param pin: PIN number
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline void disableInterrupt(unsigned char pin);

/**
 *  \fn inline void selectPin(unsigned char pin, uint8_t function);
 *  \brief Multiplexes a pin to one of it's dedicated functions
 *  \param pin: PIN number
 *  \param function: Number of the dedicated function selection (0: No selection, 1: Primary, 2: Secondary, 3: Tertiary)
 *  \warning: Use macro definition to get the correct numbers.
 * */
inline void selectPin(unsigned char pin, uint8_t function);


#endif /* GPIO_H_ */
