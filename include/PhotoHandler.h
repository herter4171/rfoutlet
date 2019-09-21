//
// Created by Justin Herter on 9/15/19.
//

#ifndef RFOUTLET_PHOTOHANDLER_H
#define RFOUTLET_PHOTOHANDLER_H

#include <string>
#include <stdlib.h>
#include <filesystem>

#include <boost/date_time.hpp>

#include "ScpSender.h"

class PhotoHandler
{

public:

    PhotoHandler()
    {
        took_photo = false;
    }

    std::string update_photo();

private:
    // Returns e.g. 2019-Sep-21
    std::string get_date_timestamp();

    // Runs "mkdir -p" for image directory
    bool ensure_image_folder();

    bool took_photo; // True after photo taken

    const std::string camera_cmd_pfx = "raspistill -w 1024 -h 768 -o ",
            camera_cmd_dir = "/home/pi/images",
            camera_cmd_ext = ".jpg";
};

#endif //RFOUTLET_PHOTOHANDLER_H
