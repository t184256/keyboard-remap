CFLAGS=$(shell pkg-config --cflags libevdev)
LDFLAGS=$(shell pkg-config --libs libevdev)

all: \
	modes/modes.part.c \
	arduino/emitter_hidproject.part.c \
	arduino/kinesis_ps2codes_to_locations.map.h \
	linux/cz_keys_to_locations.map.h \
	linux/jap_keys_to_locations.map.h \
	linux/tablet_keys_to_locations.map.h \
	linux/onemix_keys_to_locations.map.h \
	keyboard-remap-cz \
	keyboard-remap-jap \
	keyboard-remap-tablet \
	keyboard-remap-onemix

%.c: %.c.in
	./preprocessor.py < $^ > $@

%.h: %.h.in
	./preprocessor.py < $^ > $@

keyboard-remap-cz: linux/keyboard-remap-cz.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c linux/cz_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

keyboard-remap-jap: linux/keyboard-remap-jap.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c linux/jap_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

keyboard-remap-tablet: linux/keyboard-remap-tablet.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c linux/tablet_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

keyboard-remap-onemix: linux/keyboard-remap-onemix.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c linux/onemix_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

