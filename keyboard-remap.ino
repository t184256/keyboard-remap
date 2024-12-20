/* Copyright (c) 2017-2024 Alexander Sosedkin <monk@unboiled.info>.
 * Firmware for my custom PS/2 Kinesis with an Arduino Leonardo inside.
 * Interfaces with PS/2 controller, acts as USB keyboard.
 * Implements a Colemak-inspired layout and does an obscene amount of other things.vdmмьvu
 *
 * Uses Arduino HID-Project library by NicoHood <blog@nicohood.de>.
 * Uses PS2KeyAdvanced by Paul Carpenter, PC Services <sales@pcserviceselectronics.co.uk>.
*/

#include "core/modes.part.c"

#include "arduino/source_ps2keyraw.part.c"
#include "arduino/emitter_keyboard.part.c"

#include "arduino/kinesis_ps2codes_to_locations.map.h"

#include "modes/modes.part.c"


void setup(void) {
  delay(2000);  // To ease reprogramming. TODO: lower later.
  source_setup();
  emitter_setup();
  modes_setup(MODE_INITIAL);
  Serial.begin(9600);
  while(!Serial) {}
  Serial.println("Keyboard online.");
}


void loop() {
  struct InEvent ev = source_read_keycode();
  handle_event(ev);
}
