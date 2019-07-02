# ili9431

## Introduction
IPASS project, display library based on ili9341 chip.

The library comes with two examples as well as a test for the display (library). The first example is a simple game, called butter, cheese & eggs. The other example progamme is able to display data from smarthome platform 'domoticz'. However, this is very specific and should be only used to demonstrate the capabilities of the library at the IPASS assessment. Python with libary 'pyserial' is used to pass through the domoticz data to the Arduino DUE, which displays it.

This library heavily depends on the hwlib hardware library by Wouter Van Ooijen. (https://github.com/wovo).

## Changes in hwlib
I made two small changes in hwlib to make SPI/image writing on the display MUCH faster.
For Arduino DUE (and probably all other Arduino boards) change the following files:

**hwlib/library/core/hwlib-spi.hpp -> comment out line 200 (wait_us( 1 );)**<br/>

and<br/>

**hwlib/library/graphics/hwlib-graphics-window.hpp -> change line 106:**<br/>
from<br/>
**for( const auto p : all( size ) ){**<br/>
to<br/>
**for( const auto p : all( img.size ) ){**<br/>

## Files in the 'IlI9341' folder
The two most important files of the library are 'ILI9341_buffered.hpp' and 'ILI9341_buffered.cpp'.

There are 3 'main' files. The default main file is the demo game. To upload one of the other mains (test & smarthome) to the DUE, please rename the current main file to main_game.cpp, and rename the file you would like to upload to main.cpp.

## Miscellaneous comments on the project
- The display writing would have been much faster if hwlib supported the hardware SPI interface on the DUE boards. The current SPI clock is around 300 kHz, but the hardware on the DUE is reported to handle up to 16 MHz.
- The display.clear() function(s) are not as optimised as I'd have liked. Mainly because the stack provided by BMPTK is not big enough to hold all the display's pixels in memory.
