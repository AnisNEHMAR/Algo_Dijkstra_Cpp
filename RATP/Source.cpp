#include <iostream>
#include "Parser.h"
#include <string>
//#include "Grade.hpp"
using namespace std;
using namespace travel;

int main() {
	string file_stations = "data/s.csv";
	string file_connections = "data/c.csv";

	//string file_stations = "data/stations.csv";
	//string file_connections = "data/connections.csv";
	Parser R;
	
	R.read_stations(file_stations);
	R.read_connections(file_connections);
	unordered_map<uint64_t, Station> stations_umap = R.get_stations_hashmap();
	
	unordered_map<uint64_t, unordered_map<uint64_t, uint64_t>> connections_umap = R.get_connections_hashmap();
	
	//vector<pair<uint64_t, uint64_t> > best_path = R.compute_and_display_travel(1166832, 1166840);
	vector<pair<uint64_t, uint64_t> > best_path = R.compute_and_display_travel(1722, 2062);
	vector < pair<uint64_t, uint64_t>>::iterator p;
	cout << "done" << endl;
}