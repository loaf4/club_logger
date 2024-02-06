#include "club_util.h"

// time_to_int and time_to_str expects and represents the time in the format "hh:mm"
int time_to_int(const std::string& time) {
    return std::stoi(time.substr(0, 2)) * 60 + std::stoi(time.substr(3, 2));
}

std::string time_to_str(const int time) {
    std::string res;
    if (time / 60 < 10) {
        res += "0" + std::to_string(time / 60);
    } else {
        res += std::to_string(time / 60);
    }
    res += ":";
    if (time % 60 < 10) {
        res += "0" + std::to_string(time % 60);
    } else {
        res += std::to_string(time % 60);
    }
    return res;
}
