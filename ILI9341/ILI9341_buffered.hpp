
//          Copyright Daan Boezeman 2019.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef ILI9341_HPP
#define ILI9341_HPP
#include "hwlib.hpp"

using namespace hwlib;

/// @file

/// \brief
/// Enum class with a list of commands.
/// \details
/// Enum class with a list of commands to be used with the ili9341 chip, not all commands are listed but only the ones relevant to me.

enum class ili9341_commands : uint8_t 
{
    sw_reset                    = 0x01, // perform software reset, no parameters
    slp_in                      = 0x10, // go into sleep mode, no parameters
    slp_out                     = 0x11, // go out of sleep mode, no parameters
    ptl_on                      = 0x12, // partial on, no parameters
    nor_on                      = 0x13, // normal on, no paramteters
    inv_off                     = 0x20, // display inversion off, no parameters
    inv_on                      = 0x21, // display inversion on, no parameters
    gamma_set                   = 0x26, // gamma set, 1 parameter (correction setting)
    disp_off                    = 0x28, // display off, no parameters
    disp_on                     = 0x29, // display on, no parameters
    ca_set                      = 0x2A, // column address set, 4 parameters: SC[15:8], SC[7:0], EC[15:8], EC[7:0]
    pa_set                      = 0x2B, // page address set, 4 parameters: SP[15:8], SP[7:0], EP[15:8], EP[7:0]
    ram_wr                      = 0x2C, // memory/ram write, 1 parameter: D[17:0]               (gek, 2 bytes?)
    ptl_ar                      = 0x30, // partial area, 4 parameters: SR[15:8], SR[7:0], ER[15:8], ER[7:0]
    vscr_def                    = 0x33, // vertical scrolling definition, 6 parameters: TFA[15:8], TFA[7:0], VSA[15:8], VSA[7:0], BFA[15:8], BFA[7:0]
    mad_ctl                     = 0x36, // memory access control, 1 parameter: D[7] = MY, D[6] = MX, D[5] = MV, D[4] = ML, D[3] = BGR, D[2] = MH, D[1:0] = doesn't care
    vscr_sadd                   = 0x37, // vertical scrolling start adress, 2 parameters: VSP[15:8], VSP[7:0]
    pix_fmt                     = 0x3A, // pixel format set, see datasheet for details
    frm_ctl1                    = 0xB1, // frame control (normal mode), see datasheet for details
    frm_ctl2                    = 0xB2, // frame control (idle mode), see datasheet for details
    frm_ctl3                    = 0xB3, // frame control (partial mode), see datasheet for details
    inv_ctl                     = 0xB4, // display inversion control, 1 parameter: D[2] = NLA, D[1] = NLB, D[0] = NLC
    dfunc_ctl                   = 0xB6, // display function control, 4 parameters, see datasheet for details
    pw_ctl1                     = 0xC0, // power control, see datasheet for details
    pw_ctl2                     = 0xC1, // power control, see datasheet for details
    vm_ctl1                     = 0xC5, // VCOM control, see datasheet for details
    vm_ctl2                     = 0xC7, // VCOM control, see datasheet for details
    gmc_p                       = 0xE0, // gamma correction positive,  see datasheet for details
    gmc_n                       = 0xE1  // gamma correction negative,  see datasheet for details
};

/// \brief
/// Enum class with a list of colors.
/// \details
/// Enum class with a brief list of colors, useless because hwlib has this already. Used at the first stage of development.

enum class ili9341_colors : uint16_t
{
    black                       = 0x0000,
    purple                      = 0x708F,
    blue                        = 0x001F,
    green                       = 0x07E0,
    red                         = 0xF800,
    yellow                      = 0xFFE0,
    white                       = 0xFFFF,
    orange                      = 0xFD20,
    pink                        = 0xFC18
};

