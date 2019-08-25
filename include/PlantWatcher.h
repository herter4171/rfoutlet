//
// Created by Justin Herter on 8/24/19.
//

#ifndef RFOUTLET_PLANTWATCHER_H
#define RFOUTLET_PLANTWATCHER_H

#include <string>
#include <sstream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <filesystem>

#include <boost/date_time.hpp>

#include "SimpleSerial.h"
#include "OutletController.h"
#include "PlantExceptions.h"

class PlantWatcher
{
public:
    // Indices for mapping Arduino feed
    enum SENSOR_INDS{LIGHT, MOISTURE, RESERVE};

    // Instantiate with light assumed off
    PlantWatcher(): outlet_ctrl()
    {
        light_on = false;
        took_photo = false;
    }

    // Read data from Arduino, and store values
    void update_sensor_data();

    // Ensures light is on/off for time of day
    // Throws LowLightException if daytime and low light
    void update_light();

    // Runs the pump
    void update_pump();

    // Takes plant picture
    std::string update_photo();

private:
    // Convenience wrapper for boost::posix_time
    int get_current_hour();

    std::string get_date_timestamp();

    // Makes images folder if not present
    bool ensure_image_folder();

    // Store latest sensor data
    int light_val, moist_val, reserv_val;

    // Setpoints for minimum values
    const int light_min = 10,
              moist_min = 110,
              reserve_min = 5;

    bool light_on; // Reflects state of the light
    bool took_photo; // True after photo taken

    // Want on from 8 am to 8 pm
    const int light_on_hour = 8,
              light_off_hour = 20;

    // Want to run the pump 5 seconds and wait ten to recheck
    const int pump_run_seconds = 5,
              pump_wait_seconds = 10;

    // Address Arduino always shows up at
    const std::string arduino_addr = "/dev/ttyACM0";

    // Want to invoke raspistill to take 1024x768 jpg
    const std::string camera_cmd_pfx = "raspistill -w 1024 -h 768 -o ",
                      camera_cmd_dir = "/home/pi/images",
                      camera_cmd_ext = ".jpg";

    OutletController outlet_ctrl;
};

#endif //RFOUTLET_PLANTWATCHER_H