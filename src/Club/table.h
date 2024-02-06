#ifndef TABLE_H
#define TABLE_H

#include "client.h"

enum class TableStatus {
    OCCUPIED,
    FREE
};

class Table {
    int _id;
    std::string _cur_client;
    int _time_cur_sitted;
    int _time_total;
    int _money;
    TableStatus _status;

public:
    Table(int id);
    void client_sitting(std::string client, int time);
    void client_standing(int time, int money_per_hour);
    std::string current_info();
    TableStatus check_status() { return _status; }
};

#endif

