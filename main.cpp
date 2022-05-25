#include <iostream>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "pico/multicore.h"
#include "serialCommunication.h"
#include "pulsePins.h"
#include "secondCore.h"
#include "deviceControl.h"


bool execSetValue( const string &message, DeviceControl *dc );

bool echoUnrecognised( const string &message );

void processInputs( DeviceControl *dc )
{
    if ( !SerialCommunication::canReadMessage()) return;

    auto message = SerialCommunication::popReadMessage();

    PulsePins::exec( message, dc ) or execSetValue( message, dc ) or echoUnrecognised( message );
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
        PulsePins::tick( &dc );

        tight_loop_contents();
    }

    return 0;
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
