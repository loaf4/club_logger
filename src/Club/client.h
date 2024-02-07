#ifndef CLIENT_H
#define CLIENT_H

#include <string>

enum class ClientStatus {
    ARRIVED = 1,
    SITTING,
    WAITING
};

class Client {
    std::string _name;
    int _table_id;
    ClientStatus _status;

public:
    Client(std::string name);
    void sitting(int table_id) { 
        _status = ClientStatus::SITTING; 
        _table_id = table_id;
    }
    void waiting() { _status = ClientStatus::WAITING; }
    int get_table_id() const { return _table_id; }
    ClientStatus check_status() const { return _status; }
};

#endif

