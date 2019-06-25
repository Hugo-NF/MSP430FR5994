#ifndef LCD_H
#define LCD_H

#include "i2c.h"
#include "timers.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define LCD_WAIT_DELAY 2
#define LCD_BL 0x08
#define LCD_EN 0x04
#define LCD_RW 0x02
#define LCD_RS 0x01

#define LCD_INIT_BYTE           0x30
#define LCD_BUS_WIDTH_4BIT      0x20
#define LCD_BUS_WIDTH_8BIT      0x30
#define LCD_CLEAR               0x01
#define LCD_HOME                0x02
#define LCD_ON                  0x0C
#define LCD_OFF                 0x08
#define LCD_LINE1               0x80
#define LCD_LINE2               0xC0
#define LCD_LINE3               0x94
#define LCD_LINE4               0xD4
#define LCD_CURSOR_OFF          0x0C
#define LCD_UNDERLINE_ON        0x0E
#define LCD_BLINK_CURSOR_ON     0x0F
#define LCD_MOVE_CURSOR_LEFT    0x10
#define LCD_MOVE_CURSOR_RIGHT   0x14
#define LCD_SHIFT_LEFT          0x18
#define LCD_SHIFT_RIGHT         0x1E

#define LCD_DISPLAY_ON_CURSOR_OFF               0x0C
#define LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF    0x08
#define LCD_4BITS_2LINES_5x8FONT                0x28
#define LCD_INCREMENT_NO_SHIFT                  0x06

#define LO_NIBBLE(byte) (((byte) << 4) & 0xF0)
#define HI_NIBBLE(byte) ((byte) & 0xF0)

#define NO_LINES                2
#define LEN_LINE                16

volatile uint8_t lcd_address;
unsigned int lcd_UCBx;
char lcd_buffer[NO_LINES][LEN_LINE];

void lcd_init(unsigned char address, unsigned int eUSCI_Bx, int SDA_pin, int SCL_pin, int prescale);
void lcd_write_command(unsigned char data, unsigned char cmdtype);
void lcd_write_char(unsigned char data);
void lcd_write_literal(char *string);
void lcd_printf(uint8_t line, const char *format, ...);
void lcd_set_position(unsigned char row, unsigned char column);

#endif
