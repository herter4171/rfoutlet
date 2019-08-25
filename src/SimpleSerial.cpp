//
// Created by Justin Herter on 8/24/19.
//

#include "SimpleSerial.h"

std::vector<int> SimpleSerial::parseLine()
{
    using namespace boost::algorithm;

    // Read past partial line, and store full line
    readLine();
    std::string line = readLine();

    std::vector<std::string> valStrings;
    split(valStrings, line, is_any_of(","));

    std::vector<int> parsedVals;
    for (auto & valStr : valStrings)
    {
        int val = std::stoi(valStr);
        parsedVals.push_back(val);
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