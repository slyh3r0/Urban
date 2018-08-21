;Testing the A20 Line

testA20:

	pusha

	mov ax,[0x7dfe] ;Print the hex of our Magic value, should be aa55
	mov bx,0xffff
	mov es,bx

	mov bx, 0x7e0e

	mov dx,[es:bx]

	cmp dx,ax
	je .cont
	
	popa
	mov ax,1
ret

.cont:

	mov ax,[0x7dff]
	mov bx,0xffff
	mov es,bx

	mov bx,0x7e0f

	mov dx,[es:bx]

	cmp dx,ax
	je .exit 

	popa
	mov ax,1
ret

.exit:

	popa
	xor ax,ax
ret


;Enabing the A20 Line

enableA20:

	pusha
	
;###BIOS Methode####
	
	mov ax,0x2401
	int 0x15

	call testA20
	cmp ax,1
	je .done

;###Keyboard Methode###
	
	cli
	
	call waitC
	mov al,0xad
	out 0x64,al ;Disable Keyboard

	call waitC
	mov al,0xd0
	out 0x64,al ;Tell Keyboard Controller we want to read

	call waitD
	in al,0x60
	push ax

	call waitC
	mov al,0xd1
	out 0x64,al

	call waitC
	pop ax
	or al,2
	out 0x60,al ;Send masked byte to KC

	call waitC
	mov al,0xae
	out 0x64,al

	call waitC
	sti

	call testA20

	cmp ax,1
	je .done

;###fastA20###

	in al,0x92
	or al,2
	out 0x92,al

	call testA20
	cmp ax,1
	je .done
	popa
	xor ax,ax
ret

.done:
	popa
	mov ax,1
ret




waitC:
	in al,0x64
	test al,2
	jnz waitC
ret

waitD:
	in al,0x64
	test al,1
	jnz waitD
ret



















