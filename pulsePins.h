#include <iostream>
#include "deviceControl.h"
#include <list>

namespace PulsePins
{
    inline std::list<std::tuple<uint, uint64_t>> pulses;

    bool exec( const std::string &message, DeviceControl *dc );

    void startPulsingPin( uint port, uint duration_us, DeviceControl *dc );

    void tick( DeviceControl *dc );
};