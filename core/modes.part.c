#include "source_event.h"

enum ModeResult {
	PASSTHROUGH=0,
	HANDLED=1
};

#define MODES_MAX 6

typedef enum ModeResult (*mode)(struct InEvent);

mode mode_stack[MODES_MAX];
int8_t mode_stack_i;  // points at topmost active mode


void push_mode(mode m) {
	if (mode_stack_i >= MODES_MAX - 1) {
		return;
	}
	mode_stack[++mode_stack_i] = m;
}


void pop_mode(mode m) {
	if (mode_stack[mode_stack_i] != m) {
		return;
	}
	if (!mode_stack_i) {
		return;
	}
	mode_stack_i--;
}


mode peek_mode() {
	return mode_stack[mode_stack_i];
}


void swap_mode(mode victim, mode replacement) {
	int8_t i;
	for (i = mode_stack_i; i >= 0; i--) {
		if (mode_stack[i] == victim) {
			mode_stack[i] = replacement;
			return;
		}
	}
	return;
}


void modes_setup(mode m) {
	mode_stack[0] = m;
	mode_stack_i = 0;
}


void handle_event(struct InEvent ev) {
	int8_t i;
	for (i = mode_stack_i; i >= 0; i--) {
		if (mode_stack[i](ev) == HANDLED)
			return;
		// NOTE: stack manipulations must end with HANDLED!
	}
}
