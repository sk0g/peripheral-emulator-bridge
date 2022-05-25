#include "pico/stdlib.h"

#include "deviceControl.h"
#include "serialCommunication.h"
#include "cstdio"

DeviceControl::DeviceControl()
{
    DeviceControl::pinConfig = {
        { 0,  NONE },
        { 1,  NONE },
        { 2,  DIGITAL_INPUT },
        { 3,  DIGITAL_INPUT },
        { 4,  DIGITAL_INPUT },
        { 5,  DIGITAL_INPUT },
        { 6,  DIGITAL_INPUT },
        { 7,  DIGITAL_INPUT },
        { 8,  DIGITAL_INPUT },
        { 9,  DIGITAL_INPUT },
        { 10, DIGITAL_INPUT },
        { 11, DIGITAL_INPUT },
        { 12, DIGITAL_INPUT },
        { 13, DIGITAL_PWM_INPUT },
        { 14, DIGITAL_OUTPUT },
        { 15, DIGITAL_OUTPUT },
        { 16, DIGITAL_OUTPUT },
        { 17, DIGITAL_OUTPUT },
        { 18, DIGITAL_OUTPUT },
        { 19, DIGITAL_OUTPUT },
        { 20, DIGITAL_OUTPUT },
        { 21, DIGITAL_OUTPUT },
        { 22, NONE },
        { 23, NONE },
        { 24, NONE },
        { 25, DIGITAL_OUTPUT },
        { 26, DIGITAL_OUTPUT },
        { 27, DIGITAL_OUTPUT },
        { 28, DIGITAL_OUTPUT },
    };

    for ( auto &[pinNumber, pinMode]: DeviceControl::pinConfig ) {
        switch ( pinMode ) {
            case DIGITAL_OUTPUT:
                gpio_init( pinNumber );
                gpio_set_dir( pinNumber, GPIO_OUT );

                break;

            case DIGITAL_INPUT:
                gpio_init( pinNumber );
                gpio_set_dir( pinNumber, GPIO_IN );

                gpio_set_irq_enabled_with_callback(
                    pinNumber, 0b1100, true, gpio_callback );

                break;

            case DIGITAL_PWM_INPUT:
                gpio_init( pinNumber );
                gpio_set_dir( pinNumber, GPIO_IN );

                gpio_set_irq_enabled_with_callback(
                    pinNumber, 0b1100, true, gpio_phaseDuration_callback );

                break;

            case PWM_OUTPUT:
                gpio_init( pinNumber );
                gpio_set_function( pinNumber, GPIO_FUNC_PWM );

                break;

            case NONE:
                break;
        }
    }
}

void DeviceControl::gpio_callback( uint gpio, uint32_t event )
{
    bool isHighSignal = event == 8;
    notifyPinValueChange( gpio, isHighSignal );
}

void DeviceControl::gpio_phaseDuration_callback( uint gpio, uint32_t event )
{
    bool isHighSignal = event == 8;

    // pin filtering does not work correctly in the current SDK
    if ( DeviceControl::pinConfig[gpio] != DIGITAL_PWM_INPUT ) return;

    if ( isHighSignal ) {
        DeviceControl::lastPhaseRisingAt[gpio] = time_us_64();
    } else {
        auto pulseDuration = (time_us_64() - DeviceControl::lastPhaseRisingAt[gpio]) / 1e3;

        // maybe should avoid sending relatively unchanged phase durations
        char message[20];
        sprintf( message, "%02i^%0.3f", gpio, pulseDuration );

        SerialCommunication::addMessageToWrite( message );
    }
}


void DeviceControl::setGpioPinValue( uint pinNumber, bool value, bool notify )
{
    gpio_put( pinNumber, value );

    if ( notify ) notifyPinValueChange( pinNumber, value );
}

bool DeviceControl::getGpioPinValue( uint pinNumber )
{
    return gpio_get( pinNumber );
}

void DeviceControl::notifyPinValueChange( uint pinNumber, bool value )
{
    char message[20];
    sprintf( message, "%02i|%i",
             pinNumber,
             value ? 1 : 0
    );
    SerialCommunication::addMessageToWrite( message );
}

