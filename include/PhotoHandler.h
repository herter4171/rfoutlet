//
// Created by Justin Herter on 9/15/19.
//

#ifndef RFOUTLET_PHOTOHANDLER_H
#define RFOUTLET_PHOTOHANDLER_H

#include <string>
#include <stdlib.h>
#include <filesystem>

#include <boost/date_time.hpp>

class PhotoHandler
{

public:

    PhotoHandler()
    {
        took_photo = false;
    }

    std::string update_photo()
    {
        std::stringstream msg; // For return string

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


        return msg.str();
    }

private:

    std::string get_date_timestamp()
    {
        namespace bpt = boost::posix_time;
        bpt::ptime timeLocal = bpt::second_clock::local_time();

        return boost::gregorian::to_simple_string(timeLocal.date());
    }

    bool ensure_image_folder()
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

    bool took_photo; // True after photo taken

    const std::string camera_cmd_pfx = "raspistill -w 1024 -h 768 -o ",
            camera_cmd_dir = "/home/pi/images",
            camera_cmd_ext = ".jpg";
};

#endif //RFOUTLET_PHOTOHANDLER_H
