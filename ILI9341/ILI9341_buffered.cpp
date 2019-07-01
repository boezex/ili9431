
//          Copyright Daan Boezeman 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "ILI9341_buffered.hpp"

using namespace hwlib;

ili9341::ili9341 (spi_bus & bus, pin_out & res, pin_out & dc, pin_out & cs):
    window (xy (240, 320)),
    bus (bus),
    res (res),
    dc (dc),
    cs (cs),
    isRotated (false)
    {
        init ();
    }
    

void ili9341::init()
{
    res.write (0);
    wait_ms (1);
    res.write (1);

    wait_ms (20);
    
    send_command8 (ili9341_commands::pw_ctl1, 0x23);
    send_command8 (ili9341_commands::pw_ctl2, 0x10);
    send_command8 (ili9341_commands::vm_ctl1, 0x3E, 0x28);
    send_command8 (ili9341_commands::vm_ctl2, 0x86);
    send_command8 (ili9341_commands::mad_ctl, 0x48);
    send_command8 (ili9341_commands::vscr_sadd, 0x00);
    send_command8 (ili9341_commands::pix_fmt, 0x55);
    send_command8 (ili9341_commands::frm_ctl1, 0x00, 0x18);
    send_command8 (ili9341_commands::dfunc_ctl, 0x08, 0x82, 0x27);
    send_command8 (ili9341_commands::gamma_set, 0x01);
    send_command8 (ili9341_commands::gmc_p, 0x0F, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1, 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00);
    send_command8 (ili9341_commands::gmc_n, 0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1, 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F);
    send_command8 (ili9341_commands::slp_out);
    send_command8 (ili9341_commands::disp_on);

    wait_ms (20);

    set_address_clear (0, 0, tft_h - 1, tft_w - 1);

    for (uint32_t i = 0; i < (76800); i++) //320 * 240 = 76800
    {
        send_data16 (ili9341_colors::black);
    }

    for (uint8_t i = 0; i < 240; i++)
    {
        for (uint8_t j = 0; j < 240; j++)
        {
            is_pixel_written [i] [j] = false;
        }
    }
}

uint16_t ili9341::get_565_color (uint8_t red, uint8_t green, uint8_t blue)
{
    return (((red & 0xf8)<<8) + ((green & 0xfc)<<3) + (blue>>3));
}

void ili9341::write_implementation (xy pos, color pixelcolor)
{
    setPixel (pos.x, pos.y, get_565_color (pixelcolor.red, pixelcolor.green, pixelcolor.blue));
}

void ili9341::send_command8 (ili9341_commands c)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
    t.write (d1);
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
    t.write (d1);
    t.write (d2);
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
    t.write (d1);
    t.write (d2);
    t.write (d3);
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
    t.write (d1);
    t.write (d2);
    t.write (d3);
    t.write (d4);
}

void ili9341::send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14)
{
    dc.write (0);
    auto t = bus.transaction (cs);
    t.write (static_cast <uint8_t> (c));
    dc.write (1);
    t.write (d0);
    t.write (d1);
    t.write (d2);
    t.write (d3);
    t.write (d4);
    t.write (d5);
    t.write (d6);
    t.write (d7);
    t.write (d8);
    t.write (d9);
    t.write (d10);
    t.write (d11);
    t.write (d12);
    t.write (d13);
    t.write (d14);
}

void ili9341::send_data8 (uint8_t data)
{
    dc.write (1);
    auto t = bus.transaction (cs);
    t.write (data);
}

void ili9341::send_data16 (uint16_t data)
{
    send_data8 (data >> 8);
    send_data8 (data);
}

void ili9341::send_data16 (ili9341_colors color)
{
    send_data16 (static_cast <uint16_t> (color));
}

void ili9341::set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{

    if (isRotated)
    {
        x1 = 240 - x1;
        x2 = 240 - x2;
        y1 = 320 - y1;
        y2 = 320 - y2;
    }
    
    send_command8 (ili9341_commands::ca_set);
    send_data16 (x1);
    send_data16 (x2);

    send_command8 (ili9341_commands::pa_set);
    send_data16 (y1);
    send_data16 (y2);

    send_command8 (ili9341_commands::ram_wr);
}

void ili9341::set_address_clear (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{    
    send_command8 (ili9341_commands::ca_set);
    send_data16 (x1);
    send_data16 (x2);

    send_command8 (ili9341_commands::pa_set);
    send_data16 (y1);
    send_data16 (y2);

    send_command8 (ili9341_commands::ram_wr);
}

void ili9341::clear ()
{
    for (uint8_t i = 0; i < 240; i++)
    {
        for (uint8_t j = 0; j < 240; j++)
        {
            if (is_pixel_written [i] [j])
            {
                clearPixel (i, j);
                is_pixel_written [i] [j] = false;
            }
        }
    }

    if (isRotated)
    {
        set_address_clear (0, 0, tft_h - 1, 80);
    }
    else
    {
        set_address_clear (0, 240, tft_h - 1, tft_w - 1);
    }
    
    for (uint32_t i = 0; i < 19200; i++) //80 * 240 = 19200
    {
        send_data16(ili9341_colors::black);
    }
}

void ili9341::clear_dumb ()
{
    set_address_clear (0, 0, tft_h - 1, tft_w - 1);
    for (uint8_t i = 0; i < 240; i++)
    {
        for (uint8_t j = 0; j < 240; j++)
        {
            is_pixel_written [i] [j] = false;
            send_data16 (ili9341_colors::black);
        }
        for (uint16_t k = 240; k < 320; k++)
        {
            send_data16 (ili9341_colors::black);
        }
    }
}

void ili9341::clearPart (uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end)
{
    for (uint16_t i = x_start; i < x_end; i++)
    {
        for (uint16_t j = y_start; j < y_end; j++)
        {
            clearPixel (i, j);
        }
    }
}

void ili9341::clearPixel (uint16_t x, uint16_t y)
{
    if (x >= tft_h || y >= tft_w)
    {
        return;
    }

    set_address (x, y, x + 1, y + 1);

    send_data16 (ili9341_colors::black);
}

void ili9341::setPixel (uint16_t x, uint16_t y)
{
    if (x >= tft_h || y >= tft_w)
    {
        return;
    }

    if (y < 240)
    {
        is_pixel_written [x] [y] = true;
    }

    set_address (x, y, x + 1, y + 1);

    send_data16 (ili9341_colors::white);
}

void ili9341::setPixel (uint16_t x, uint16_t y, uint16_t color)
{
    if (x >= tft_h || y >= tft_w)
    {
        return;
    }

    if (y < 240 && color != 0) //black pixels don't have to be cleared, but they DO have to be written (especially when overwriting chars)
    {
        is_pixel_written [x] [y] = true;
    }

    set_address (x, y, x + 1, y + 1);

    send_data16 (color);
}

void ili9341::setRotation (bool rotated)
{
    isRotated = rotated;
}

void ili9341::flush ()
{}