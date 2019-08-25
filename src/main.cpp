#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "SimpleSerial.h"
#include "OutletController.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{

    try {

        SimpleSerial serial("/dev/ttyACM0");

        // Cycle outlet on and off
        OutletController oc = OutletController();
        oc.flicker_test(2);

        // Take still image
        std::system("raspistill -w 1024 -h 768 -o /home/pi/image.jpg");

        for(int i = 0; i < 1000; i++)
        {
            for (auto &val : serial.parseLine())
            {
                std::cout << val << " ";
            }

            std::cout << "\n";
        }
    } catch(boost::system::system_error& e)
    {
        cout<<"Error: "<<e.what()<<endl;
        return 1;
    }
}
