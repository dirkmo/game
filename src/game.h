#ifndef GAME_H
#define	GAME_H

#include <stdint.h>

#define GAME_TIMER_MS 10

void game_init(void);
void game_timer_callback(void);
void game_loop(void);

#endif	/* GAME_H */
