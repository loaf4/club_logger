#ifndef CLIENT_H
#define CLIENT_H

#include <string>

enum class ClientStatus {Arrived = 1, Sitting, Waiting};

class Client {
    std::string _name;
    int _time_arrived;
    ClientStatus _status;

public:
    Client(std::string name, int time_arrived) : _name{name}, 
        _time_arrived{time_arrived},
        _status{ClientStatus::Arrived} 
    {}
    void change_status(ClientStatus stat) { _status = stat; }
};

#endif

