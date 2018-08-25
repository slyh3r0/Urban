#include "ktypes.h"
#include "kvga.h"

#ifndef __KVGA_C__
#define __KVGA_C__


word* vga_buffer;
void* vga_buffer_end;

void kvga_init(){

	vga_buffer = (word *) 0x000B8000;
	vga_buffer_end = (void *)vga_buffer + (vga_width * vga_height * sizeof(word));
	kvga_clear(kvga_entry(' ',kvga_comb_colors(WHITE,BLACK)));
	return;
}

static inline byte kvga_comb_colors(kvga_color fg, kvga_color bg){
	return fg | bg << 4;
}

static inline word kvga_entry(byte ch, byte color){
	return (word) ch | (word) color << 8;
}

word kvga_construct_entry(byte ch, kvga_color fg, kvga_color bg){
	return kvga_entry(ch,kvga_comb_colors(fg, bg));
}

void kvga_clear(word clear_entry){

	size_t i = 0;
	while ( (void *) &vga_buffer[i] < vga_buffer_end){
		vga_buffer[i] = clear_entry;
		i++;
	}
	return;
}

void kvga_put(word entry, size_t x, size_t y){
	
	size_t i;

	if (x > vga_width || y > vga_height ){
		return;
	}
	
	i = vga_width * y + x;
	vga_buffer[i] = entry;
	return;
}

#endif
