//
// Created by Justin Herter on 9/21/19.
//

#include "ScpSender.h"

int scp::send_to_remote(string from_path, string host, string to_path)
{
    // Build SCP command
    vector<string> remote_args = {host, to_path};
    vector<string> scp_args = {"scp", from_path, ba::join(remote_args, ":")};
    string scp_cmd = ba::join(scp_args, " ");

    // Return exit code of command
    return system(scp_cmd.c_str());
}

bool scp::wrapper_send_to_remote(string from_path) {
    string host = "mac_mini";
    string to_path = "~/images";

    return send_to_remote(from_path, host, to_path) == 0;
}