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
    LDY #$06
    STY FIBCOUNT    
    LDX #$04
    STX $A0

    LDY #$05
    CPY FIBCOUNT ;Is 6 greater than 05?
    BRK
    CPY #$05
    BRK
    CPY $A0
    BRK
