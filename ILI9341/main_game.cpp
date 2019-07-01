#include "hwlib.hpp"
#include "ILI9341_buffered.hpp"

void blinkUntilPressed (hwlib::terminal_from & cdisplay, ili9341 & tft, hwlib::pin_in & but1, hwlib::pin_in & but2, const xy & loc, char toPrint)
{
    while (true)
    {
        cdisplay.cursor_set (loc);
        cdisplay.putc (toPrint);

        for (uint8_t i = 0; i < 250; i++)
        {
            but1.refresh ();
            but2.refresh ();

            if (but1.read () || but2.read ())
            {
                tft.clearPart (16 * loc.x, 16 * loc.y, 16 * (loc.x + 1), 16 * (loc.y + 1));
                return;
            }

            hwlib::wait_ms (1);
        }

        tft.clearPart (16 * loc.x, 16 * loc.y, 16 * (loc.x + 1), 16 * (loc.y + 1));

        for (uint8_t i = 0; i < 250; i++)
        {
            but1.refresh ();
            but2.refresh ();

            if (but1.read () || but2.read ())
            {
                return;
            }

            hwlib::wait_ms (1);
        }
    }
}

void printWinMessageAndWait (hwlib::terminal_from & cdisplay, hwlib::pin_in & but1, hwlib::pin_in & but2, char toPrint)
{
    cdisplay.cursor_set (xy (0, 0));

    cdisplay.putc (toPrint);
    cdisplay.putc (' ');
    cdisplay.putc ('h');
    cdisplay.putc ('e');
    cdisplay.putc ('e');
    cdisplay.putc ('f');
    cdisplay.putc ('t');
    
    cdisplay.cursor_set (xy (0, 2));

    cdisplay.putc ('g');
    cdisplay.putc ('e');
    cdisplay.putc ('w');
    cdisplay.putc ('o');
    cdisplay.putc ('n');
    cdisplay.putc ('n');
    cdisplay.putc ('e');
    cdisplay.putc ('n');
    cdisplay.putc ('!');

    while (true)
    {
        but1.refresh ();
        but2.refresh ();

        if (but1.read () || but2.read ())
        {
            return;
        }
    }
}

