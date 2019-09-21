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

int send_scp(string from_path, string host, string to_path)
{
    // Build SCP command
    vector<string> remote_args = {host, to_path};
    vector<string> scp_args = {"scp", from_path, ba::join(remote_args, ":")};
    string scp_cmd = ba::join(scp_args, " ");

    // Return exit code of command
    return system(scp_cmd.c_str());
}

bool wrapper_test_scp(string from_path)
{
    string host = "mac_mini";
    string to

}


#endif //RFOUTLET_SCPSENDER_H
