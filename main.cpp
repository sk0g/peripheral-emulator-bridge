#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "secondCore.h"

int main()
{
    stdio_init_all();

    multicore_launch_core1( &core1_main );

    while (true) {
//        printf( "hey\n" );

        sleep_ms( 500 );
    }

    return 0;
}
