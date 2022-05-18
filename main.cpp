#include <iostream>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "secondCore.h"
#include "deviceControl.h"

void processInputs()
{
    if (!SerialCommunication::canReadMessage()) return;

    std::cout << "new message read: " << SerialCommunication::popReadMessage() << std::endl;
}

uint tracker = 0;

int main()
{
    stdio_init_all();

    multicore_reset_core1();
    multicore_launch_core1( &core1_main );

    sleep_ms( 200 );

    DeviceControl dc;

    while (true) {
        tracker++;
        processInputs();

        if (tracker % 1000000 == 0)
            dc.setGpioPinValue(
                25,
                !dc.getGpioPinValue( 25 ),
                true );

        tight_loop_contents();
    }

    return 0;
}
