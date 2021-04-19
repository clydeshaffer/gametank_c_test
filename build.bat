WDC02AS T0.ASM
WDC02AS ASSETS.ASM
WDC02CC main.c
WDCLN -HB -CE1FC -D500, main.obj assets.obj T0.obj -LC -T
dd bs=57344 skip=1 if=main.bin of=main.gtr