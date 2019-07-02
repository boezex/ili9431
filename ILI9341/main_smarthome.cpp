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

  tft1.setRotation(true);

  WDT->WDT_MR = WDT_MR_WDDIS;

  // wait for the PC console to start
  hwlib::wait_ms(500);

  auto font = hwlib::font_default_16x16();
  auto display = hwlib::terminal_from(tft1, font);

  while (true)
  {

    //======================================== 
    // Daans kamer
    display.cursor_set (xy (0,0));
    char daanskamer[] = "Daans kamer:";
    uint8_t sizekamer = 12;

    for (int i = 0; i < sizekamer; i++)
    {
      display.putc(daanskamer[i]);
    }

    hwlib::cout << "1\n";

    char kamerdata[20];
    uint8_t size_text = 0;

    display.cursor_set(xy(0, 1));

    while (true)
    {
      char in;

      hwlib::cin >> in;

      if (in != '\n')
      {
        kamerdata[size_text] = in;
        size_text++;
      }
      else
      {
        break;
      }
    }

    for (int i = 0; i < size_text; i++)
    {
      display.putc(kamerdata[i]);
    }

    //========================================
    // Schakelaar
    display.cursor_set (xy (0, 3));
    char switchname[] = "Schakelaar:";
    uint8_t sizeswitch = 11;

    for (int i = 0; i < sizeswitch; i++)
    {
      display.putc(switchname[i]);
    }

    hwlib::cout << "2\n";

    char switchdata[20];
    size_text = 0;

    display.cursor_set(xy(0, 4));

    while (true)
    {
      char in;

      hwlib::cin >> in;

      if (in != '\n')
      {
        switchdata[size_text] = in;
        size_text++;
      }
      else
      {
        break;
      }
    }

    for (int i = 0; i < size_text; i++)
    {
      display.putc(switchdata[i]);
    }

    //========================================
    // Woonkamer
    display.cursor_set (xy (0, 6));
    char kamername[] = "Woonkamer:";
    uint8_t sizewoonkamer = 10;

    for (int i = 0; i < sizewoonkamer; i++)
    {
      display.putc(kamername[i]);
    }

    hwlib::cout << "3\n";

    char woonkamerdata[20];
    size_text = 0;

    display.cursor_set(xy(0, 7));

    while (true)
    {
      char in;

      hwlib::cin >> in;

      if (in != '\n')
      {
        woonkamerdata[size_text] = in;
        size_text++;
      }
      else
      {
        break;
      }
    }

    for (int i = 0; i < size_text; i++)
    {
      display.putc(woonkamerdata[i]);
    }

    //========================================
    // CV Set temp
    display.cursor_set (xy (0, 9));
    char cvtempname[] = "CV set temp:";
    uint8_t sizecvtemp = 12;

    for (int i = 0; i < sizecvtemp; i++)
    {
      display.putc(cvtempname[i]);
    }

    hwlib::cout << "4\n";

    char cvtempdata[20];
    size_text = 0;

    display.cursor_set(xy(0, 10));

    while (true)
    {
      char in;

      hwlib::cin >> in;

      if (in != '\n')
      {
        cvtempdata[size_text] = in;
        size_text++;
      }
      else
      {
        break;
      }
    }

    for (int i = 0; i < size_text; i++)
    {
      display.putc(cvtempdata[i]);
    }

    //========================================
    // CV pressure
    display.cursor_set (xy (0, 12));
    char cvpressname[] = "CV pressure:";
    uint8_t sizecvpress = 12;

    for (int i = 0; i < sizecvpress; i++)
    {
      display.putc(cvpressname[i]);
    }

    hwlib::cout << "5\n";

    char cvpressdata[20];
    size_text = 0;

    display.cursor_set(xy(0, 13));

    while (true)
    {
      char in;

      hwlib::cin >> in;

      if (in != '\n')
      {
        cvpressdata[size_text] = in;
        size_text++;
      }
      else
      {
        break;
      }
    }

    for (int i = 0; i < size_text; i++)
    {
      display.putc(cvpressdata[i]);
    }

    hwlib::wait_ms(8000);
    tft1.clear();
  }
}