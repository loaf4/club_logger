#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include <unordered_map>
#include <deque>

#include "table.h"
#include "client.h"

class Club {
    std::vector<Table> _tables; // all tables in club
    std::unordered_map<std::string, Client> _clients_in_club; // all clients in club
    std::deque<std::string> _clients_in_queue; // clients in queue in club
    int _time_opened;
    int _time_closed;
    int _tables_total;
    int _tables_free;
    int _money_per_hour;

public:
    Club(int table_count, int time_opened, int time_closed, int money);
    void client_arriving(const std::string& name, const int time);
    void client_sitting(const std::string& name, const int time, const int table_id);
    void client_waiting(const std::string& name);
    void client_leaving(const std::string& name, const int time);
    int get_time_opened() { return _time_opened; }
    int get_time_closed() { return _time_closed; }
    int get_tables_total() { return _tables_total; }
    int get_tables_free() { return _tables_free; }
    // checking client status
    bool is_client_in_queue(const std::string& name) { return _clients_in_club.find(name)->second.check_status() == ClientStatus::WAITING; }
    bool is_client_in_club(const std::string& name) { return _clients_in_club.find(name)->second.check_status() == ClientStatus::ARRIVED; }
    bool is_client_sitting(const std::string& name) { return _clients_in_club.find(name)->second.check_status() == ClientStatus::SITTING; }
    // checking table status
    bool is_table_occupied(int table_id) { return _tables[table_id - 1].check_status() == TableStatus::OCCUPIED; }
    bool is_table_free(int table_id) { return _tables[table_id - 1].check_status() == TableStatus::FREE; }
};

#endif

