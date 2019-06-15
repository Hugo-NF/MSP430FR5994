#include "../include/lcd.h"

void lcd_init(unsigned char address){
    lcd_address = address;
    I2C_single_master(UCB2, P7_0, P7_1, 8);

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

    writePin(P1_0, HIGH);
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

void lcd_write_string(char *s) {
    while (*s != '\0')
        lcd_write_char(*s++);
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
