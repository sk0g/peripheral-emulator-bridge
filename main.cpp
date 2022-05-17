#include <iostream>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "secondCore.h"

void processInputsAndOutputs()
{
    if (SerialCommunication::canReadMessage()) {
        std::cout << "new message read: " << SerialCommunication::popReadMessage() << std::endl;
    }

    if (SerialCommunication::hasMessageToWrite()) {
        std::cout << "w: " << SerialCommunication::popMessageToWrite() << std::endl;
    }
}

int main()
{
    stdio_init_all();

    multicore_reset_core1();
    multicore_launch_core1( &core1_main );

    while (true) {
        processInputsAndOutputs();

        sleep_ms( 500 );
    }

    return 0;
}
