//
// Created by Justin Herter on 9/21/19.
//

#include "PhotoHandler.h"

std::string PhotoHandler::update_photo()
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

        // Want to try again if photo fails to upload
        took_photo = scp::wrapper_send_to_remote(imgPath);
    }
    else
    {
        msg << "Failed to write!\n";
    }


    return msg.str();
}

std::string PhotoHandler::get_date_timestamp()
{
    namespace bpt = boost::posix_time;
    bpt::ptime timeLocal = bpt::second_clock::local_time();

    return boost::gregorian::to_simple_string(timeLocal.date());
}

bool PhotoHandler::ensure_image_folder()
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