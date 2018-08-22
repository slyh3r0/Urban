print:
	push rax
	push rdi
	
	mov rdi, VGA_MEM	
	.printloop:
		mov al, byte [rsi]
		cmp al,0
		jz .printexit
		mov ah,[DEFAULT_COLOR]
		mov word [rdi], ax
		add rdi,2
		inc rsi
		jmp .printloop

.printexit:
	pop rdi
	pop rax
ret

pinth: ;rsi is the address of bytes to read rcx is the count of bytes to read
	




HEX_TABLE: db "0123456789abcdef"
VGA_MEM equ 0xb8000
DEFAULT_COLOR: db 0x03
