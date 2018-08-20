#include <stdint.h>
#include "ktypes.h"


#ifndef __KTERM_H__
#define __KTERM_H__


#define vga_width 80
#define vga_height 25

typedef enum kvga_color {
	BLACK = 0,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LGRAY,
	DGRAY,
	LBLUE,
	LGREEN,
	LCYAN,
	LRED,
	LMAGENTA,
	LBROWN,
	WHITE = 15
} kvga_color;

void kvga_init(void);
static inline byte kvga_comb_colors(kvga_color fg, kvga_color bg);
static inline word kvga_entry(byte ch, byte color);
word kvga_construct_entry(byte ch, kvga_color fg, kvga_color bg);
void kvga_clear(word entry);
void kvga_put(word entry,size_t x, size_t y);

#endif
