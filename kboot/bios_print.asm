bios_print: ;Uses si for str_start
    pusha
    mov ah, 0x0e
    str_loop:
        mov al, [si]
        cmp al, 0
        jz print_exit
        int 0x10
        add si, 1
        jmp str_loop
    print_exit:
    popa
ret

hex: ; Uses dx for the hexadecimal word to print
	pusha
	mov ax,3 
	hex_loop:
		mov bx,dx
		and bx,0x000f
		mov cx,[HEX_CONV+bx]
		mov bx,ax
		mov [bx+HEX_INPRINT],cl
		cmp ax,0
		je hex_exit
		shr dx,4
		sub ax,1
		jmp hex_loop

hex_exit:
	mov si,HEX_INPRINT
	call bios_print
	popa
ret



HEX_INPRINT: db "****",0x0a,0x0d, 0
HEX_CONV: db "0123456789abcdef"
