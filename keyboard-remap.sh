#!/bin/sh

KBD=/dev/input/by-path/platform-i8042-serio-0-event-kbd
ONENETBOOK4=/sys/devices/pci0000:00/0000:00:15.0/i2c_designware.0/i2c-*/i2c-SYNA3602:00/0018:0911:5288.0007
X1_CARBONG9=/sys/devices/pci0000:00/0000:00:15.0/i2c_designware.0/i2c-*/i2c-ELAN0672:00/0018:04F3:3187.0001

if [ -e $KBD ] && [ -e $ONENETBOOK4 ]; then exec keyboard-remap-onemix; fi
if [ -e $KBD ] && [ -e $X1_CARBONG9 ]; then exec keyboard-remap-cz; fi
