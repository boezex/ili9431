#include "hwlib.hpp"
#include "ILI9341_buffered.hpp"

// no timing included in this test due to inconsistent results when using the hwlib::now_us() for timing.

int main(void)
{
  auto tft_reset = hwlib::target::pin_out(hwlib::target::pins::d8);
  auto tft_dc = hwlib::target::pin_out(hwlib::target::pins::d9);
  auto tft_cs = hwlib::target::pin_out(hwlib::target::pins::d10);
  auto tft_mosi = hwlib::target::pin_out(hwlib::target::pins::d11);
  auto tft_clk = hwlib::target::pin_out(hwlib::target::pins::d13);

  auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso(tft_clk, tft_mosi, hwlib::pin_in_dummy);

  auto tft1 = ili9341(spi, tft_reset, tft_dc, tft_cs);

  tft1.setRotation (true);

  WDT->WDT_MR = WDT_MR_WDDIS;

  // wait for the PC console to start
  hwlib::wait_ms(500);

  auto font = hwlib::font_default_16x16();
  auto display = hwlib::terminal_from(tft1, font);

  hwlib::cout << "Testing the ILI9341 library ..." << "\n\n";

  hwlib::cout << "Printing X-signs on the screen" << "\n\n";

  for (uint16_t i = 0; i < 15; i++)
  {
    for (uint16_t j = 0; j < 20; j++)
    {
      display.cursor_set (xy (i, j));
      display.putc ('X');
    }
  }

  hwlib::wait_ms (5000);

  tft1.clear ();

  hwlib::cout << "Printing six lines on the screen" << "\n\n";

  line hl1 (xy (80, 0), xy (80, 320));
  hl1.draw (tft1);

  line hl2 (xy (160, 0), xy (160, 320));
  hl2.draw (tft1);

  line vl1 (xy (0, 107), xy (240, 107));
  vl1.draw (tft1);

  line vl2 (xy (0, 214), xy (240, 214));
  vl2.draw (tft1);

  line diag1 (xy (0, 0), xy (240, 320));
  diag1.draw (tft1);

  line diag2 (xy (240, 0), xy (0, 320));
  diag2.draw (tft1);

  hwlib::wait_ms (5000);

  tft1.clear ();

  hwlib::cout << "Printing the screen totally white" << "\n\n";

  for (uint8_t i = 0; i < 240; i++)
  {
    for (uint16_t j = 0; j < 320; j++)
    { 
      tft1.setPixel (i, j);
    }
  }

  hwlib::cout << "End of the test" << "\n\n";
}