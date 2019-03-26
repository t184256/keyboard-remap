#ifndef __SOURCE_EVENT_H
#define __SOURCE_EVENT_H

#ifndef uint16_t
#include <stdint.h>
#endif

struct InEvent {
  uint16_t code;
  uint8_t value;
  unsigned long time;
};

#endif
