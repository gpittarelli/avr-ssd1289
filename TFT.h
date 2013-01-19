/* SSD1289 TFT LCD Library for Atmega
 * Author: George Pittarelli
 *
 * Requires pin #defines:
 *  - TFT_RS
 *  - TFT_WR
 *  - TFT_RD
 *  - TFT_CS
 *  - TFT_RST
 * as bit numbers on PORTB
 */

#ifndef __TFT_h
#define __TFT_h

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "pins.h"
#include "shift.h"

void TFT_init(void);

void TFT_write_command(uint16_t command);
void TFT_write_data(uint16_t data);
void TFT_write_command_data(uint16_t command, uint16_t data);
void TFT_write_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void TFT_fill(uint16_t color);
void TFT_draw_box(uint16_t x1, uint16_t y1, uint16_t x2,
                  uint16_t y2, uint16_t color);
void TFT_box_outline(uint16_t x1, uint16_t y1, uint16_t x2,
                     uint16_t y2, uint16_t width, uint16_t color);
void TFT_dot(uint16_t x, uint16_t y, uint16_t color);

void TFT_char(const uint8_t *font, uint8_t ch,
                uint16_t x, uint16_t y,
                uint16_t fg_color, uint16_t bg_color,
                uint16_t width, uint16_t height);

#endif
