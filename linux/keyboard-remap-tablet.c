/* Copyright (c) 2017-2019 Alexander Sosedkin <monk@unboiled.info>.
 * Remaps my japanese laptop keyboard.
 * Implements a Colemak-inspired layout and does an obscene amount of other things.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../core/modes.part.c"

#define EVDEV_FILENAME "/dev/input/event20"
#include "source_libevdev.part.c"
#include "emitter_libevdev.part.c"

#include "tablet_keys_to_locations.map.h"

#include "../modes/modes.part.c"


int main() {
	source_setup();
	emitter_setup();
	modes_setup(MODE_INITIAL);
	printf("Online.\n");
	while (1) {
		struct InEvent ev = source_read_keycode();
		handle_event(ev);
	}
}
