.MODEL SMALL
.STACK 256
.DATA
string db 100 dup ('$')
word_buffer db 100 dup (?) 
general_buffer db  100 dup (?)
invite_str db 'Enter string, ended by .',10,13,'$'
rezult db 10,13, 'Result:',10,13,'$'
.CODE

Invertor macro str, word_buf, buff 
        lea di, str
        mov cx, 0

        ; посчитаем длину строки 	
        lenth dw 0
        mov ah, '$'
        _next:
            cmp [di], ah ; долши ли мы до символа конца строки 
            je _out ; если дошли, то выходим из цикла, иначе ... 
                inc di ; сдвигаем указатель вправо
                add lenth, 1 ; увеличиваем переменную, отвечающую за длину строки
                jmp _next ; переходи на новую итерацию
            _out: ; 
        sub lenth, 1 ; пропускаем точку

        lea di, str
    
        mov cx, lenth
        _l1: ; цикл нужен, чтобы спистить указатель di в конец строки 
            inc di
        loop _l1    

        lea si, word_buf
        lea bx, buff

        word_len dw, 0
        mov cx, lenth
        _l2:
            push cx
; копируем элементы из di в si и увеличиваем длину слова на 1
            mov ah, [di]
            mov [si], ah
            add word_len, 1          
            dec di
            inc si

            mov ah, ' ' 
            cmp [di], ah ; сравниваем символ с пробелом 
            je _do 
                jmp _dan ; если не пробел, то переходи на следующую итерацию
            _do: ; ... иначе
                mov cx, word_len ; создаём вложенный цикл
                dec si
                _l3: ; суть в том, чтобы второй раз перевернуть скопированное слово
                    mov ah, [si] ; поскольку di идёт справа налево, поэтому в word_buf
                    mov [bx], ah ; лежит перевёрнутое слово
                    dec si ; а в этом цикле мы снвоа переворачиваем слово и закидываем 
                    inc bx ; его в buf
                loop _l3
                inc si
                mov word_len, 0
            _dan:
            pop cx
        loop _l2
; завершаем строку 
        mov [bx], 10
        inc bx
        mov [bx], 13
        inc bx
        mov [bx], '$'
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
	
    lea dx, general_buffer 
    mov ah, 09h
    int 21h

    ret
    
print_string endp

start:
    mov ax, @data
    mov ds, ax
    mov es, ax
    call input_string

    Invertor string, word_buffer, general_buffer

    call print_string
    mov ah, 4ch
    int 21h
END start

