STARTUP SECTION OFFSET $FF80
START:
    CLC

;Clear all RAM pages except ZP
    LDY #$0
    STZ $00
    LDA #1
    STA $01
ZLOOP:
    LDA #$0
    STA ($00), y
    INY
    BNE ZLOOP
    INC $01
    LDA $01
    CMP #$20
    BNE ZLOOP

;Clear ZP
    LDA #0
    LDY #$0
ZLOOP2:
    STA $00, y
    INY
    BNE ZLOOP2

;Init Hardware Stack
    LDX #$FF
    TXS

;Top of stack at $1000 for now
    LDA #$10
    STA $33
    LDA #$00
    STA $32

    XREF _main
    JSR _main
IRQV:
    RTI
NMIV:
    RTI

.ORG $FFFA
NMI DW  NMIV
RESET   DW    START
IRQ DW  IRQV
    ENDS
    END