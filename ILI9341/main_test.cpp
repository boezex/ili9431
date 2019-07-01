#include "hwlib.hpp"
#include "ILI9341_buffered.hpp"
//#include "ILI9341_window.hpp"

/*void displayString (auto & display, char str[])
{
  for (int i = 0; i < str.size(); i++)
  {
    display.putc(str[i]);
  }
}*/

int main(void)
{
  auto tft_reset = hwlib::target::pin_out(hwlib::target::pins::d8);
  auto tft_dc = hwlib::target::pin_out(hwlib::target::pins::d9);
  auto tft_cs = hwlib::target::pin_out(hwlib::target::pins::d10);
  auto tft_mosi = hwlib::target::pin_out(hwlib::target::pins::d11);
  auto tft_clk = hwlib::target::pin_out(hwlib::target::pins::d13);

  auto rx1 = hwlib::target::pin_out(hwlib::target::pins::d19);
  auto tx1 = hwlib::target::pin_out(hwlib::target::pins::d24);

  auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(tft_clk, tft_mosi, hwlib::pin_in_dummy);

  uart_putc_bit_banged_pin('a', tx1);

  cout << "Dikke BMW jonge" << flush;

  auto tft1 = ili9341(spi, tft_reset, tft_dc, tft_cs);

  tft1.setRotation (true);

  WDT->WDT_MR = WDT_MR_WDDIS;

  // wait for the PC console to start
  hwlib::wait_ms(500);

  auto font = hwlib::font_default_16x16();
  auto display = hwlib::terminal_from(tft1, font);

  display.putc('C');

  display.cursor_set(xy(0, 1));
  //tft1.clear();

  display.putc('H');

  //tft1.clear();

  display.putc('e');
  display.putc('l');
  display.putc('l');
  display.putc('o');
  display.putc(' ');
  display.putc('W');
  display.putc('o');
  display.putc('r');
  display.putc('l');
  display.putc('d');

  display.cursor_set(xy(0, 1));


  display.putc('K');
  display.putc('a');
  display.putc('n');
  display.putc(' ');
  display.putc('i');
  display.putc('e');
  display.putc('m');
  display.putc('a');
  display.putc('n');
  display.putc('d');

  display.cursor_set(xy(0, 2));

  display.putc('m');
  display.putc('i');
  display.putc('j');
  display.putc(' ');
  display.putc('h');
  display.putc('o');
  display.putc('r');
  display.putc('e');
  display.putc('n');

  display.cursor_set(xy(0, 3));

  display.putc('X');

  //tft1.clear();

  tft1.setPixel(0,0);
  tft1.setPixel(0,319);

  circle top(xy(120, 160), 40);
  top.draw(tft1);

  wait_ms(3000);
  tft1.clear();

  display.putc('X');

  for (int i = 0; i < 240; i++)
    {
        for (int j = 0; j < 320; j++)
        {
            tft1.setPixel(i, j);
        }
    }

    tft1.clear();
}