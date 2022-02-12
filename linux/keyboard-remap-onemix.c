/* Copyright (c) 2017-2021 Alexander Sosedkin <monk@unboiled.info>.
 * Remaps my One Netbook OneMix 4 keyboard.
 * Implements a Colemak-inspired layout and does an obscene amount of other things.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../core/modes.part.c"

#define EVDEV_FILENAME "/dev/input/by-path/platform-i8042-serio-0-event-kbd"
#include "source_libevdev.part.c"
#include "emitter_libevdev.part.c"

// Do not indicate mode switches
#define EXT_NOTIFY_ON()
#define EXT_NOTIFY_OFF()
// Using Gnome's Focus Switcher for window focus switching
#define WINDOW_FOCUS_MOD(x) do { \
		emit_press(KEY_LEFTMETA); \
		emit_press(KEY_LEFTALT); \
		emit_press(KEY_LEFTCTRL); \
		emit_press(x); emit_release(x); \
		emit_release(KEY_LEFTCTRL); \
		emit_release(KEY_LEFTALT); \
		emit_release(KEY_LEFTMETA); \
	} while (0)
#define WINDOW_MOVE_MOD(x) do { \
		emit_press(KEY_LEFTMETA); emit_press(x); \
		emit_release(x); emit_press(KEY_LEFTMETA); \
	} while (0)
#define WINDOW_MOVE_LEFT() WINDOW_MOVE_MOD(KEY_LEFT)
#define WINDOW_MOVE_DOWN() WINDOW_MOVE_MOD(KEY_DOWN)
#define WINDOW_MOVE_UP() WINDOW_MOVE_MOD(KEY_UP)
#define WINDOW_MOVE_RIGHT() WINDOW_MOVE_MOD(KEY_RIGHT)

#include "onemix_keys_to_locations.map.h"

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
