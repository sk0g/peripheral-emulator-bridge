#include "pulsePins.h"
#include "pico/time.h"
#include "serialCommunication.h"

namespace PulsePins
{
    bool exec( const std::string &message, DeviceControl *dc )
    {
        uint port, duration_us;

        auto hits = sscanf( message.c_str(), "p%i,%i", &port, &duration_us ); // p20,1000 | p14,10
        if ( hits == 2 ) {
            startPulsingPin( port, duration_us, dc );
            SerialCommunication::addMessageToWrite( "? pulsing a pin" );
            return true;
        }

        return false;
    }

    void startPulsingPin( uint port, uint duration_us, DeviceControl *dc )
    {
        const auto currentTime_us = time_us_64();
        dc->setGpioPinValue( port, true );
        pulses.emplace_back( std::make_tuple( port, currentTime_us + duration_us ));
    }

    void tick( DeviceControl *dc )
    {
        auto currentTime_us = time_us_64();
        std::list<std::tuple<uint, uint64_t>> itemsToRemove;

        for ( auto const &pulse: pulses ) {
            if ( std::get<1>( pulse ) <= currentTime_us ) { // pin should stop pulsing
                dc->setGpioPinValue( std::get<0>( pulse ), false );

                itemsToRemove.emplace_back( pulse );
            }
        }

        for ( auto item: itemsToRemove ) pulses.remove( item );
    }
}