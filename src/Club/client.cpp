#include "client.h"

Client::Client(std::string name) : _name{name}, 
    _table_id{0},
    _status{ClientStatus::ARRIVED} 
{}
