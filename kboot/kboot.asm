[org 0x7c00]
[bits 16]

section .text
global boot

boot:
	cli
	jmp 0x0000:SegZero
SegZero:
	
	xor ax,ax
	mov ss,ax
	mov ds,ax
	mov es,ax
	mov fs,ax
	mov gs,ax
	mov sp,main
	cld
	sti
	
	push ax
	xor ax,ax
	mov dl, 0x80 ;for the Harddrive(80)/floppy(0)/usb(0)
	int 0x13
	pop ax


mov al, 1
mov cl, 2
call read_sectors

mov si, READ_SUCCESS
call secsec

jmp $

READ_SUCCESS: db "Loaded secound Sector", 0
NEWSTR: db "This is printed from the secound Sector", 0
;padding and magic value
times 510-($ - $$) db 0
dw 0xaa55

secsec:
	mov si, NEWSTR
	call print
ret


times 512 db 0
