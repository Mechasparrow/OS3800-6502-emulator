; A * B and writes to MULRESULT
A = $06
B = $02

MULRESULT = $B002

        ORG $C000
program:
        LDA #$00        ;Init MULRESULT to zero
        STA MULRESULT 
                        ; We know that A * B is simply A added together B times.
        LDY #B          ; Store number of times we have left to multiply
        DEY          
WHILE   CPY #$00        ; while timesLeft >= 0
        BMI programreturn
THEN    LDA MULRESULT   ; Add A to the MULRESULT
        CLC
        ADC #A
        STA MULRESULT 
        DEY             ; Decrement the Y index
        JMP WHILE       ; Loop

programreturn:
        BRK
        RTS