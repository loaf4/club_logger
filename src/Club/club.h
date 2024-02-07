#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include <unordered_map>
#include <deque>
#include <cstdint>

#include "table.h"
#include "client.h"

class Club {
    std::vector<Table> _tables; // all tables in club
    std::unordered_map<std::string, Client> _clients_in_club; // all clients in club
    std::deque<std::string> _clients_in_queue; // clients in queue in club
    uint32_t _time_opened;
    uint32_t _time_closed;
    int _tables_total;
    int _tables_free;
    int _money_per_hour;

public:
    Club(int table_count, uint32_t time_opened, uint32_t time_closed, int money);
    void client_arriving(const std::string& name, const uint32_t time);
    void client_sitting(const std::string& name, const uint32_t time, const int table_id);
    void client_waiting(const std::string& name);
    void client_leaving(const std::string& name, const uint32_t time);

    std::vector<std::string> get_clients_in_club() const;
    int get_count_clients_in_queue() const { return _clients_in_queue.size(); }
    std::string get_first_client_in_queue() const { return _clients_in_queue.front(); }
    int get_table_id_by_client(std::string name) const { return _clients_in_club.find(name)->second.get_table_id(); } 
    std::string get_client_by_table_id(int table_id) const { return _tables[table_id - 1].get_cur_client(); }
    uint32_t get_time_opened() const { return _time_opened; }
    uint32_t get_time_closed() const { return _time_closed; }
    int get_tables_total() const { return _tables_total; }
    int get_tables_free() const { return _tables_free; }
    std::string get_all_tables_info() const;

    // checking client status
    bool is_client_in_queue(const std::string& name) const { return _clients_in_club.find(name)->second.check_status() == ClientStatus::WAITING; }
    bool is_client_arrived(const std::string& name) const { return _clients_in_club.find(name)->second.check_status() == ClientStatus::ARRIVED; }
    bool is_client_sitting(const std::string& name) const { return _clients_in_club.find(name)->second.check_status() == ClientStatus::SITTING; }
    bool is_client_in_club(const std::string& name) const { return _clients_in_club.contains(name); }

    // checking table status
    bool is_table_occupied(int table_id) const { return _tables[table_id - 1].check_status() == TableStatus::OCCUPIED; }
    bool is_table_free(int table_id) const { return _tables[table_id - 1].check_status() == TableStatus::FREE; }
};

#endif

