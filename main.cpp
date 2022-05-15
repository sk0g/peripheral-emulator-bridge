#include <iostream>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "deviceControl.h"
#include "secondCore.cpp"

int main()
{
    stdio_init_all();

//    multicore_launch_core1( &core1_main );

    while (true) {
        printf( "hey\n" );

        sleep_ms( 500 );
    }

    return 0;
}
