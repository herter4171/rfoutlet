//
// Created by Justin Herter on 8/24/19.
//

#ifndef RFOUTLET_SIMPLESERIAL_H
#define RFOUTLET_SIMPLESERIAL_H

#include <vector>
#include <stdexcept>

#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>


using namespace boost::asio;

class SimpleSerial
{
public:

    // Instantiate with a port.
    SimpleSerial(std::string port)
            : io(), serial(io, port)
    {
        serial.set_option(serial_port_base::baud_rate(baud_rate));
    }

    // Ensures a complete line is returned
    std::vector<int> parseLine();

private:
    // Legacy implementation for reading a single line
    std::string readLine();

    // Needed for serial communication
    boost::asio::io_service io;
    boost::asio::serial_port serial;

    // Need same baud rate as arduino
    const int baud_rate = 9600;

    // Expect three values per line from Arduino
    const int num_vals = 3;
};

#endif //RFOUTLET_SIMPLESERIAL_H
