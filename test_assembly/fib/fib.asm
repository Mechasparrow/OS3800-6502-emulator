; Performs fib(FIBN) and writes to FIBRESULT

FIBN = $06
FIBNMINUS = $B008
FIBNMINUSMINUS = $B006 
FIBCOUNTER = $B004
FIBRESULT = $B002

        ORG $C000
program:
        LDA #$00 ; A = N - 2
        STA FIBNMINUSMINUS
        STA FIBRESULT ; Reset Fib result

        LDX #$01 ; X = N - 1
        STX FIBNMINUS
        LDY #FIBN ; Load in Fibn

    ; Fib (0) = 0
        CPY #$00
IF0     BNE CONTINUE0
THEN0   STA FIBRESULT 
        BRK
        RTS
CONTINUE0
        ; Fib (1) = 1
        CPY #$01
IF1     BNE CONTINUE1
THEN1     
        LDA #$01
        STA FIBRESULT
        BRK
        RTS
CONTINUE1
        ; Else Begin the fibnocci loop
        LDA #$01
        STA FIBCOUNTER
WHILE   LDY FIBCOUNTER
        CPY #FIBN 
        BPL LOOPEND 
THENFIB INC FIBCOUNTER
        ; Fibresult = Fib - 1 + Fib - 2
        LDA FIBNMINUS
        ADC FIBNMINUSMINUS
        STA FIBRESULT

        ; Fib - 1 now becomes Fib - 2
        LDX FIBNMINUS
        STX FIBNMINUSMINUS

        ; Fibresult from last time will now be Fib - 1
        LDX FIBRESULT
        STX FIBNMINUS
        
        JMP WHILE
LOOPEND BRK
        RTS