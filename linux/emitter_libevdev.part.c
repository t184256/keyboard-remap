#include "../core/source_event.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev/libevdev-uinput.h>

struct libevdev_uinput* uidev;
int uidev_fd;


void emit_release_all(void);


#define MAX_KEYS 0x300
bool key_states[MAX_KEYS];


void emitter_cleanup(void) {
	emit_release_all();
	libevdev_uinput_destroy(uidev);
	close(uidev_fd);
}

void emitter_setup(void) {
	memset(key_states, 0, MAX_KEYS * sizeof(bool));
	atexit(emitter_cleanup);
	uidev_fd = open("/dev/uinput", O_RDWR);
	assert(uidev_fd > 0);
	int err = libevdev_uinput_create_from_device(in_dev, uidev_fd, &uidev);
	assert(!err);
}

void emit_key(uint16_t code_, bool value) {
	//printf(">%s %d\n", libevdev_event_code_get_name(EV_KEY, code_), value);
	key_states[code_] = value;
	int err = libevdev_uinput_write_event(uidev, EV_KEY, code_, value);
	assert(!err);
	err = libevdev_uinput_write_event(uidev, EV_SYN, SYN_REPORT, 0);
	assert(!err);
	usleep(10000);
}

void emit_press(uint16_t code) {
	emit_key(code, 1);
}

void emit_release(uint16_t code) {
	emit_key(code, 0);
}

void emit_release_all(void) {
	for (int i = 0; i < MAX_KEYS; i++)
		if (key_states[i])
			emit_release(i);
}
