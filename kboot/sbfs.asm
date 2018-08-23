; Bootsector for sbfs bootloader-loader
[org 0x7c00]
[bits 16]

boot:
	jmp begin

	times 4 -($ - $$) nop

SBFS_HEADER:
;##### START FS-ENTRY #####
.FILESYSTEM_TYPE:		dw 0x0001	; 0x0000 is reserved, 0x0001 is SBFS
.FILESYSTEM_VERSION:		dw 0x0000
.MAX_BYTES:				dq 0x0000000000000000
;##### END   FS-ENTRY #####

;##### START SBFS-HEADER #####
.DRIVE_NUMBER:			db 0		; reserved for flags and alignment
.BLOCKSIZE:				db 0x01		; shl 0x0200, BLOCKSIZE
;Leave offset at 0 if not needed it may in the future serve some other purpose 
.OFFSET:					dw 0		; offset added to all tables 
.READ_TABLE:				dw 0		; RT offset
.RT_BACKUP:				dw 0
.WRITE_TABLE:			dw 0		; WT offset
.WT_BACKUP:				dw 0
.CHECKSUM:				dd 0		; xor all of the above as multiple dwords (starts from 0)
;##### END   SBFS-HEADER #####

; Address to load the osloader
LOAD_ADDR equ 0x40000

; Address that is jumped to after loading the osloader
LINK_ADDR equ 0x40000 ; The Urban Loader uses the filestart as its linking point

; Address to store LBA 

LBA_PACKET equ 0x9000

; SBFS reserves only the first 32 byte of the Bootsector
; So we have 478 Bytes for the Loader

begin:
	
	jmp 0:main ;Fix cs, just in case

main:
	
	cld
	test dl, 0x7f ; Force a sane value for the drive number
	jz dl_valid
	mov dl, byte [SBFS_HEADER.DRIVE_NUMBER] ; if value seems bad

dl_valid:

	;Save Drive Number in upper edx
	push dx
	bswap edx
	pop dx

	;Stack Setup 
	xor di,di
	mov di,ss
	mov sp,0x7bfc

	;Segments Setup 
	mov di,ds
	mov di,es

	;Test for LBA support
	mov ah,0x41
	mov bx,0x55aa
	mov dl,0x80
	int 0x13
	jc no_lba

	mov si,SBFS_HEADER
	mov di,SBFS_HEADER.CHECKSUM

	call checkfsheader
	jne dirty_header

	mov si, [SBFS_HEADER]
	


make_lba_packet:


checkfsheader: ;si = header start ; di = header stop ; upper eax is trashed
	pusha
	xor eax,eax
.loop:
	xor eax,dword [si]
	add si,4
	cmp di,si
	jne .loop
	cmp eax,dword [si]
	popa
ret

dirty_header:
no_lba:

jmp $





times 510 - ($ - $$) db 0
dw 0xaa55

; If checkfs fails this will be loaded
SBFS_BACKUP_HEADER:
;##### START BACKUP FS-ENTRY #####
.FILESYSTEM_TYPE:			dw 0x0001
.FILESYSTEM_VERSION:		dw 0x0000
.MAX_BYTES:					dq 0x0000000000000000
;##### END   BACKUP FS-ENTRY #####

;##### START BACKUP SBFS-HEADER #####
.RESERVED_BYTE:				db 0
.BLOCKSIZE:					db 0x01
.OFFSET:					dw 0
.READ_TABLE:				dw 0
.RT_BACKUP:					dw 0
.WRITE_TABLE:				dw 0
.WT_BACKUP:					dw 0
.CHECKSUM:					dd 0
;##### END   BACKUP SBFS-HEADER #####
