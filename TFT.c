/* Implementation of SSD1289 TFT LCD library from TFT.h */

#include "TFT.h"

void TFT_write_command(uint16_t command) {
  PORTB &= ~(_BV(TFT_RS));

  shift_out(command);

  PORTB &= ~(_BV(TFT_WR));
  PORTB |= _BV(TFT_WR);
}

void TFT_write_data(uint16_t data) {
  PORTB |= _BV(TFT_RS);

  shift_out(data);

  PORTB &= ~(_BV(TFT_WR));
  PORTB |= _BV(TFT_WR);
}

void TFT_write_command_data(uint16_t command, uint16_t data) {
  TFT_write_command(command);
  TFT_write_data(data);
}

void TFT_write_address(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
  TFT_write_command_data(0x0044, (x2 << 8) + x1);
  TFT_write_command_data(0x0045, y1);
  TFT_write_command_data(0x0046, y2);
  TFT_write_command_data(0x004e, x1);
  TFT_write_command_data(0x004f, y1);
  TFT_write_command(0x0022);
}

void TFT_fill(uint16_t color) {
  uint32_t i;
  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(0,0,239,319);
  TFT_write_data(color);

  for(i = 0; i <= 0x9600; i++)
  {
    PORTB &= ~(_BV(TFT_WR));
    PORTB |= _BV(TFT_WR);
    PORTB &= ~(_BV(TFT_WR));
    PORTB |= _BV(TFT_WR);
  }

  PORTB |= _BV(TFT_CS);
}


void TFT_draw_box(uint16_t x1, uint16_t y1, uint16_t x2,
                  uint16_t y2, uint16_t color) {
  uint16_t dx = x2 - x1 + 1, j;
  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(x1, y1, x2, y2);
  TFT_write_data(color);

  y2 -= y1 + 1;
  while (--y2) {
    j = dx;
    while (--j) {
      PORTB &= ~(_BV(TFT_WR));
      PORTB |= _BV(TFT_WR);
    }
  }

  PORTB |= _BV(TFT_CS);
}

void TFT_dot(uint16_t x, uint16_t y, uint16_t color) {
  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(x, y, x, y);
  TFT_write_data(color);
  PORTB |= _BV(TFT_CS);
}

void TFT_init(void) {
  PORTB |= _BV(TFT_RD);

  PORTB |= _BV(TFT_RST);
  _delay_ms(5);
  PORTB &= ~(_BV(TFT_RST));
  _delay_ms(15);
  PORTB |= _BV(TFT_RST);
  _delay_ms(15);

  PORTB &= ~(_BV(TFT_CS));

  TFT_write_command_data(0x0000,0x0001); // Turn on oscillator
  TFT_write_command_data(0x0003,0xA8A4); // Power control
  TFT_write_command_data(0x000C,0x0000); // Power control 2
  TFT_write_command_data(0x000D,0x000C); // Power control 3
  TFT_write_command_data(0x000E,0x2B00); // Power control 4
  TFT_write_command_data(0x001E,0x00B7); // Power control 5
  TFT_write_command_data(0x0001,0x2B3F); // Driver Output Control
  TFT_write_command_data(0x0002,0x0600); // LCD Driving Waveform
  TFT_write_command_data(0x0010,0x0000); // Sleep Mode
  TFT_write_command_data(0x0011,0x6070); // Entry Mode
  TFT_write_command_data(0x0005,0x0000); // Compare register
  TFT_write_command_data(0x0006,0x0000); // Compare register
  TFT_write_command_data(0x0016,0xEF1C); // Horizontal Porch
  TFT_write_command_data(0x0017,0x0003); // Vertical Porch
  TFT_write_command_data(0x0007,0x0233); // Display Control
  TFT_write_command_data(0x000B,0x0000); // Frame cycle control
  TFT_write_command_data(0x000F,0x0000); // Gate scan start position
  TFT_write_command_data(0x0041,0x0000); // Vertical scroll control
  TFT_write_command_data(0x0042,0x0000); // Horiz scroll control
  TFT_write_command_data(0x0048,0x0000); // First window start
  TFT_write_command_data(0x0049,0x013F); // First window end
  TFT_write_command_data(0x004A,0x0000); // Second window start
  TFT_write_command_data(0x004B,0x0000); // Second window end
  TFT_write_command_data(0x0044,0xEF95); // Horizontal RAM addr pos
  TFT_write_command_data(0x0045,0x0000); // Vertical RAM addr start pos
  TFT_write_command_data(0x0046,0x013F); // Vertical RAM addr end pos
  TFT_write_command_data(0x0030,0x0707); // gamma control 1
  TFT_write_command_data(0x0031,0x0204);
  TFT_write_command_data(0x0032,0x0204);
  TFT_write_command_data(0x0033,0x0502);
  TFT_write_command_data(0x0034,0x0507);
  TFT_write_command_data(0x0035,0x0204);
  TFT_write_command_data(0x0036,0x0204);
  TFT_write_command_data(0x0037,0x0502);
  TFT_write_command_data(0x003A,0x0302);
  TFT_write_command_data(0x003B,0x0302); // gamma control 10
  TFT_write_command_data(0x0023,0x0000); // RAM write data mask 1
  TFT_write_command_data(0x0024,0x0000); // RAM write data mask 2
//  TFT_write_command_data(0x0025,0x8000); //
  TFT_write_command_data(0x004f,0x0000); // GDDRAM Y addr counter
  TFT_write_command_data(0x004e,0x0000); // GDDRAM X addr counter
  TFT_write_command(0x0022); // RAM data write

  PORTB &= ~(_BV(TFT_CS));
}

void TFT_char(const uint8_t *font, uint8_t ch,
              uint16_t x, uint16_t y,
              uint16_t fg_color, uint16_t bg_color,
              uint16_t width, uint16_t height) {
  uint16_t j, k;
  const uint8_t *bmp_addr = font + ((ch - ' ')*height*(width/8));
  uint8_t bmp_byte = 0, pixel_mask = 0x80;
  uint8_t bit_set = 0;

  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(x, y, x + width - 1, y + height - 1);

  k = 0;
  while (height--)
  {
    for (j = width; j; --j)
    {
      if ((k % 8) == 0) {
        bmp_byte = pgm_read_byte(bmp_addr);
        pixel_mask = 0x80;
        ++bmp_addr;
      }

      bit_set = bmp_byte & pixel_mask;

      pixel_mask >>= 1;
      ++k;

      if (bit_set) {
        TFT_write_data(fg_color);
      } else {
        TFT_write_data(bg_color);
      }
    }
  }

  PORTB |= _BV(TFT_CS);
}
