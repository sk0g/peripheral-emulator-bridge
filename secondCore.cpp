#include <hardware/timer.h>
#include <string>
#include <iostream>
#include <pico/time.h>
#include <pico/stdio.h>
#include "secondCore.h"
#include "deviceControl.h"
#include "serialCommunication.h"

uint lastToggledAt_us = 0;
uint toggleEvery_us = 5000000; // 5 seconds
std::string inputString;

void maybeToggleLed( DeviceControl *dc )
{
    if (time_us_64() > lastToggledAt_us + toggleEvery_us) {
        dc->setGpioPinValue( 25, !dc->getGpioPinValue( 25 ));
        lastToggledAt_us = time_us_64();
        SerialCommunication::addMessageToWrite( "toggling LED" );
    }
}

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

void core1_main()
{
    DeviceControl dc;

    while (true) {
        maybeToggleLed( &dc );
        readInput();

        tight_loop_contents();
    }
}