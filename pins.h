/* Pin definitions for this project */

#ifndef __PINS_h
#define __PINS_h

/***** Configure IO *****/
#define configure_as_input(bit)             {bit ## _DDR &= ~(1 << bit);}
#define configure_as_output(bit)            {bit ## _DDR |= (1 << bit);}

#define pullup_on(bit)                      {bit ## _PORT |= (1 << bit);}
#define pullup_off(bit)                     {bit ## _PORT &= ~(1 << bit);}

#define disable_digital_input(channel)      {DIDR0 |= (1 << channel);}
#define enable_digital_input(channel)       {DIDR0 &= ~(1 << channel);}

#define enable_pin_change_interrupt(pin)    {pin ## _PCMSK |= (1 << pin ## _PCINT);}
#define disable_pin_change_interrupt(pin)   {pin ## _PCMSK &= ~(1<< pin ## _PCINT);}


/***** Manipulate Outputs *****/
#define set_high(bit)                       {bit ## _PORT |= (1 << bit);}
#define set_low(bit)                        {bit ## _PORT &= ~(1 << bit);}
#define toggle(bit)                         {bit ## _PIN |= (1 << bit);}

/***** Test Inputs *****/
#define is_high(bit)                        (bit ## _PIN & (1 << bit))
#define is_low(bit)                         (! (bit ## _PIN & (1 << bit)))

// PORT D
#define SHIFT_DATA       2
#define SHIFT_DATA_PORT  PORTD
#define SHIFT_DATA_DDR   DDRD
#define SHIFT_DATA_PIN   PIND

#define SHIFT_LATCH       3
#define SHIFT_LATCH_PORT  PORTD
#define SHIFT_LATCH_DDR   DDRD
#define SHIFT_LATCH_PIN   PIND

#define SHIFT_CLOCK       4
#define SHIFT_CLOCK_PORT  PORTD
#define SHIFT_CLOCK_DDR   DDRD
#define SHIFT_CLOCK_PIN   PIND

// PORT B
#define TFT_RS       PB0
#define TFT_RS_PORT  PORTB
#define TFT_RS_DDR   DDRB
#define TFT_RS_PIN   PINB

#define TFT_WR       PB1
#define TFT_WR_PORT  PORTB
#define TFT_WR_DDR   DDRB
#define TFT_WR_PIN   PINB

#define TFT_RD       PB2
#define TFT_RD_PORT  PORTB
#define TFT_RD_DDR   DDRB
#define TFT_RD_PIN   PINB

#define TFT_CS       PB3
#define TFT_CS_PORT  PORTB
#define TFT_CS_DDR   DDRB
#define TFT_CS_PIN   PINB

#define TFT_RST       PB4
#define TFT_RST_PORT  PORTB
#define TFT_RST_DDR   DDRB
#define TFT_RST_PIN   PINB
/*
#define TFT_WR       1
#define TFT_RD       2
#define TFT_CS       3
#define TFT_RST      4
*/
// PORT C

#define TOUCH_CLK    0
#define TOUCH_CLK_PORT  PORTC
#define TOUCH_CLK_DDR   DDRC
#define TOUCH_CLK_PIN   PINC

#define TOUCH_IN     1
#define TOUCH_IN_PORT  PORTC
#define TOUCH_IN_DDR   DDRC
#define TOUCH_IN_PIN   PINC

#define TOUCH_BUSY   2
#define TOUCH_BUSY_PORT  PORTC
#define TOUCH_BUSY_DDR   DDRC
#define TOUCH_BUSY_PIN   PINC

#define TOUCH_OUT    3
#define TOUCH_OUT_PORT  PORTC
#define TOUCH_OUT_DDR   DDRC
#define TOUCH_OUT_PIN   PINC

#define TOUCH_PENIRQ 4
#define TOUCH_PENIRQ_PORT  PORTC
#define TOUCH_PENIRQ_DDR   DDRC
#define TOUCH_PENIRQ_PIN   PINC

#define TEMP       PC5
#define TEMP_PORT  PORTC
#define TEMP_DDR   DDRC
#define TEMP_PIN   PINC


#endif
