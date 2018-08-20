#include <stdbool.h>
#include <stddef.h>
#include "ktypes.h"
#include "kvga.h"
#include "multiboot.h"


#if defined(__linux__)
#error "This is a linux compiler! You need a cross compiler! (for info visit: www.osdev.org)"
#endif

#if !defined(__i386__)
#error "Trying to compile for wrong target! Use a cross compiler for i686-elf to have a chance to compile this :)"
#endif 





void kinit(/*multiboot_info_t* mbdata, unsigned int magic*/){

	kvga_init();
	kvga_clear(kvga_construct_entry('c',BLUE,RED));
	kvga_put(kvga_construct_entry('X',WHITE,BLACK),79,19);
}
