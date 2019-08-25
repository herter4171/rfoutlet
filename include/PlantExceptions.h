//
// Created by Justin Herter on 8/24/19.
//

#ifndef RFOUTLET_PLANTEXCEPTIONS_H
#define RFOUTLET_PLANTEXCEPTIONS_H

#include <exception>

class LowLightException : public std::exception
{
    const char * what() const throw ()
    {
        return "Plant light too low.  Is the light on?";
    }
};

class LowMoistureException : public std::exception
{
    const char * what() const throw()
    {
        return "Moisture too low.  Is the pump working?";
    }
};

class LowReserveException : public std::exception
{
    const char * what() const throw()
    {
        return "Water reserve is low.  Refill ASAP.";
    }
};

#endif //RFOUTLET_PLANTEXCEPTIONS_H
