//
// Created by Justin Herter on 8/25/19.
//

#ifndef RFOUTLET_CACHEIO_H
#define RFOUTLET_CACHEIO_H

#include <memory>
#include <map>
#include <vector>
#include <string>

#include "hiredis.h"
#include "BasePlantIO.h"

class CacheIO : public BasePlantIO
{

public:
    CacheIO()
    {
        redisContext *rdsCtx = redisConnect(ip.c_str(), port);
        ctx = std::make_unique<redisContext>(*rdsCtx);
    }

    void set_values(std::vector<int> sensorVals);

    void set_statuses(std::vector<bool> statusVec);


private:

    void write_map(str_map outMap);

    std::string get_status_string(bool status);

    const std::string ip = "192.168.1.118";//"54.176.149.126";
    const int port = 6379;

    std::unique_ptr<redisContext> ctx;


};

#endif //RFOUTLET_CACHEIO_H
