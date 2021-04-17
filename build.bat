WDC02AS startup.asm
WDC02CC main.c
WDCLN -HB -CE000 -D200, main.obj startup.obj -LC
dd bs=57344 skip=1 if=main.bin of=main.gtr