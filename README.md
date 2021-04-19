# gametank_c_test

Some test code for working out how to use WDC's C compiler for the W65C02S,
particularly to run on the GameTank and its emulator

After obtaining the WDCTools package from https://wdc65xx.com/WDCTools
you'll need to edit zpage.inc and wdc02cc.cfg in your install directory to remove the conditionals for USING_134 which the compiler doesn't seem to fully obey, using the 134 clause even when building for 65C02.