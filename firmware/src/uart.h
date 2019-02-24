#ifndef _UART_H    /* Guard against multiple inclusion */
#define _UART_H


#include "app.h"

void uart_init(void);
bool uart_received_str(void);
int uart_getstring(char *str, int maxlen);

#endif /* _UART_H */
