#include <hardware/timer.h>
#include "secondCore.h"
#include "deviceControl.h"

uint lastToggledAt_us = 0;
uint toggleEvery_us = 5000000; // 5 seconds

void maybeToggleLed( DeviceControl *dc )
{
    if (time_us_64() > lastToggledAt_us + toggleEvery_us) {
        dc->setGpioPinValue( 25, !dc->getGpioPinValue( 25 ));
        lastToggledAt_us = time_us_64();
    }
}

void core1_main()
{
    DeviceControl dc;

    while (true) {
        maybeToggleLed( &dc );

        tight_loop_contents();
    }
}