[org 0x7c00]
[bits 16]

section .text
global main

main:
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

	;reset disk
	xor ax,ax
	mov dl,0x80
	int 0x13

	;read secound sector
	mov al,1
	mov cl,2
	call read_sectors
	
	;check A20 compatible
	call enableA20
	cmp ax,1
	je A20enabled ;jmp secound sector
	
	mov si,A20_FAIL
	call print
	mov si,SYSTEM_NEEDS
	call print
	mov dx,ax
	call hex
	jmp $


%include "print.asm"
%include "read_sectors.asm"
%include "enableA20.asm"

A20_FAIL: db "The A20 Line could not be enabled !",0x0a,0x0d,0
LM_FAIL: db "Long Mode is not supported !",0x0a,0x0d,0
SYSTEM_NEEDS: db "The Urban Kernel needs: A20 Line, Long Mode",0x0a,0x0d,0
SUCCESS: db "DONE",0x0a,0x0d,0

;padding and magic value
times 510-($ - $$) db 0
dw 0xaa55
;Secound sector

A20enabled:
	call checkLM
	cmp ax,1
	je LMchecked

	mov si,LM_FAIL
	call print
	mov si,SYSTEM_NEEDS
	call print
	mov dx,ax
	call hex
	jmp $

LMchecked:
	
	cli
	mov edi,0x1000
	mov cr3,edi
	xor eax,eax
	mov ecx,4096
	rep stosd
	mov edi,0x1000

	mov dword [edi], 0x2003
	add edi,0x1000
	mov dword [edi], 0x3003
	add edi,0x1000
	mov dword [edi], 0x4003
	add edi,0x1000

	mov dword ebx, 3
	mov ecx, 512

.setEntry:
	mov dword [edi], ebx
	add ebx, 0x1000
	add edi, 8
	loop .setEntry

	;Enable PAE
	mov eax,cr4
	or eax,1<<5
	mov cr4,eax

	mov ecx, 0xc0000080
	rdmsr
	or eax,1<<8
	wrmsr

	mov eax,cr0
	or eax,1<<31
	or eax,1<<0
	mov cr0,eax

	lgdt [GDT.POINTER]
	jmp GDT.CODE:LongMode

%include "gdt.asm"
%include "checkLM.asm"

[bits 64]

LongMode:
	
	mov rax, 0x0f54
	mov [VGA_MEM], rax
	
	hlt
	


VGA_MEM: equ 0xb8000
times 1024- ($ - $$) db 0

