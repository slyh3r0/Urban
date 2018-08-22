kterm:
		


kterm_clean:
	mov rax,byte [KTERM.XMAX]
	mul byte [KTERM.YMAX]
	mov rdi,KTERM.VGA

	mov bx, [KTERM.COLOR]
	mov bx, 0x20 << 4

	mov word [rdi], bx







KTERM:
	.XPOS: db 0
	.YPOS: db 0
	.XMAX: db 80
	.YMAX: db 25
	.COLOR: db 0x0f
	.VGA equ 0xb8000
