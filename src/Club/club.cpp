#include <algorithm>
#include <fstream>
#include <filesystem>

#include "club.h"

Club::Club(int table_count, int time_opened, int time_closed, int money) : _time_opened{time_opened},
    _time_closed{time_closed},
    _tables_total{table_count},
    _tables_free{0},
    _money_per_hour{money}
{
    for (int i {1}; i <= table_count; ++i) {
        _tables.push_back(Table(i));
    }
}

void Club::client_arriving(const std::string& name, const int time) {
    _clients_in_club.insert(std::make_pair(name, Client(name)));
}

void Club::client_sitting(const std::string& name, const int time, const int table_id) {
    _tables[table_id - 1].client_sitting(name, time);
    _tables_free--;
    _clients_in_club.find(name)->second.sitting(table_id);
}

void Club::client_waiting(const std::string& name) {
    _clients_in_queue.push_back(name);
    _clients_in_club.find(name)->second.waiting();
}

void Club::client_leaving(const std::string& name, const int time) {
    Client cur_client = _clients_in_club.find(name)->second;
    if (cur_client.check_status() == ClientStatus::WAITING) {
        // if client was in queue before leaving
        _clients_in_queue.erase(std::find(_clients_in_queue.begin(), _clients_in_queue.end(), name));
    } else if (cur_client.check_status() == ClientStatus::SITTING) {
        // if client was sitting at the table before leaving
        _tables[cur_client.get_table_id() - 1].client_standing(time, _money_per_hour);
    }

    _clients_in_club.erase(name);
}
