#include <hardware/timer.h>
#include "secondCore.h"
#include "deviceControl.h"

uint lastToggledAt = 0;
uint toggleEvery = 5000000;

void core1_main()
{
    DeviceControl dc;

    while (true) {

        if (time_us_64() > lastToggledAt + toggleEvery) {
            dc.setGpioPinValue( 25, !dc.getGpioPinValue( 25 ));
            lastToggledAt = time_us_64();
        }

        tight_loop_contents();
    }
}