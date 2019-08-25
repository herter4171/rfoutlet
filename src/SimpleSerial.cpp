//
// Created by Justin Herter on 8/24/19.
//

#include "SimpleSerial.h"

std::vector<int> SimpleSerial::parseLine()
{
    using namespace boost::algorithm;

    // Read past partial line, and store full line
    readLine();
    bool goodRead = false;
    int tries = 0, maxTries = 3;

    std::vector<int> parsedVals;

    while (!goodRead)
    {
        tries++;

        try
        {
            // Read line and split by commas
            std::string line = readLine();
            std::vector<std::string> valStrings;
            split(valStrings, line, is_any_of(","));

            // Length error if three strings not present
            if (valStrings.size() != num_vals)
            {
                std::string msg = "Expect ";
                msg += std::to_string(num_vals) + " values.";
                throw std::length_error(msg);
            }

            // Fill int vector from strings
            for (auto & valStr : valStrings)
            {
                int val = std::stoi(valStr);
                parsedVals.push_back(val);
            }

            goodRead = true; // Valid int vec established
        }
        catch(std::exception& ex)
        {
            if (tries >= maxTries) // Can't get good read
            {
                throw; // Handle elsewhere
            }
        }
    }

    return parsedVals;
}

// Retained from legacy implementation
std::string SimpleSerial::readLine()
{
    //Reading data char by char, code is optimized for simplicity, not speed
    using namespace boost;
    char c;
    std::string result;

    for(;;)
    {
        asio::read(serial,asio::buffer(&c,1));
        switch(c)
        {
            case '\r':
                break;
            case '\n':
                return result;
            default:
                result+=c;
        }
    }
}