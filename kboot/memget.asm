memget:

	pusha

	mov [0x5000], dword 0
	mov [0x5004], dword 0

	mov di, 0x5008 ;First 64bit are used for info about the table
	xor ebx,ebx
	xor bp,bp
	mov edx, 0x534d4150
	mov eax, 0xe820
	mov [es:di +20], dword 1
	mov ecx, 24
	

	int 0x15
	jc .error

	mov edx,0x534d4150
	cmp eax,edx
	jne .error

	test ebx,ebx
	je .error

	jmp .jmpin

.loop:
	mov eax, 0xe820
	mov [es:di +20], dword 1
	mov ecx, 24
	
	int 0x15

	jc .end

	mov edx,0x534d4150

.jmpin:
	jcxz .skipentry
	
	cmp cl, 20
	jbe .noacpi3
	
	test byte [es:di +20], 1
	je .skipentry

.noacpi3:
	mov ecx, [es:di +8]
	or ecx, [es:di +12]
	jz .skipentry

	inc bp
	add di,24

.skipentry:
	test ebx,ebx	
	jne .loop

.end:
	
	mov [0x5004], bp
	popa
	clc
ret

.error:
	popa
	stc
ret
