#ifndef TABLE_H
#define TABLE_H

#include "client.h"

enum class TableStatus {Occupied, Free};

class Table {
    Client* _cur_client;
    int _time_cur_sitted;
    int _time_total;
    int _money;
    TableStatus _status;

public:
    Table() : _cur_client{nullptr},
        _time_cur_sitted{0},
        _time_total{0},
        _money{0},
        _status{TableStatus::Free}
    {}
    void client_sitting(Client* client, int time);
    void client_standing(int time, int money_per_hour);
    TableStatus check_status() { return _status; }
};

#endif

