//
// Created by Justin Herter on 8/24/19.
//

#include "PlantWatcher.h"
#include "PlantExceptions.h"

void PlantWatcher::operator()()
{
    try
    {
        while(*keep_alive)
        {
            statusVec = {true, true, true};

            // Read sensors
            update_sensor_data();

            // Ensure lighting is good
            try {
                update_light();
            }
            catch(LowLightException llEx)
            {
                statusVec[LIGHT] = false;
            }

            //update_pump();

            std::string photo_msg = update_photo();
            if (verbose_output)
            {
                std::cout << photo_msg; // TODO: mutex
            }

            send_plant_data();
            sleep(delay_seconds);
        }
    }
    catch(boost::thread_interrupted&){}

}

void PlantWatcher::update_sensor_data()
{
    // Read in sensor data
    SimpleSerial serial(arduino_addr);
    sensorVals = serial.parseLine();
}

void PlantWatcher::update_light()
{
    int currHour = get_current_hour();

    // Want light on between these hours
    if (currHour >= light_on_hour && currHour <= light_off_hour)
    {
        if (!light_on) // Switch light on
        {
            outlet_ctrl.light_on();
            light_on = true;
        }
        // Raise exception if light is "on" and too dim
        else if (sensorVals[LIGHT] < minVals[LIGHT])
        {
            throw LowLightException();
        }
    }
        // Want light off otherwise
    else if (light_on)
    {
        outlet_ctrl.light_off();
        light_on = false;
    }
}

std::string PlantWatcher::update_photo()
{
    // Want to take at middle of light cycle
    int photo_hour = light_on_hour + (light_off_hour - light_on_hour)/2;
    int curr_hour = get_current_hour();

    std::stringstream msg; // For return string

    // Want photo if at/past photo hour, no photo has been taken,
    // and the light is currently on
    if (curr_hour >= photo_hour && !took_photo && light_on)
    {
        PhotoHandler ph;
        std::cout << ph.update_photo();
    }

    return msg.str();
}

void PlantWatcher::update_pump()
{
    if (sensorVals[MOISTURE] < minVals[MOISTURE]) // Need to run pump
    {
        outlet_ctrl.run_pump_for_time(pump_run_seconds);
        sleep(pump_wait_seconds);
    }
}

int PlantWatcher::get_current_hour()
{
    using namespace boost::posix_time;
    ptime timeLocal = second_clock::local_time();
    return timeLocal.time_of_day().hours();
}

void PlantWatcher::send_plant_data()
{
    CacheIO cacheIo;
    cacheIo.set_values(sensorVals);
    cacheIo.set_statuses(statusVec);
    cacheIo.update_last_write();

    if (verbose_output)
    {
        print_sensor_data();
    }
}

// TODO: Mutex
void PlantWatcher::print_sensor_data()
{
    for (auto &val : sensorVals)
    {
        std::cout << val << " ";
    }

    std::cout << std::endl;
}