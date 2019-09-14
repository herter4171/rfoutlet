//
// Created by Justin Herter on 8/24/19.
//

#ifndef RFOUTLET_OUTLETCONTROLLER_H
#define RFOUTLET_OUTLETCONTROLLER_H

#include <unistd.h>
#include <initializer_list>
#include "RCSwitch.h"

class OutletController
{

public:

    OutletController();

    // Light switching
    void light_on();
    void light_off();

    // Pump operation
    void run_pump_for_time(int seconds);

    // Turns light on and off a bit
    void flicker_test(int cycles);

private:
    // Convenience wrapper for light switching
    void send_code(unsigned int code, bool want_on);

    // On codes for channel 1 (light)
    // and channel 2 (pump)
    const int light_code_on = 1398067;
    const int pump_code_on = 1398211;

    // Defaults for wiringpi pin and pulse length
    const int outPin = 0;
    const int pulseLen = 189;

};


#endif //RFOUTLET_OUTLETCONTROLLER_H
