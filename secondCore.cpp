#include <string>
#include <pico/stdio.h>
#include <iostream>
#include "secondCore.h"
#include "deviceControl.h"
#include "serialCommunication.h"

std::string inputString;

void readInput()
{
    int c;
    while ((c = getchar_timeout_us( 100 )) != PICO_ERROR_TIMEOUT) {
        inputString += static_cast<char>(c);
    }

    if (!inputString.empty() and inputString.back() == 13) { // reached end of line
        SerialCommunication::addReadMessage( inputString );
        inputString = "";
    }
}

void writeOutputs()
{
    if (!SerialCommunication::hasMessageToWrite()) return;

    std::cout << SerialCommunication::popMessageToWrite() << std::endl;
}

void core1_main()
{
    while (true) {
        readInput();
        writeOutputs();

        tight_loop_contents();
    }
}
