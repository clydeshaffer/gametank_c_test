STARTUP SECTION OFFSET $FF80
START:
    CLC
    LDY #$0
    STZ $00
    LDA #$01
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

    LDY #$0
ZLOOP2:
    STA $00, y
    INY
    BNE ZLOOP2

    LDX #$FF
    TXS

    LDA #$18
    STA $37
    LDA #$00
    STA $36

    LDA #$18
    STA $35
    LDA #$00
    STA $34

    LDA #$18
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