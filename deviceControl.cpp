#include "pico/stdlib.h"

#include "deviceControl.h"

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
