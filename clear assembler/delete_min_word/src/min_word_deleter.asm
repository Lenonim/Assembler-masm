.MODEL SMALL
.STACK 256
.DATA
string db  100 dup ('$')
buffer db  100 dup (?)
invite_str db 'Enter string, ended by .',10,13,'$'
rezult db 10,13, 'Result:',10,13,'$'
_min_len dw 100
_word_len dw 0
_position_min_word dw 0
_position_this_word dw 0
_str_len dw 0 
.CODE

MinWordDeleter macro source, buff, min_len, word_len, position_min_word, position_this_word, str_len
    lea di, source
    mov cx, 100
    
    _next:
        mov ah, '$'
        cmp [di], ah
        je _y1
            add str_len, 1
            mov ah, ' '
            cmp [di], ah
            je _y2
                add word_len, 1
                jmp _d2
            _y2:
                mov si, min_len
                mov cx, word_len
                cmp si, cx
                jg _y3
                    jmp _d3
                _y3:
                    mov min_len, cx
                    mov cx, position_this_word
                    mov position_min_word, cx
                _d3:
                mov word_len, 0
                add position_this_word, 1
            _d2:
            inc di
            jmp _next
    _y1:

    lea di, source
    lea si, buff
    mov cx, str_len

    _l1:
    push cx
        mov cx, position_min_word
        cmp cx, 0
        je _y4
            mov ah, ' '
            cmp [di], ah
            je _y5
                jmp _d5
            _y5:
                sub position_min_word, 1
            _d5:
                mov ah, [di]
                mov [si], ah
                inc di
                inc si
                jmp _n
        _y4:
            add min_len, 1
            mov cx, min_len
            _l2:
                inc di
            loop _l2
            mov position_min_word, 10000
    _n:
    pop cx
    loop _l1

    mov [si], '$'
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

    MinWordDeleter string, buffer, _min_len, _word_len, _position_min_word, _position_this_word, _str_len

    call print_string
    mov ah, 4ch
    int 21h
END start
