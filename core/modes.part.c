#include "source_event.h"

#define HANDLED true
#define PASSTHROUGH false

#define MODES_MAX 6

typedef bool (*mode)(struct InEvent);

mode mode_stack[MODES_MAX];
int8_t mode_stack_i;  // points at topmost active mode


void push_mode(mode m) {
	Serial.println("push_mode");
	if (mode_stack_i >= MODES_MAX - 1) {
		Serial.println("Mode overflow denied!");
		return;
	}
	mode_stack[++mode_stack_i] = m;
}


void pop_mode(mode m) {
	Serial.println("pop_mode");
	if (mode_stack[mode_stack_i] != m) {
		Serial.println("Wrong mode pop denied!");
		return;
	}
	if (!mode_stack_i) {
		Serial.println("Zero mode pop denied!");
		return;
	}
	mode_stack_i--;
}


mode peek_mode() {
	return mode_stack[mode_stack_i];
}


void swap_mode(mode victim, mode replacement) {
	Serial.println("swap_mode");
	int8_t i;
	for (i = mode_stack_i; i >= 0; i--) {
		if (mode_stack[i] == victim) {
			mode_stack[i] = replacement;
			return;
		}
	}
	Serial.println("Mode switch failed, no victim!");
	return;
}


void modes_setup(mode m) {
	mode_stack[0] = m;
	mode_stack_i = 0;
}


void handle_event(InEvent ev) {
	int8_t i;
	for (i = mode_stack_i; i >= 0; i--) {
		if (mode_stack[i](ev) == HANDLED)
			return;
		// NOTE: stack manipulations must end with HANDLED!
	}
	Serial.println("Unhandled event!");
	Serial.println(ev.code, HEX);
}
