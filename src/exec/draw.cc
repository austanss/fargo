#include "constants.hh"

static uint32_t ii = 0;

void redraw(uint32_t *buffer) {
    
    for (uint32_t i = 0; i < 800 * 600; i++) {
        buffer[i] = ii++;
    }

    if (ii > 0xFFFFFF) {
        ii = 0;
    }

}
