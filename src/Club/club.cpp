#include <iostream>
#include <algorithm>
#include <fstream>
#include <filesystem>

#include "club.h"

Club::Club(int table_count, const std::string& time_opened, const std::string& time_closed, int money) : _time_opened{time_to_int(time_opened)},
    _time_closed{time_to_int(time_closed)},
    _tables_total{table_count},
    _tables_free{table_count},
    _money_per_hour{money}
{
    for (int i {1}; i <= table_count; ++i) {
        _tables.push_back(Table(i));
    }
}

void Club::client_arriving(const std::string& name, const std::string& time) {
    if (is_client_in_club(name) || !is_in_working_hours(time)) {
        return;
    }
    _clients_in_club.insert(std::make_pair(name, Client(name)));
}

void Club::client_sitting(const std::string& name, const std::string& time, const int table_id) {
    if (!is_client_in_club(name) || is_table_occupied(table_id)) { 
        return;
    }
    if (_clients_in_club.find(name)->second.check_status() == ClientStatus::WAITING) {
        _clients_in_queue.pop_front();
    }
    _tables[table_id - 1].client_sitting(name, time);
    _tables_free--;
    _clients_in_club.find(name)->second.sitting(table_id);
}

void Club::client_waiting(const std::string& name, const std::string& time) {
    if (get_tables_free() > 0) { return; }
    if (get_count_clients_in_queue() > get_tables_total()) {
        client_leaving(name, time);
        return;
    }
    _clients_in_queue.push_back(name);
    _clients_in_club.find(name)->second.waiting();
}

void Club::client_leaving(const std::string& name, const std::string& time) {
    if (!is_client_in_club(name)) {
        return;
    }
    Client cur_client = _clients_in_club.find(name)->second;
    if (cur_client.check_status() == ClientStatus::WAITING) {
        // if client was in queue before leaving
        _clients_in_queue.erase(std::find(_clients_in_queue.begin(), _clients_in_queue.end(), name));
    } else if (cur_client.check_status() == ClientStatus::SITTING) {
        // if client was sitting at the table before leaving
        int table_id = cur_client.get_table_id(); 
        _tables[table_id - 1].client_standing(time, _money_per_hour);
        _tables_free++;

        // next in queue sitting 
        if (get_count_clients_in_queue() > 0 && is_in_working_hours(time)) {
            client_sitting(_clients_in_queue.front(), time, table_id);
        }
    }

    _clients_in_club.erase(name);
}

std::vector<std::string> Club::get_clients_in_club() const { 
    std::vector<std::string> res;
    res.reserve(_clients_in_club.size());
    for (const auto& client : _clients_in_club) { res.push_back(client.first); }
    return res;
}

std::string Club::get_all_tables_info() const {
    std::string res;
    for (const Table& t : _tables) {
        res += t.current_info() + "\n";
    }
    return res;
}
