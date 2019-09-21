//
// Created by Justin Herter on 9/15/19.
//

#ifndef RFOUTLET_SCPSENDER_H
#define RFOUTLET_SCPSENDER_H

#include <string>
#include <vector>
#include <cstdlib>

#include <boost/algorithm/string/join.hpp>

using namespace std;
namespace ba = boost::algorithm;

namespace scp {

    // Runs "scp from_path host:to_path"
    int send_to_remote(string from_path, string host, string to_path);

    // Convenience wrapper for testing
    bool wrapper_send_to_remote(string from_path);

}

#endif //RFOUTLET_SCPSENDER_H
