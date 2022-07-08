#!/bin/sh

KBD=/dev/input/by-path/platform-i8042-serio-0-event-kbd
ONENETBOOK4=/sys/devices/pci0000:00/0000:00:15.0/i2c_designware.0/i2c-16/i2c-SYNA3602:00/0018:0911:5288.0007

if [ -e $KBD ] && [ -e $ONENETBOOK4 ]; then exec keyboard-remap-onemix; fi
