CFLAGS=$(shell pkg-config --cflags libevdev)
LDFLAGS=$(shell pkg-config --libs libevdev)

all: \
	modes/modes.part.c \
	arduino/emitter_hidproject.part.c \
	arduino/kinesis_ps2codes_to_locations.map.h \
	linux/jap_keys_to_locations.map.h \
	linux/tablet_keys_to_locations.map.h \
	keyboard-remap-jap \
	keyboard-remap-tablet

%.c: %.c.in
	./preprocessor.py < $^ > $@

%.h: %.h.in
	./preprocessor.py < $^ > $@

keyboard-remap-jap: linux/keyboard-remap-jap.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

keyboard-remap-tablet: linux/keyboard-remap-tablet.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}
