//
// Created by Justin Herter on 8/24/19.
//

#include "PlantWatcher.h"
#include "PlantExceptions.h"

void PlantWatcher::operator()()
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
    //update_photo();
    send_plant_data();
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
        // Try to use expected dir.  Fall-back to home.
        // If home isn't defined, bigger problems exist.
        std::string pathStr = camera_cmd_dir;
        if (!ensure_image_folder())
        {
            pathStr = std::getenv("HOME");
        }

        // Add filename to path
        pathStr += "/" + get_date_timestamp() + camera_cmd_ext;

        // Run raspistill to take 1024x768 jpg
        std::system(std::string(camera_cmd_pfx + pathStr).c_str());

        // Check and report on image if exists
        namespace fs = std::filesystem;
        fs::path imgPath(pathStr);

        // Populate message stringstream
        msg << "Photo File: " << pathStr << std::endl;

        // Print success/failure for string return
        if (fs::exists(imgPath))
        {
            uintmax_t  numBytes = fs::file_size(imgPath);
            msg << "Successful write of "
                << numBytes << " bytes\n";

            took_photo = true; // No redundant photos
        }
        else
        {
            msg << "Failed to write!\n";
        }
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

std::string PlantWatcher::get_date_timestamp()
{
    namespace bpt = boost::posix_time;
    bpt::ptime timeLocal = bpt::second_clock::local_time();

    return boost::gregorian::to_simple_string(timeLocal.date());
}

bool PlantWatcher::ensure_image_folder()
{
    namespace fs = std::filesystem;
    fs::path dirPath(camera_cmd_dir);
    bool dirExist = true;

    // Attempt to make with std::filesystem
    if (!fs::is_directory(dirPath))
    {
        dirExist = fs::create_directory(dirPath);
    }

    // Fall back on mkdir if that's flaky
    if (!dirExist)
    {
        std::string cmd = "mkdir -p ";
        cmd += camera_cmd_dir;
        std::system(cmd.c_str());

        dirExist = fs::is_directory(dirPath);
    }

    return dirExist;
}

void PlantWatcher::send_plant_data()
{
    CacheIO cacheIo;
    cacheIo.set_values(sensorVals);
    cacheIo.set_statuses(statusVec);
}