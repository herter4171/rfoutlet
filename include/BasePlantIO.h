//
// Created by Justin Herter on 8/25/19.
//

#ifndef RFOUTLET_BASEPLANTIO_H
#define RFOUTLET_BASEPLANTIO_H

#include <string>
#include <vector>

class BasePlantIO
{
public:
    typedef std::vector<std::string> str_vec;
    typedef std::map<std::string, std::string> str_map;

protected:
    // Indices for mapping Arduino feed
    enum SENSOR_INDS{LIGHT, MOISTURE, RESERVE};

    // Used for get/set sensor values
    const str_vec levelKeys = {"Light_Level",
                               "Moist_Level",
                               "Resrv_Level"};

    // Used for get/set monitoring statuses
    const str_vec statusKeys = {"Light_Status",
                                "Moist_Status",
                                "Resrv_Status"};

    // For latest write timestamp
    const std::string writeTimeKey = "Last_Write";

    // Want human readable statuses
    const std::string statusGood = "Good",
                      statusError = "ERROR";
};

#endif //RFOUTLET_BASEPLANTIO_H
