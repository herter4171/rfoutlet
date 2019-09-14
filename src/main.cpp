#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <boost/thread.hpp>

#include "OutletController.h"
#include "PlantWatcher.h"

using namespace std;
using namespace boost;

int main(int argc, char* argv[])
{
    // Execution threads to keep track of
    std::vector<boost::thread> thread_vec;

    // Add plant watcher to threads
    PlantWatcher pw;
    thread_vec.push_back(boost::thread(pw));

    // Wait for a while
    sleep(60);

    // Interrupt and join all threads before termination
    for (auto &curr_thread : thread_vec)
    {
        curr_thread.interrupt();
        curr_thread.join();
    }

    return 0;
}
