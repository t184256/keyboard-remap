#include "../core/source_event.h"


#include <PS2KeyRaw.h>


// PS/2 stuff
#define EXTENDED_FLAG 0xE0
#define RELEASE_FLAG 0xF0

// Wiring
#define PIN_DATA 4  // To DATA	pin of PS/2 header
#define PIN_CLOCK 3 // To CLOCK pin of PS/2 header


PS2KeyRaw ps2;

void source_setup(void) {
	ps2.begin(PIN_DATA, PIN_CLOCK);
}


bool extended_flag_happened = 0;
bool release_flag_happened = 0;

struct InEvent source_read_keycode(void) {
	uint8_t r;
	uint16_t c;
	struct InEvent ev;

	while (1) {
		if (ps2.available()) {
			r = ps2.read();

			if (r == 0xE0)
				extended_flag_happened = 1;
			else if (r == 0xF0)
				release_flag_happened = 1;
			else
				break;
		}
	}

	c = r;

	if (r == 0x12 && extended_flag_happened) c = 0x7C;  // fix PRINTSCREEN press/release mismatch
	if (r == 0x14 && extended_flag_happened) c = 0x77;  // fix PAUSE press/release mismatch

	// TODO: debounce a bouncy PgDn on my of my keyboards	FIXME
	//if (c == 0x171 && !release_flag_happened) delay(20);

	if (extended_flag_happened) c |= 0x100;	 // let's embed that into the code itself

	ev.code = c;
	ev.value = !release_flag_happened;
	ev.time = millis;

	extended_flag_happened = release_flag_happened = 0;
	return ev;
}
