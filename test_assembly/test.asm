; Input:  A NUL-terminated, <255-length pattern at address PATTERN.
;         A NUL-terminated, <255-length string pointed to by STR.
;
; Output: Carry bit = 1 if the string matches the pattern, = 0 if not.
;
; Notes:  Clobbers A, X, Y. Each * in the pattern uses 4 bytes of stack.
;

FIBCOUNT = $B001

    ORG $C000
program:
    INX
    INY
    LDA #$00
    STA FIBCOUNT

    INC FIBCOUNT
    INC FIBCOUNT
    INC FIBCOUNT
    INC FIBCOUNT

    BRK

    DEX
    DEY
    DEC FIBCOUNT
    DEC FIBCOUNT
    DEC FIBCOUNT
    DEC FIBCOUNT
    
    BRK
