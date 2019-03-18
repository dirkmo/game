#include "buttons.h"
#include <stdint.h>

static uint32_t s_buttons;
static uint32_t s_buttons_pressed;
static uint32_t s_buttons_released;


void button_callback(uint32_t _buttons) {
    if( s_buttons != _buttons ) {
        const uint32_t change = s_buttons ^ _buttons;
        s_buttons_pressed |= s_buttons & change;
	s_buttons_released |= ~s_buttons & change;
        s_buttons = _buttons;
    }
}

bool button_pressed(uint32_t button_mask) {
    bool state = (s_buttons_pressed & button_mask) != 0;
    s_buttons_pressed &= ~button_mask;
    return state;
}

bool button_released(uint32_t button_mask) {
    bool state = (s_buttons_released & button_mask) != 0;
    s_buttons_released &= ~button_mask;
    return state;
}

bool button_is_down(uint32_t button_mask) {
    return s_buttons & button_mask;
}

bool button_up(uint32_t button_mask) {
    return ~s_buttons & button_mask;
}

uint32_t button_status(void) {
    return s_buttons;
}
