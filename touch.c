#include "touch.h"

#define nop()  asm volatile("nop")

void touch_init(void) {
  PORTC |= _BV(TOUCH_CLK) | _BV(TOUCH_IN);
}

void touch_write_data(uint_fast8_t data) {

  PORTC &= ~(_BV(TOUCH_CLK));

  for (uint8_t mask = 0x80; mask; mask >>= 1)
  {
    if (data & mask) {
      PORTC |= _BV(TOUCH_IN);
    } else {
      PORTC &= ~(_BV(TOUCH_IN));
    }

    PORTC &= ~(_BV(TOUCH_CLK));
    nop(); nop(); nop();
    PORTC |= _BV(TOUCH_CLK);
    nop(); nop(); nop();
  }
}

uint16_t touch_read_data(void) {
  uint16_t data = 0;

  for(uint_fast8_t count = 12; count; --count)
  {
    PORTC |= _BV(TOUCH_CLK);
    nop(); nop(); nop();
    PORTC &= ~(_BV(TOUCH_CLK));
    nop(); nop(); nop();

    if (PINC & _BV(TOUCH_OUT)) {
      data |= 1;
    }

    data <<= 1;
  }

  return data;
}

void touch_read(uint16_t * out_x, uint16_t * out_y) {
  uint16_t temp_x, temp_y;
  uint32_t tx = 0, ty = 0;
	uint_fast8_t datacount = 0;

	for (uint_fast8_t i = 8; i; --i) {
		touch_write_data(0x90);
    PORTC |= _BV(TOUCH_CLK);
    nop(); nop();
    PORTC &= ~(_BV(TOUCH_CLK));
    nop(); nop();
		temp_x = touch_read_data();

		touch_write_data(0xD0);
    PORTC |= _BV(TOUCH_CLK);
    nop(); nop();
    PORTC &= ~(_BV(TOUCH_CLK));
    nop(); nop();
		temp_y = touch_read_data();

   	if (temp_x && temp_y) {
			ty += temp_x;
			tx += temp_y;
			++datacount;
    }
	}

	if (datacount) {
    tx /= datacount;
    ty /= datacount;

    // TODO: move all these to constants. I'm just being super hacky atm
    tx -= 0x1A0;
    ty -= 0x2A3;

    tx *= 240;
    tx /= (0x1F10 - 0x01A0);

    ty *= 320;
    ty /= (0x1EE6 - 0x02A3);

    *out_x = tx;
    *out_y = 320-ty;
	} else {
		*out_x = *out_y = 0xFFFF;
	}
}

uint_fast8_t touch_available(void) {
  return !(PINC & _BV(TOUCH_PENIRQ));
}
