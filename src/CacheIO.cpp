//
// Created by Justin Herter on 8/25/19.
//

#include <CacheIO.h>

void CacheIO::set_values(std::vector<int> sensorVals)
{
    str_map sensorMap;

    for (int i = 0; i < sensorVals.size(); i++)
    {
        sensorMap[levelKeys[i]] = std::to_string(sensorVals[i]);
    }

    write_map(sensorMap);
}

void CacheIO::set_statuses(std::vector<bool> statusVec)
{
    str_map statusMap;

    for (int i = 0; i < statusVec.size(); i++)
    {
        std::string status = statusGood;
        if (!statusVec[i])
        {
            status = statusError;
        }

        statusMap[statusKeys[i]] = status;
    }

    write_map(statusMap);
}

void CacheIO::update_last_write()
{
    using namespace std::chrono;
    seconds sec_val = duration_cast<seconds>(system_clock::now().time_since_epoch());
    std::string sec_str = std::to_string(sec_val.count());

    write_map({{writeTimeKey, sec_str}});
}

std::string CacheIO::get_status_string(bool status)
{
    return status ? statusGood : statusError;
}

void CacheIO::write_map(str_map outMap)
{
    for (auto &pair : outMap)
    {
        std::string cmd = "SET " + pair.first + " " + pair.second;
        redisCommand(ctx.get(), cmd.c_str());
    }
}