#include <map>
#include <vector>

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
    const std::map<uint, PinModes> pinConfig = {
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

    static inline uint64_t lastPhaseRisingAt[pinCount];
//    static double lastPhaseWidthSent[pinCount]; // needed if communication will be 'throttled'

private:
    static void notifyPinValueChange( uint pinNumber, bool value );

public:
    DeviceControl();

    static void gpio_callback( uint gpio, uint32_t event );

    static void gpio_phaseDuration_callback( uint gpio, uint32_t event );

    void setGpioPinValue( uint pinNumber, bool value, bool notify = false );

    bool getGpioPinValue( uint pinNumber );
};

