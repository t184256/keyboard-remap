#include "../core/source_event.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <libevdev/libevdev.h>


struct libevdev* in_dev;
int in_dev_fd;


void source_cleanup(void) {
	libevdev_grab(in_dev, LIBEVDEV_UNGRAB);
	libevdev_free(in_dev);
	close(in_dev_fd);
}

void source_setup(void) {
	atexit(source_cleanup);
	in_dev_fd = open(EVDEV_FILENAME, O_RDONLY);
	assert(in_dev_fd > 0);
	int err = libevdev_new_from_fd(in_dev_fd, &in_dev);
	assert(!err);
	err = libevdev_grab(in_dev, LIBEVDEV_GRAB);
	assert(!err);

}


struct InEvent source_read_keycode(void) {
	struct InEvent ev;
	struct input_event iev;
	int res;

	do {
		res = libevdev_next_event(in_dev, LIBEVDEV_READ_FLAG_NORMAL|LIBEVDEV_READ_FLAG_BLOCKING, &iev);
	} while (!(res == LIBEVDEV_READ_STATUS_SUCCESS && iev.type == EV_KEY));
	//printf("<%s %d\n", libevdev_event_code_get_name(iev.type, iev.code), iev.value);

	ev.code = iev.code;
	ev.value = !!iev.value;
	ev.time = (iev.time.tv_sec * (uint64_t)1000) + (iev.time.tv_usec / 1000);

	return ev;
}
