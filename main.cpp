#include <iostream>
#include <list>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "secondCore.h"
#include "deviceControl.h"

bool execPulse( const string &message, DeviceControl *dc );

bool execSetValue( const string &message, DeviceControl *dc );

bool echoUnrecognised( const string &message );

void processInputs( DeviceControl *dc )
{
    if ( !SerialCommunication::canReadMessage()) return;

    auto message = SerialCommunication::popReadMessage();

    execPulse( message, dc ) or execSetValue( message, dc ) or echoUnrecognised( message );
}

std::list<std::tuple<uint, uint64_t>> pulses;

void startPulsingPin( uint port, uint duration_us, DeviceControl *dc )
{
    const auto currentTime_us = time_us_64();
    dc->setGpioPinValue( port, true );
    pulses.emplace_back( std::make_tuple( port, currentTime_us + duration_us ));

    for ( auto const &[p, d]: pulses ) std::cout << p << " | " << d << std::endl;
}

void tickPulsedPins( DeviceControl *dc )
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

int main()
{
    stdio_init_all();

    multicore_reset_core1();
    multicore_launch_core1( &core1_main );

    sleep_ms( 200 );

    DeviceControl dc;

    while ( true ) {
        processInputs( &dc );
        tickPulsedPins( &dc );

        tight_loop_contents();
    }

    return 0;
}

bool execPulse( const string &message, DeviceControl *dc )
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

bool execSetValue( const string &message, DeviceControl *dc )
{
    uint port;

    auto hits = sscanf( message.c_str(), "n%i", &port ); // n25 | n02 | n9
    if ( hits == 1 ) {
        dc->setGpioPinValue( port, true );
        SerialCommunication::addMessageToWrite( "? pin -> high" );
        return true;
    }

    hits = sscanf( message.c_str(), "f%i", &port ); // f20 | f08 | f11
    if ( hits == 1 ) {
        dc->setGpioPinValue( port, false );
        SerialCommunication::addMessageToWrite( "? pin -> low" );
        return true;
    }

    return false;
}

bool echoUnrecognised( const string &message )
{
    std::cout << "? " << message << std::endl;
    return true;
}
