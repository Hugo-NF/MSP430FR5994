#include "../include/lcd.h"
#include "../include/timers.h"


void lcd_init(unsigned char address, unsigned int eUSCI_Bx, int SDA_pin, int SCL_pin, int prescale){
    lcd_address = address;
    I2C_single_master(eUSCI_Bx, SDA_pin, SCL_pin, prescale);

    delay_miliseconds(15);
    lcd_write_command(LCD_INIT_BYTE, 0);

    delay_miliseconds(5);
    lcd_write_command(LCD_INIT_BYTE, 0);

    delay_microseconds(150);
    lcd_write_command(LCD_INIT_BYTE, 0);
    lcd_write_command(LCD_BUS_WIDTH_4BIT, 0);

    lcd_write_command(LCD_4BITS_2LINES_5x8FONT, 1);
    lcd_write_command(LCD_DISPLAY_OFF_CURSOR_OFF_BLINK_OFF, 1);
    lcd_write_command(LCD_CLEAR, 1);
    lcd_write_command(LCD_INCREMENT_NO_SHIFT, 1);
    lcd_write_command(LCD_DISPLAY_ON_CURSOR_OFF, 1);
}

void lcd_write_command(unsigned char data, unsigned char cmdtype) {

    TX_data = (HI_NIBBLE(data) | LCD_BL) | LCD_EN;
    I2C_transmit(lcd_address, UCB2);

    TX_data = (HI_NIBBLE(data) | LCD_BL) & ~LCD_EN;
    I2C_transmit(lcd_address, UCB2);

    if (cmdtype) {
        TX_data = (LO_NIBBLE(data) | LCD_BL) | LCD_EN;
        I2C_transmit(lcd_address, UCB2);
        TX_data = (LO_NIBBLE(data) | LCD_BL) | ~LCD_EN;
        I2C_transmit(lcd_address, UCB2);
    }
    if(data == LCD_CLEAR || data == LCD_HOME)
        delay_miliseconds(2);
    else
        delay_microseconds(50);
}

void lcd_write_char(unsigned char data) {

    TX_data = (HI_NIBBLE(data) | LCD_BL | LCD_RS) | LCD_EN;
    I2C_transmit(lcd_address, UCB2);

    TX_data = (HI_NIBBLE(data) | LCD_BL | LCD_RS) & ~LCD_EN;
    I2C_transmit(lcd_address, UCB2);

    TX_data = (LO_NIBBLE(data) | LCD_BL | LCD_RS) | LCD_EN;
    I2C_transmit(lcd_address, UCB2);

    TX_data = (LO_NIBBLE(data) | LCD_BL | LCD_RS) & ~LCD_EN;
    I2C_transmit(lcd_address, UCB2);
}

void lcd_write_literal(char *string){
    while (*string != '\0')
            lcd_write_char(*string++);
}

void lcd_printf(uint8_t line, const char *format, ...) {
    va_list args;
    va_start (args, format);
    vsnprintf(lcd_buffer[line-1], LEN_LINE, format, args);
    if(line == 2)
        lcd_set_position(2, 1);
    lcd_write_literal(lcd_buffer[line-1]);
    va_end(args);
    lcd_set_position(1, 1);
}

void lcd_set_position(unsigned char row, unsigned char column) {
    switch(row) {
        case 1: 
            lcd_write_command(LCD_LINE1 + (column - 1), 1);
            break;
        case 2:
            lcd_write_command(LCD_LINE2 + (column - 1), 1);
            break;
        case 3:
            lcd_write_command(LCD_LINE3 + (column - 1), 1);
            break;
        case 4:
            lcd_write_command(LCD_LINE4 + (column - 1), 1);
            break;
        default:
            lcd_write_command(LCD_LINE1 + (column - 1), 1);
    }
}
