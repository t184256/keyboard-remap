all: \
	modes/modes.part.c \
	arduino/emitter_hidproject.part.c \
	arduino/kinesis_ps2codes_to_locations.map.h

%.c: %.c.in
	./preprocessor.py < $^ > $@

%.h: %.h.in
	./preprocessor.py < $^ > $@
