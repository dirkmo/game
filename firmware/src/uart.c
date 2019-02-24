#include "uart.h"
#include "app.h"

static char fifo_rxbuf[128];

static FIFO fifo_rx = {
    .first = 0,
    .count = 0,
    .len = sizeof(fifo_rxbuf),
    .buf = fifo_rxbuf
};

static int received = 0;

static void receive_callback(const SYS_MODULE_INDEX index)
{
    char c = DRV_USART0_ReadByte();
    if( c == '\r' || c == '\n' ) {
        received++;
    }
    fifo_push(&fifo_rx, c);
}

void uart_init(void) {
    DRV_USART_ByteReceiveCallbackSet(DRV_USART_INDEX_0, receive_callback);
}

bool uart_received_str(void) {
    return received > 0;
}

int uart_getstring(char *str, int maxlen) {
    char c;
    int len = 0;
    while( len < maxlen-1 && fifo_pop(&fifo_rx, &c) ) {
        len++;
        *str++ = c;
        if( c == '\r' || c == '\n') {
            received--;
            break;
        }
    }
    *str = 0;
    return len;
}
