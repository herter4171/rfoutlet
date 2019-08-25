//
// Created by Justin Herter on 8/24/19.
//
#include <unistd.h>

#include "RCSwitch.h"
#include "OutletController.h"

void OutletController::light_on()
{
    send_code(light_code_on, true);
}

void OutletController::light_off()
{
    send_code(light_code_on, false);
}

void OutletController::flicker_test(int cycles)
{
    for (int i = 0; i < cycles; i++)
    {
        send_code(light_code_on, true);
        sleep(1);
        send_code(light_code_on, false);
        sleep(1);
    }
}

void OutletController::run_pump_for_time(int seconds)
{
    send_code(pump_code_on, true);
    sleep(seconds);
    send_code(pump_code_on, false);
}

void OutletController::send_code(unsigned int code, bool want_on)
{
    if (wiringPiSetup () == -1) {
    }

    // Instantiate and configure RCSwitch
    RCSwitch switchInst = RCSwitch();
    switchInst.setPulseLength(pulseLen);
    switchInst.enableTransmit(outPin);

    // Switch off code is 9 more than the on code
    if (!want_on)
    {
        code += 9;
    }

    // Send pulse.  Not sure what 24 does (legacy)
    switchInst.send(code, 24);
}