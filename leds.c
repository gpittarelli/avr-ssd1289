#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#include "pins.h"
#include "TFT.h"
#include "fonts.h"
#include "uart.h"
#include "shift.h"
#include "touch.h"

FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);

void TFT_pattern1(void) {
  uint16_t i;
  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(0, 0, 239, 319);

  for(i = 0; i <= 0x9600; i++)
  {
    TFT_write_data(0xff00);
    TFT_write_data(0x00ff);
  }

  PORTB |= _BV(TFT_CS);
  PORTB |= _BV(TFT_RS);
}

void TFT_pattern2(void) {
  uint16_t i;
  PORTB &= ~(_BV(TFT_CS));
  TFT_write_address(0, 0, 239, 319);

  for(i = 0; i <= 0x9600; i++)
  {
    TFT_write_data(0x00ff);
    TFT_write_data(0xff00);
  }

  PORTB |= _BV(TFT_CS);
  PORTB |= _BV(TFT_RS);
}

int main(void) {
  DDRD = _BV(SHIFT_DATA) | _BV(SHIFT_LATCH) | _BV(SHIFT_CLOCK);
  DDRB = _BV(TFT_RS) | _BV(TFT_WR) | _BV(TFT_RD) | _BV(TFT_CS) | _BV(TFT_RST);
  DDRC = 0 | _BV(TOUCH_IN) | _BV(TOUCH_CLK);
  //    TOUCH_OUT set to INPUT

  PORTD = 0;
  PORTC = 0;
  PORTB = 0;

  TFT_init();

  uart_init();
  stdout = &uart_output;
  stdin  = &uart_input;

  touch_init();

  TFT_fill(0);

  uint16_t x = 0, y = 0;
  uint8_t ch;

  // draw all of 8x8 font
  for (ch = ' '; ch <= '~'; ++ch) {
    TFT_char(FONT_8x8, ch, x, y, 61, 62016, 8, 8);
    x += 8;
    if (x >= 240) {
      y += 8;
      x = 0;
    }
  }

  // 8x8 font has 2 extra symbols:
  TFT_char(FONT_8x8, ch + 1, x, y, 61, 62016, 8, 8);
  TFT_char(FONT_8x8, ch + 2, x + 8, y, 61, 62016, 8, 8);

  y += 8;

  x = 0;
  for (ch = ' '; ch <= '~'; ++ch) {
    TFT_char(FONT_16x16, ch, x, y, 61, 62016, 16, 16);
    x += 16;
    if (x >= 240) {
      y += 16;
      x = 0;
    }
  }

  char command[10];
  uint16_t arg1, arg2, arg3, arg4;

  x = 0;
  y = 0;

  uint_fast16_t n;
  uint_fast32_t tx, ty;

  while(1) { /*
    n = 0;
    tx = ty = 0;
    while (touch_available()) {
      touch_read(&x, &y);
      tx += x;
      ty += y;
      ++n;
      _delay_us(100);
    }

    if (tx && ty) {
      tx /= n;
      ty /= n;
      printf("%#04lX   %#04lX\n", tx, ty);
    } */
/*
    if (touch_available()) {
      fputs("Touch!", stdout);
    } else {
      fputs("      ", stdout);
    }

    if (PINC & _BV(TOUCH_BUSY)) {
      fputs(" c ", stdout);
    } else {
      fputs("   ", stdout);
    }
*/
    touch_read(&x, &y);
//    printf("%#04X   %#04X\n", x, y);
    if (x != 0xFFFF) {
      TFT_draw_box(x-1, y-1, x+1, y+1, 61);
    }

  }

  while (1) {
    //input = getchar();

    scanf("%9s %u %u %u %u", command, &arg1, &arg2, &arg3, &arg4);

    printf("Got: %s %u %u %u %u\n", command, arg1, arg2, arg3, arg4);

    if (strcmp(command, "rect") == 0) {
      printf("Drawing rect from (%u, %u) -> (%u, %u)\n",
             arg1, arg2, arg3, arg4);
      TFT_draw_box(arg1, arg2, arg3, arg4, 61);
      puts("Done");
    }
  }
/*
    if (input >= ' ' && input <= '~') {
      TFT_char(FONT_16x16, input, x, y, 61, 62016, 16, 16);
      x += 16;
      if (x >= 240) {
        y += 16;
        x = 0;
      }
    } else if (input == '\r') {
      TFT_draw_box(x, y, 239, y+16, 62016);

      y += 16;
      x = 0;
    } else if (input == 0x7F) { // Backspace
      if (x == 0 && y == 0) {
        continue;
      }

      if (x > 0) {
        x -= 16;
      } else {
        y -= 16;
        x = 240-16;
      }
      TFT_char(FONT_16x16, ' ', x, y, 61, 62016, 16, 16);
    } else {
      printf("Invalid: %#X\n", input);
    }

    if (y >= 320) {
      y = 0;
    }
    } */

  return 0;
}
