#include <stdio.h>
#include <ctype.h>
#include "app.h"
#include "uart.h"
#include "dem128064a.h"
#include "game.h"
#include "salma.h"

APP_DATA appData;

char *trim(char *s) {
    char *w = s;
    // trim left
    while(isspace(*w)) ++w;
    s = w;
    if( *w ) {
        // trim right
        while(*w) ++w; // search end
        while(w>s && isspace(w[-1])) --w;
        *w = 0;
    }
    return s;
}

void delay(int val) {
    volatile int i = 0;
    while( i < val ) {
        i++;
        _nop();
    }
}
void timer_callback(uintptr_t context, uint32_t alarmCount) {
    game_timer_callback();
}

void APP_Initialize ( void )
{
    /* Place the App state machine in its initial state. */
    appData.state = APP_STATE_INIT;
    uart_init();
        
}

void APP_Tasks ( void )
{

    /* Check the application's current state. */
    switch ( appData.state )
    {
        /* Application's initial state. */
        case APP_STATE_INIT:
        {
            bool appInitialized = true;
       
            
            if( DRV_TMR_AlarmRegister(
                DRV_TMR_INDEX_0, // DRV_HANDLE handle,
                3125, // uint32_t divider
                true, // bool isPeriodic
                NULL, // uintptr_t context
                timer_callback
            ) ) {
                printf("Timer registered.\n");
            } else {
                printf("ERROR: Timer could not be registered.\n");
            }
            DRV_TMR_Start(DRV_TMR_INDEX_0);
            DRV_TMR_AlarmEnable(DRV_TMR_INDEX_0, true);
            
            game_init();        

            if (appInitialized)
            {
                appData.state = APP_STATE_SERVICE_TASKS;
            }
            break;
        }

        case APP_STATE_SERVICE_TASKS:
        {
            game_loop();
            if( uart_received_str() ) {
                char str[128];
                uart_getstring(str, sizeof(str));
                char *s = trim(str);
                printf("Empfangen: '%s'\n", s);
                int val;
                if( strcmp(s, "clear") == 0 ) {
                    dem_fill(0);
                } else if( sscanf(s, "fill %d", &val) == 1 ) {
                    dem_fill(val);
                } else if( strcmp(s, "raw") == 0 ) {
                    dem_copy_raw(pic_raw_salma);
                } else if( strcmp(s, "pic") == 0 ) {
                    dem_copy(pic_salma);
                } else if( strcmp(s, "enable") == 0 ) {
                    dem_enable();
                } else if( strcmp(s, "disable") == 0 ) {
                    dem_disable();
                }
            }
            break;
        }

        default:
        {
            /* TODO: Handle error in application's state machine. */
            break;
        }
    }
}

 

/*******************************************************************************
 End of File
 */
