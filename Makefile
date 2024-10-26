CFLAGS=$(shell pkg-config --cflags libevdev)
LDFLAGS=$(shell pkg-config --libs libevdev)
CFLAGS+=-O2

COMMON_DEPS=core/modes.part.c modes/modes.part.c
COMMON_DEPS+=langs/unicode.part.c langs/cz.h langs/ru.h
LINUX_ONLY_DEPS=linux/source_libevdev.part.c linux/emitter_libevdev.part.c
LINUX_DEPS=$(LINUX_ONLY_DEPS) $(COMMON_DEPS)
ARDUINO_DEPS=arduino/emitter_keyboard.part.c
ARDUINO_DEPS+=arduino/kinesis_ps2codes_to_locations.map.h

all: \
	$(LINUX_DEPS) $(ARDUINO_DEPS) \
	langs/mappings_generated.json \
	keyboard-remap-cz \
	keyboard-remap-jap \
	keyboard-remap-tablet \
	keyboard-remap-onemix

%.c: %.c.in preprocessor.py
	./preprocessor.py < $^ > $@

%.h: %.h.in preprocessor.py
	./preprocessor.py < $^ > $@

langs/%.h: langs/%.chars langs/genunicode.py
	./langs/genunicode.py < $^ > $@

keyboard-remap-%: $(LINUX_DEPS)
keyboard-remap-%: linux/keyboard-remap-%.c linux/%_keys_to_locations.map.h
	${CC} $< -o $@ ${CFLAGS} ${LDFLAGS}

langs/mappings_generated.json: langs/genandroid.py langs/mappings_base.json
langs/mappings_generated.json: langs/cz.chars langs/ru.chars
	(cat langs/cz.chars langs/ru.chars) | ./langs/genandroid.py > $@
