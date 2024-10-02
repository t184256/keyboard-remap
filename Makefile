CFLAGS=$(shell pkg-config --cflags libevdev)
LDFLAGS=$(shell pkg-config --libs libevdev)
CFLAGS+=-O2

COMMON_DEPS=core/modes.part.c modes/modes.part.c
LINUX_ONLY_DEPS=linux/source_libevdev.part.c linux/emitter_libevdev.part.c
LINUX_DEPS=$(LINUX_ONLY_DEPS) $(COMMON_DEPS)
ARDUINO_DEPS=arduino/emitter_hidproject.part.c
ARDUINO_DEPS+=arduino/kinesis_ps2codes_to_locations.map.h

all: \
	$(LINUX_DEPS) $(ARDUINO_DEPS) \
	keyboard-remap-cz \
	keyboard-remap-jap \
	keyboard-remap-tablet \
	keyboard-remap-onemix

%.c: %.c.in preprocessor.py
	./preprocessor.py < $^ > $@

%.h: %.h.in preprocessor.py
	./preprocessor.py < $^ > $@

keyboard-remap-cz: linux/keyboard-remap-cz.c linux/source_libevdev.part.c linux/emitter_libevdev.part.c modes/modes.part.c linux/cz_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

keyboard-remap-%: $(LINUX_DEPS)
keyboard-remap-%: linux/keyboard-remap-%.c linux/%_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}
