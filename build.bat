WDC02AS T0.ASM
WDC02CC main.c
WDCLN -HB -CE000 -D200, main.obj T0.obj -LC -T
dd bs=57344 skip=1 if=main.bin of=main.gtr