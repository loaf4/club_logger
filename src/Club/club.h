#ifndef CLUB_H
#define CLUB_H

#include <vector>
#include <queue>

#include "table.h"
#include "client.h"

class Club {
    std::vector<Table> _tables;
    std::queue<Client> _clients;
    int _time_opened;
    int _time_closed;
    int _table_total;
    int _table_free;

public:
    Club(int table_count, int time_opened, int time_closed, int tables) : _tables(table_count),
       _time_opened{time_opened},
       _time_closed{time_closed},
       _table_total{tables},
       _table_free{0}
    {}
    void client_arriving(Client client);
};

#endif

