LCDST7032SPI
============

This library allows an Arduino board to control LiquidCrystal displays (LCDs) based on the `ST7032` chipset (SPI interface, plus `RS`, `RST` signals).

Support All Arduino-type devices.

Tested with NewHaven displays (eg. NHD-C0216CZ-FSW-FBW-3V3)

The LCD is controled by 5 pins:
  - Reset
  - RS
  - CS
  - SCK
  - MOSI

The RESET pin, Register Select (RS) and Chip Select (CS) can be defined by the user in the instance of the Object LCDST7032SPI. The pins SCK and MOSI are the standar pins used by the SPI library (SPI.h)

## USE of Library

Include the headers:
```
#include "LCDST7032SPI.h"
#include "SPI.h"
```

Instance a new object:
```
LCDST7032SPI myLCD(_PIN_RST_, _PIN_RS_, _PIN_CS_);  // Pins MOSI and SCK are the Arduino Standar
```

Inicialize the LCD with the standar config (inside the setup):
```
myLCD.init();
```

Getting Starter (Show a message):
```
myLCD.print("Hello Word",0);  // The second parameter is the address reference of the LCD
```


## CREDITS

This Library is based on the work of @JQIamo/LCD-arduino, @tomozh/arduino_ST7032 and the original Arduino liquidCrystal library.


## == LICENSE ==

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