/// \brief
/// Class to provide a window class.
/// \details
/// Class to provide a window class on a display using the ili9341 chip.
class ili9341 : public window
{
    spi_bus & bus;
    pin_out & res;
    pin_out & dc;
    pin_out & cs;

    const uint16_t tft_h = 240; //x
    const uint16_t tft_w = 320; //y

    bool is_pixel_written [240] [240]; // can't do [240] [320] because of memory limitations

    bool isRotated;

    /// \brief
    /// Init function.
    /// \details
    /// Init function which prepares the display for regular usage.
    void init ();

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, without a parameter byte.
    void send_command8 (ili9341_commands c);

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with one parameter byte.
    void send_command8 (ili9341_commands c, uint8_t d0);

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with two parameter bytes.
    void send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1);
    
    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with three parameter bytes.
    void send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2);

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with four parameter bytes.
    void send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with five parameter bytes.
    void send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4);

    /// \brief
    /// Send a single command.
    /// \details
    /// Send a single command, with fifteen parameter bytes.
    void send_command8 (ili9341_commands c, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7, uint8_t d8, uint8_t d9, uint8_t d10, uint8_t d11, uint8_t d12, uint8_t d13, uint8_t d14);

    /// \brief
    /// Send a single data byte.
    /// \details
    /// Send a single data byte.
    void send_data8 (uint8_t data);

    /// \brief
    /// Send two data bytes.
    /// \details
    /// Send two data bytes.
    void send_data16 (uint16_t data);

    /// \brief
    /// Send two data bytes.
    /// \details
    /// Send two data bytes containing the ili9341_colors color, which is a parameter.
    void send_data16 (ili9341_colors color);

    /// \brief
    /// Set the working address.
    /// \details
    /// Set the working address where the bytes after this command will be written. This function takes rotation into account.
    void set_address (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    /// \brief
    /// Set the working address.
    /// \details
    /// Set the working address where the bytes after this command will be written. This function DOES NOT take rotation into account, making it suitable for use within clearing functions.
    void set_address_clear (uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

    /// \brief
    /// Funtion to get the 2-byte color code.
    /// \details
    /// Funtion to get the 2-byte color code from the red, green and blue argument bytes.
    uint16_t get_565_color (uint8_t red, uint8_t green, uint8_t blue);

    /// \brief
    /// Write implementation function used by HWLIB to write certain drawables.
    /// \details
    /// Write implementation function used by HWLIB to write certain drawables.
    void write_implementation (xy pos, color pixelcolor);

public: 

    /// \brief
    /// Default constructor.
    /// \details
    /// Default constructor, which takes a spi_bus, a reset pin, a data/command pin and a chipSelect pin as arguments.
    ili9341 (spi_bus & bus, pin_out & res, pin_out & dc, pin_out & cs);

    /// \brief
    /// Clear display funtion.
    /// \details
    /// This function clears the display.
    void clear () override;

    /// \brief
    /// Clear display partly funtion.
    /// \details
    /// This function clears the display partly. With the arguments, you can specify the rectangle to be cleared.
    void clearPart (uint16_t x_start, uint16_t y_start, uint16_t x_end, uint16_t y_end);

    /// \brief
    /// Flush function.
    /// \details
    /// Flush function, not used in this library.
    void flush () override;

    /// \brief
    /// Set pixel function.
    /// \details
    /// Set pixel at x, y to white.
    void setPixel (uint16_t x, uint16_t y);

    /// \brief
    /// Set pixel function.
    /// \details
    /// Set pixel at x, y to color.
    void setPixel (uint16_t x, uint16_t y, uint16_t color);

    /// \brief
    /// Clear pixel function.
    /// \details
    /// Clear pixel at x, y to black.
    void clearPixel (uint16_t x, uint16_t y);

    /// \brief
    /// Set display rotation function.
    /// \details
    /// Set display rotation, false is not rotated an true is rotated.
    void setRotation (bool rotated = false);
};

#endif //ILI9341_HPP