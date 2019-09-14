#include <iostream>
#include <vector>
#include <memory>

#include "PlantWatcher.h"
#include <boost/thread.hpp>

int main(int argc, char* argv[])
{
    // Execution threads to keep track of
    std::vector<boost::thread> thread_vec;

    // Kill switch
    std::shared_ptr<std::atomic_bool> keep_alive(new std::atomic_bool(true));


    // Add plant watcher to threads
    PlantWatcher pw(true);
    pw.set_keep_alive(keep_alive);
    thread_vec.push_back(boost::thread(pw));

    // Wait for a while
    sleep(60);

    // Send stop signal
    *keep_alive = false;

    // Interrupt and join all threads before termination
    for (auto &curr_thread : thread_vec)
    {
        curr_thread.join();
    }

    return 0;
}
