/*
   LCDST7032SPI.cpp  - Library for SPI-type LCDs

   Created by Leonardo Urrego @trecetp, 2016

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef LCDST7032SPI_H
#define LCDST7032SPI_H

#include "Arduino.h"
#include <SPI.h>
#include "Print.h"

// COMMANDS
#define _LCD_CLEARDISPLAY_          0x01      // Write "20H" to DDRAM. and set DDRAM address to "00H" from AC
#define _LCD_RETURNHOME_            0x02      // SET DDRAM address to "00H" from AC and return cursor to its original position if shifted. The contents of DDRAM are not changed.

#define _LCD_ENTRYMODESET_          0x04      // SETS cursor move direction and specifies display shift. These operations are performed during data write and read.
// flags for display entry mode
#define _LCD_ENTRYRIGHT_            0x00
#define _LCD_ENTRYLEFT_             0x02
#define _LCD_ENTRYSHIFTINCREMENT_   0x01
#define _LCD_ENTRYSHIFTDECREMENT_   0x00

#define _LCD_DISPLAYCONTROLSET_     0x08      // SETS: entire display on/off, cursor on/off, cursor position on/off
// flags for display control set
#define _LCD_DISPLAYON_             0x04
#define _LCD_DISPLAYOFF_            0x00
#define _LCD_CURSORON_              0x02
#define _LCD_CURSOROFF_             0x00
#define _LCD_BLINKON_               0x01
#define _LCD_BLINKOFF_              0x00

#define _LCD_FUNCTIONSET_           0x20      // SETS: interface data is 8/4 bits, number of line is 2/1, double height font, instruction table select.
// flags for function set
#define _LCD_8BITMODE_              0x10
#define _LCD_4BITMODE_              0x00
#define _LCD_2LINE_                 0x08
#define _LCD_1LINE_                 0x00
#define _LCD_5x10DOTS_              0x04
#define _LCD_5x8DOTS_               0x00
#define _LCD_INSTRUCTIONTABLE_1_    0x01
#define _LCD_INSTRUCTIONTABLE_0_    0x00

#define _LCD_SETDDRAM_ADDR_         0x80      // SET DDRAM address in address counter

//=== INSTRUCTION TABLE 0 (IS=0)
#define _LCD_CURSORSHIFTSET_        0x10      // SET cursor moving and display shift control bit, and the direction, without changing DDRAM data.
// flags for display/cursor shift
#define _LCD_DISPLAYMOVE_           0x08
#define _LCD_CURSORMOVE_            0x00
#define _LCD_MOVERIGHT_             0x04
#define _LCD_MOVELEFT_              0x00

#define _LCD_SETCGRAMADDR_          0x40      // SET CGRAM address in address counter

//=== INSTRUCTION TABLE 1 (IS=1)
#define _LCD_BIASINTOSCSET_         0x10      // SET Bias selection / Internal OSC frequency adjust
// flags for Bias selection
#define _LCD_BIAS_1_4_              0x08      // bias will be 1/4
#define _LCD_BIAS_1_5_              0x00      // bias will be 1/5
// flags for Adjust Internal OSC
#define _LCD_OSC_122HZ_             0x00      // 122Hz@3.0V
#define _LCD_OSC_131HZ_             0x01      // 131Hz@3.0V
#define _LCD_OSC_144HZ_             0x02      // 144Hz@3.0V
#define _LCD_OSC_161HZ_             0x03      // 161Hz@3.0V
#define _LCD_OSC_183HZ_             0x04      // 183Hz@3.0V
#define _LCD_OSC_221HZ_             0x05      // 221Hz@3.0V
#define _LCD_OSC_274HZ_             0x06      // 274Hz@3.0V
#define _LCD_OSC_347HZ_             0x07      // 347Hz@3.0V

#define _LCD_SETICONADDR_           0x40      // SET ICON address in address counter.

#define _LCD_POWER_CONTROL_         0x56
#define _LCD_POWICONCONTRASTHSET_   0x50      // SET Power / ICON control / Contrast set(high byte)
// flags Power / ICON control / Contrast set(high byte)
#define _LCD_ICON_ON_               0x08      // ICON display on
#define _LCD_ICON_OFF_              0x00      // ICON display off
#define _LCD_BOOST_ON_              0x04      // booster circuit is turn on
#define _LCD_BOOST_OFF_             0x00      // booster circuit is turn off
#define _LCD_CONTRAST_C5_ON_        0x02
#define _LCD_CONTRAST_C4_ON_        0x01

#define _LCD_FOLLOWERCONTROLSET_    0x60      // SET Follower control
// flags Follower control
#define _LCD_FOLLOWER_ON_           0x08      // internal follower circuit is turn on
#define _LCD_FOLLOWER_OFF_          0x00      // internal follower circuit is turn off
#define _LCD_RAB_1_00_              0x00      // 1+(Rb/Ra)=1.00
#define _LCD_RAB_1_25_              0x01      // 1+(Rb/Ra)=1.25
#define _LCD_RAB_1_50_              0x02      // 1+(Rb/Ra)=1.50
#define _LCD_RAB_1_80_              0x03      // 1+(Rb/Ra)=1.80
#define _LCD_RAB_2_00_              0x04      // 1+(Rb/Ra)=2.00
#define _LCD_RAB_2_50_              0x05      // 1+(Rb/Ra)=2.50
#define _LCD_RAB_3_00_              0x06      // 1+(Rb/Ra)=3.00
#define _LCD_RAB_3_75_              0x07      // 1+(Rb/Ra)=3.75

#define _LCD_CONTRASTSET_           0x70      // Contrast set(low byte)
// flags contrast set (low byte)
#define _LCD_CONTRAST_C3_ON_        0x08
#define _LCD_CONTRAST_C2_ON_        0x04
#define _LCD_CONTRAST_C1_ON_        0x02
#define _LCD_CONTRAST_C0_ON_        0x01


class LCDST7032SPI : public Print {

    public:
    //! Constructor for LCDST7032SPI class.
    /*!
        reset: reset pin
        register_select: RS pin
        cs: chip select pin
    */
    LCDST7032SPI(uint8_t reset, uint8_t register_select, uint8_t cs);

    void init();      // Initially the LCD with the defaults settings
    void home();
    void clear();
    void setCursor(uint8_t, uint8_t);
    void cursor();
    void noCursor();
    void noBlink();
    void blink();
    void noDisplay();
    void display();

    // void write(char data);    // Print a character in the actual address
    virtual size_t write(uint8_t);
    using Print::write;

    private:
    uint8_t _rst, _cs, _rs;
    uint8_t _displayentrymode;
    uint8_t _displayfunction;
    uint8_t _displaycontrol;

    void command(byte uint8_t);
};

#endif
