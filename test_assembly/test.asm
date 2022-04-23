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
    LDA #$08
    LDY #$05
    STY FIBCOUNT
    
    BRK
    SEC 
    SBC FIBCOUNT
    BRK
