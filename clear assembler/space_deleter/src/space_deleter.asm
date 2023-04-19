.MODEL SMALL
.STACK 256
.DATA
string db  100 dup ('$')
buffer db  100 dup (?)
invite_str db 'Enter string:',10,13,'$'
rezult db 10,13, 'Result:',10,13,'$'
.CODE

SpaceDeleter macro source, buff
    lea di, source
    lea si, buff
    mov cx, 100

    _loop:
        push cx
        mov ah, '.'
        cmp [di], ah
        je _end
            mov ah, ' '
            cmp [di], ah
            je _sec
                mov ah, [di]
                mov [si], ah
                inc di
                inc si
                jmp _dan
            _sec: 
                mov ah, [di]
                mov [si], ah
                inc si
                inc di
                mov al, ' '
                _next:
                cmp [di], al
                je _yes
                    jmp _dan
                _yes:
                    inc di
                    jmp _next
        _end:
            mov [si], ah
            pop cx
            mov cx, 0
            push cx
        _dan:
        pop cx
    loop _loop
endm

input_string proc near
    lea     dx, invite_str
    mov     ah, 09h
    int     21h
    
    mov     cx, 100
    lea     bx, string
    enter_char:
    mov     ah, 01h
    int     21h 
    cmp     al, '.'
    je quit_input
    mov     byte ptr [bx], al
    inc     bx
    loop    enter_char
    quit_input:
    ret
input_string endp

print_string proc near

    lea dx, rezult 
    mov ah, 09h
    int 21h
	
    lea dx, buffer
    mov ah, 09h
    int 21h

    ret
    
print_string endp

start:
    mov ax, @data
    mov ds, ax
    mov es, ax
    call input_string

    SpaceDeleter string, buffer

    call print_string
    mov ah, 4ch
    int 21h
END start
