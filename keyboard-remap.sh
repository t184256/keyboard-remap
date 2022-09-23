#!/bin/sh

KBD=/dev/input/by-path/platform-i8042-serio-0-event-kbd
ONENETBOOK4_DEV=/sys/devices/pci0000:00/0000:00:15.0/i2c_designware.0/i2c-*/i2c-SYNA3602:00/0018:0911:5288.000*
X1_CARBONG9_DEV=/sys/devices/pci0000:00/0000:00:15.0/i2c_designware.0/i2c-*/i2c-ELAN0672:00/0018:04F3:3187.0001
ONENETBOOK4_SERIAL1=215311150005
X1_CARBON_G9_SERIAL=PF3FBEP5

[ -z $remapper ] && [ -e $ONENETBOOK4_DEV ] && remapper=keyboard-remap-onemix
[ -z $remapper ] && [ -e $X1_CARBONG9_DEV ] && remapper=keyboard-remap-cz
if [ -z $remapper ] && command -v dmidecode >/dev/null; then
	SERIAL=$(dmidecode -t system-serial-number)
	[ "$SERIAL" = $ONENETBOOK4_SERIAL1 ] && remapper=keyboard-remap-onemix
	[ "$SERIAL" = $X1_CARBON_G9_SERIAL ] && remapper=keyboard-remap-cz
fi

if [ -e $KBD ] && [ -e $ONENETBOOK4 ]; then remapper=keyboard-remap-onemix; fi
if [ -e $KBD ] && [ -e $X1_CARBONG9 ]; then remapper=keyboard-remap-cz; fi

[ -n "$remapper" ] && exec $remapper || exit 1
