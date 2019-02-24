#include "fifo.h"
#include "system/int/sys_int.h"

#define IRQ_DISABLE() SYS_INT_PROCESSOR_STATUS __status = SYS_INT_StatusGetAndDisable()
#define IRQ_ENABLE() SYS_INT_StatusRestore(__status)


void fifo_init(FIFO *fifo, uint8_t len, char *buf) {
	fifo->first = 0;
	fifo->count = 0;
	fifo->len = len;
	fifo->buf = buf;
}

// Nachricht in FIFO schieben
bool fifo_push(FIFO *fifo, const char item) {
	IRQ_DISABLE();

	bool res = false;

	if(fifo->count < fifo->len) {
		
		res = true;

		uint8_t idx = (fifo->first + fifo->count) % fifo->len;
		fifo->buf[idx] = item;

		++fifo->count;
	}

	IRQ_ENABLE();

	return res;
}

// Erste Nachricht aus FIFO entnehmen
bool fifo_pop(FIFO *fifo, char *item) {
	IRQ_DISABLE();

	bool res = false;
	if(fifo->count > 0) {

		res = true;

		*item = fifo->buf[fifo->first];

		--fifo->count;

		fifo->first = (fifo->first + 1) % fifo->len;
	}

	IRQ_ENABLE();

	return res;
}

bool fifo_is_empty(const FIFO *fifo) {
	bool empty;
	IRQ_DISABLE();

	empty = fifo->count == 0;

	IRQ_ENABLE();
	return empty;
}

bool fifo_is_full(const FIFO *fifo) {
	bool full;
	IRQ_DISABLE();


	full = fifo->count == fifo->len;

	IRQ_ENABLE();
	return full;
}
