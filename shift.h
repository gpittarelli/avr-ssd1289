/* Optimized shift-out function for shift registers, in this case two
 * 74HC595's.
 */

#ifndef __SHIFT_h
#define __SHIFT_h

#include <inttypes.h>
#include <avr/io.h>

#include "pins.h"

#ifdef __cplusplus
extern "C" {
#endif

void shift_out(uint16_t data);
void inline shift_out_inline(uint16_t data);

#ifdef __cplusplus
}
#endif


#endif
