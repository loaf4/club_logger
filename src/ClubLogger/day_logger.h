#ifndef DAY_LOGGER_H
#define DAY_LOGGER_H

#include <string>
#include <vector>

#include "club.h"

enum class EventIds {
    ARRIVED = 1,
    SITTING,
    WAITING,
    LEAVING,
    LEAVING_END = 11,
    SITTING_FROM_QUEUE,
    ERROR
};

class DayLogger {
    void handle_input_event(std::ostream& os, const std::vector<std::string>& event_line, Club& club);
    // possible events
    std::string handle_arriving(const std::vector<std::string>& event_line, Club& club);
    std::string handle_sitting(const std::vector<std::string>& event_line, Club& club);
    std::string handle_waiting(const std::vector<std::string>& event_line, Club& club);
    std::string handle_leaving(const std::vector<std::string>& event_line, Club& club);
    std::string handle_error(const std::vector<std::string>& event_line, Club& club);
    std::vector<std::string> split_str(const std::string& str);

public:
    void generate_day_log(const std::string& filename);
};

#endif

