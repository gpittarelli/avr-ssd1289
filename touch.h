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

#ifndef __TOUCH_h
#define __TOUCH_h

#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "pins.h"

void touch_init(void);

void touch_write_data(uint8_t data);
uint16_t touch_read_data(void);
void touch_read(uint16_t * out_x, uint16_t * out_y);
uint_fast8_t touch_available(void);

#endif
