#pragma once
#include <iostream>
//#include "Generic_connection_parser.hpp"
#include "Generic_mapper.hpp"
using namespace std;
using namespace travel;

//lire les stations + les connections
class Parser : public Generic_mapper {

public:
    void read_stations(const std::string& _filename) override;
    void read_connections(const std::string& _filename) override;
    vector<std::pair<uint64_t, uint64_t> > compute_travel(uint64_t _start, uint64_t _end);
    vector<std::pair<uint64_t, uint64_t> > compute_and_display_travel(uint64_t _start, uint64_t _end);

};

