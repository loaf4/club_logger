#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

#include "day_logger.h"
#include "club.h"
#include "club_util.h"

namespace fs = std::filesystem;

void DayLogger::generate_day_log(const std::string& filename) {
    std::string buffer;
    fs::path path_to_tmp {fs::current_path().parent_path().parent_path() / "tmp"};

    std::ifstream fin(path_to_tmp / filename);
    if (!fin) { 
        std::cerr << "error: input file can't be opened";
    }

    std::ofstream fout(path_to_tmp / ("log_" + filename));
    if (!fout) { 
        std::cerr << "error: output file can't be opened";
    }

    std::vector<std::string> club_init_params;
    for (int i {0}; i < 3; ++i) {
        if (!fin.good()) {
            std::cerr << "error: can't read input file anymore";
            return;
        }

        std::getline(fin, buffer);
        club_init_params.push_back(buffer);
    }

    std::vector<std::string> working_hours {split_str(club_init_params[1])};
    Club club(std::stoi(club_init_params[0]),
            time_to_int(working_hours[0]),
            time_to_int(working_hours[1]),
            std::stoi(club_init_params[2]));

    if (!fout.good()) {
        std::cerr << "error: can't write output file anymore";
        return;
    }
    fout << working_hours[0] << std::endl;
    
    std::vector<std::string> split_buffer;
    while (!fin.eof() && !fin.good() && !fout.good()) {
        std::getline(fin, buffer);
        split_buffer = split_str(buffer);

        handle_input_event(fout, split_buffer, club);
    }

    if (!fout.good()) {
        std::cerr << "error: can't write output file anymore";
        return;
    }
    fout << working_hours[1] << std::endl;

    fin.close();
    fout.close();
}

void DayLogger::handle_input_event(std::ostream& os, const std::vector<std::string>& event_line, Club& club) {

}

std::string DayLogger::handle_arriving(const std::vector<std::string>& event_line, Club& club) {
    std::string response;

}

std::string DayLogger::handle_sitting(const std::vector<std::string>& event_line, Club& club) {}

std::string DayLogger::handle_waiting(const std::vector<std::string>& event_line, Club& club) {}

std::string DayLogger::handle_leaving(const std::vector<std::string>& event_line, Club& club) {}

std::string DayLogger::handle_error(const std::vector<std::string>& event_line, Club& club) {}

std::vector<std::string> DayLogger::split_str(const std::string& str) {
    std::vector<std::string> res;

    std::stringstream ss(str);
    std::string part;
    while (ss >> part) {
        res.push_back(part);
    }

    return res;
}
