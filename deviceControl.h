#include <map>
#include <vector>

#pragma once

enum PinModes
{
    DIGITAL_INPUT,
    DIGITAL_OUTPUT,
    DIGITAL_PWM_INPUT,
    PWM_OUTPUT,
    NONE,
};

class DeviceControl
{
// variables
private:
    const static int pinCount = 29;
    std::map<uint, PinModes> pinConfig;

    static inline uint64_t lastPhaseRisingAt[pinCount];

private:
    static void notifyPinValueChange( uint pinNumber, bool value );

public:
    DeviceControl();

    static void gpio_callback( uint gpio, uint32_t event );

    static void gpio_phaseDuration_callback( uint gpio, uint32_t event );

    void setGpioPinValue( uint pinNumber, bool value, bool notify = false );

    bool getGpioPinValue( uint pinNumber );
};
