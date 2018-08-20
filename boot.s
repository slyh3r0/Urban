
# Multiboot Constants 

#ask bootloader to align loaded modules on page boundaries
.set MULTIBOOTALIGN,	1<<0		
#ask bootloader to provide a memory map
.set MULTIBOOTMEMINFO,	1<<1		
#combined into the Multiboot "Flags" field
.set MULTIBOOTFLAGS,	MULTIBOOTALIGN | MULTIBOOTMEMINFO	
#Black Magic !
.set MULTIBOOTMAGIC,	0x1BADB002	
#for bootloader to verify this is an actual Multibootheader
.set MULTIBOOTCHECKSUM,	-(MULTIBOOTMAGIC + MULTIBOOTFLAGS)

# Actual Multibootheader :

.section .multiboot
.align 4
.long MULTIBOOTMAGIC
.long MULTIBOOTFLAGS
.long MULTIBOOTCHECKSUM

# Inital stack till managed by kernel

.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 Kib
stack_top:

# Startup
.section .text
.global _start
.type _start,@function
_start:
	# Establish early stack
	movl $stack_top, %esp

	call kinit 

	cli
1:	hlt
	jmp 1b

# Debugging Stuff
.size _start, . - _start
# Defines the size of the section i guess
