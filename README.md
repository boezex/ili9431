# ili9431
IPASS project, display library based on ili9341 chip

Depends heavily on the hwlib hardware library by Wouter Van Ooijen. (https://github.com/wovo).

I made two small changes in hwlib to make SPI/image writing on the display MUCH faster.
For Arduino DUE (and probably all other Arduino boards) change the following files:

hwlib/library/core/hwlib-spi.hpp -> comment out line 200 (wait_us( 1 );)

and

hwlib/library/graphics/hwlib-graphics-window.hpp -> change line 106:
from 
for( const auto p : all( size ) ){
to
for( const auto p : all( img.size ) ){
