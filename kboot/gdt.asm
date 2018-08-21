GDT:

	.NULL: equ $ - GDT
		dw 0
		dw 0
		db 0
		db 0
		db 0
		db 0

	.CODE: equ $ - GDT
		dw 0
		dw 0
		db 0
		db 10011000b
		db 00100000b
		db 0

	.DATA: equ $ - GDT
		dw 0
		dw 0
		db 0
		db 10000000b
		db 0
		db 0

	.POINTER:
		dw $ - GDT -1
		dq GDT