int main(void)
{
    auto tft_reset = hwlib::target::pin_out (hwlib::target::pins::d8);
    auto tft_dc = hwlib::target::pin_out (hwlib::target::pins::d9);
    auto tft_cs = hwlib::target::pin_out (hwlib::target::pins::d10);
    auto tft_mosi = hwlib::target::pin_out (hwlib::target::pins::d11);
    auto tft_clk = hwlib::target::pin_out (hwlib::target::pins::d13);

    auto but_select = hwlib::target::pin_in (hwlib::target::pins::d2);
    auto but_confirm = hwlib::target::pin_in (hwlib::target::pins::d3);

    auto spi = hwlib::spi_bus_bit_banged_sclk_mosi_miso (tft_clk, tft_mosi, hwlib::pin_in_dummy);

    auto tft1 = ili9341 (spi, tft_reset, tft_dc, tft_cs);

    tft1.setRotation (true);

    WDT->WDT_MR = WDT_MR_WDDIS;

    auto font = hwlib::font_default_16x16 ();
    auto display = hwlib::terminal_from (tft1, font);

    uint8_t cursor = 0;

    uint8_t griddata [9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //0 is nothing, 1 is X and 2 is O

    bool turn = false; //false is X, true is O

    const xy charlocation [9] = {xy (2, 3), xy (7, 3), xy (12, 3), xy (2, 9), xy (7, 9), xy (12, 9), xy (2, 16), xy (7, 16), xy (12, 16)};

    line hl1 (xy (80, 0), xy (80, 320));
    hl1.draw (tft1);

    line hl2 (xy (160, 0), xy (160, 320));
    hl2.draw (tft1);

    line vl1 (xy (0, 107), xy (240, 107));
    vl1.draw (tft1);

    line vl2 (xy (0, 214), xy (240, 214));
    vl2.draw (tft1);

    while (true)
    {
        while (griddata [cursor] != 0)
        {
            if (cursor > 8)
            {
                cursor = 0;
            }
            else
            {
                cursor++;
            }
        }
        
        if (turn)
        {
            blinkUntilPressed (display, tft1, but_select, but_confirm, charlocation [cursor], 'O');
        }
        else
        {
            blinkUntilPressed (display, tft1, but_select, but_confirm, charlocation [cursor], 'X');
        }

        but_select.refresh ();
        but_confirm.refresh ();

        if (but_select.read ())
        {
            cursor++;

            hwlib::wait_ms (50);
        }

        if (but_confirm.read ())
        {
             if (turn)
            {
                display.cursor_set (charlocation [cursor]);
                display.putc ('O');
                griddata [cursor] = 2;
                turn = false;
            }
            else
            {
                display.cursor_set (charlocation [cursor]);
                display.putc ('X');
                griddata [cursor] = 1;
                turn = true;
            }
            cursor = 0;

            hwlib::wait_ms (50);
        }

        if 
        (
            (griddata [0] == 1 && griddata [3] == 1 && griddata [6] == 1) ||
            (griddata [1] == 1 && griddata [4] == 1 && griddata [7] == 1) ||
            (griddata [2] == 1 && griddata [5] == 1 && griddata [8] == 1) ||
            (griddata [0] == 1 && griddata [1] == 1 && griddata [2] == 1) ||
            (griddata [3] == 1 && griddata [4] == 1 && griddata [5] == 1) ||
            (griddata [6] == 1 && griddata [7] == 1 && griddata [8] == 1) ||
            (griddata [0] == 1 && griddata [4] == 1 && griddata [8] == 1) ||
            (griddata [2] == 1 && griddata [4] == 1 && griddata [6] == 1) 
        )
        {
            tft1.clear ();

            printWinMessageAndWait (display, but_confirm, but_select, 'X');

            cursor = 0;
            turn = false; //winner gets to start

            for (uint8_t i = 0; i < 9; i++)
            {
                griddata [i] = 0;
            }

            tft1.clear ();

            hl1.draw (tft1);
            hl2.draw (tft1);
            vl1.draw (tft1);
            vl2.draw (tft1);
        }
        else if 
        (
            (griddata [0] == 2 && griddata [3] == 2 && griddata [6] == 2) ||
            (griddata [1] == 2 && griddata [4] == 2 && griddata [7] == 2) ||
            (griddata [2] == 2 && griddata [5] == 2 && griddata [8] == 2) ||
            (griddata [0] == 2 && griddata [1] == 2 && griddata [2] == 2) ||
            (griddata [3] == 2 && griddata [4] == 2 && griddata [5] == 2) ||
            (griddata [6] == 2 && griddata [7] == 2 && griddata [8] == 2) ||
            (griddata [0] == 2 && griddata [4] == 2 && griddata [8] == 2) ||
            (griddata [2] == 2 && griddata [4] == 2 && griddata [6] == 2) 
        )
        {
            tft1.clear ();

            printWinMessageAndWait (display, but_confirm, but_select, 'O');

            cursor = 0;
            turn = true; //winner gets to start

            for (uint8_t i = 0; i < 9; i++)
            {
                griddata [i] = 0;
            }

            tft1.clear ();

            hl1.draw (tft1);
            hl2.draw (tft1);
            vl1.draw (tft1);
            vl2.draw (tft1);
        }
        else if 
        (
            griddata [0] != 0 && griddata [1] != 0 && griddata [2] != 0 &&
            griddata [3] != 0 && griddata [4] != 0 && griddata [5] != 0 &&
            griddata [6] != 0 && griddata [7] != 0 && griddata [8] != 0
        )
        {
            cursor = 0;
            turn = true; //winner gets to start

            for (uint8_t i = 0; i < 9; i++)
            {
                griddata [i] = 0;
            }

            tft1.clear ();

            hl1.draw (tft1);
            hl2.draw (tft1);
            vl1.draw (tft1);
            vl2.draw (tft1);
        }

        if (cursor > 8)
        {
            cursor = 0;
        }
    }
}