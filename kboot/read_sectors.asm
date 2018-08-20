read_sectors: ;al is number of sectors to read ;cl starting sector (starts with 1)
    pusha
    mov ah, 0x02
    mov dl, 0x80
    mov ch, 0
    mov dh, 0

    push bx
    mov bx, 0
    mov es, bx
    pop bx
    mov bx, 0x7c00 + 512 ; Always load afer bootsector
    int 0x13

    jc read_error
    popa
ret
read_error:
    mov si, READ_ERROR
    call print
    jmp $
READ_ERROR: db "Error loading from Disk !", 0
