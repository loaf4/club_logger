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

};

#endif

