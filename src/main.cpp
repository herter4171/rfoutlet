#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

#include "SimpleSerial.h"
#include "OutletController.h"
#include "PlantWatcher.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{

    try {

        SimpleSerial serial("/dev/ttyACM0");

        PlantWatcher pw;
        pw.update_sensor_data();
        pw.update_light();
        std::cout << pw.update_photo();

        for(int i = 0; i < 10000; i++)
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
