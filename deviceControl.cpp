#include <iostream>
#include "pico/stdlib.h"

#include "deviceControl.h"
#include "serialCommunication.h"
#include "cstdio"

DeviceControl::DeviceControl()
{
    for (auto &[pinNumber, pinMode]: pinConfig) {
        switch (pinMode) {
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

            case PWM_INPUT:
                gpio_set_function( pinNumber, GPIO_FUNC_PWM );

                break;

            case PWM_OUTPUT:
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


void DeviceControl::setGpioPinValue( uint pinNumber, bool value, bool notify )
{
    gpio_put( pinNumber, value );

    if (notify) notifyPinValueChange( pinNumber, value );
}

bool DeviceControl::getGpioPinValue( uint pinNumber )
{
    return gpio_get( pinNumber );
}

void DeviceControl::notifyPinValueChange( uint pinNumber, bool value )
{
    char message[20];
    sprintf( message, "%i|%s",
             pinNumber,
             value ? "1" : "0"
    );
    SerialCommunication::addMessageToWrite( message );
}

