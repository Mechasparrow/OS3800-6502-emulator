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
    LDA #$05
    CMP #$06
    BRK
    ;BEQ success
    BNE success
    RTS
    NOP
success LDA #$AA
    BRK 
    RTS

