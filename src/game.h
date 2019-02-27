#ifndef GAME_H
#define	GAME_H

#include <stdint.h>

#define GAME_TIMER_MS 10

typedef enum {
    BUTTON_UP      = 0x01,
    BUTTON_DOWN    = 0x02,
    BUTTON_LEFT    = 0x04,
    BUTTON_RIGHT   = 0x08,
    BUTTON_ACTION0 = 0x10,
    BUTTON_ACTION1 = 0x20,
    BUTTON_ACTION2 = 0x40,
    BUTTON_ACTION3 = 0x80,
} buttons_t;

void game_init(void);
void game_timer_callback(void);
void game_button_callback(uint32_t _buttons);
void game_loop(void);

#endif	/* GAME_H */
