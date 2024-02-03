#include "table.h"

void Table::client_sitting(Client* client, int time) {
    _cur_client = client;
    _time_cur_sitted = time;
    _status = TableStatus::Occupied;
}

void Table::client_standing(int time, int money_per_hour) {
    _cur_client = nullptr;
    int tmp_time = time - _time_cur_sitted; 
    _time_total += tmp_time; 
    _money += money_per_hour * (tmp_time / 60);
    if (tmp_time % 60) {
        _money += money_per_hour;
    }
    _status = TableStatus::Free;
}

