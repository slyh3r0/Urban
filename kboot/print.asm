print:
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
