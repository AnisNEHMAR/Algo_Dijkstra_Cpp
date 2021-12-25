#include<iostream>
#include<fstream>
#include"Parser.h"


#define INF 50000

using namespace std;
using namespace travel;

void Parser::read_stations(const std::string& _filename)  {
	ifstream monFlux(_filename);

	if (monFlux)
	{
		string ligne;
		string info[5];
		string id;
		int i = 0;
		getline(monFlux, ligne);
		while (getline(monFlux, ligne, ',')) {

			info[i] = ligne;
			i++;
			if (i == 4) {  //pour le dernier element de la ligne
				getline(monFlux, ligne, '\n');
				i++;
			}
			if (i == 5) {
				Station s;
				id = info[1];
				s.name = info[0];
				s.line_id = info[2];
				s.address = info[3];
				s.line_name = info[4];
				stations_hashmap[stoi(id)] = s;
				i = 0;
				
			}
		}		
	}
	else{
		cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}

};


void Parser::read_connections(const std::string& _filename) {
	ifstream monFlux(_filename);

	if (monFlux)
	{
		string ligne;
		string info[3];
		
		int i = 0;
		getline(monFlux, ligne);
		while (getline(monFlux, ligne, ',')) {
			info[i] = ligne;
			i++;
			if (i == 2) {
				getline(monFlux, ligne, '\n');
				info[i] = ligne;
				connections_hashmap[stoi(info[0])][stoi(info[1])] = stoi(info[2]);
				i = 0;
			}
			
		}
	}
}

vector<pair<uint64_t, uint64_t> > Parser::compute_travel(uint64_t _start, uint64_t _end) {

	unordered_map<uint64_t, Station>graph(stations_hashmap);// (node_id,distance)
	unordered_map<uint64_t, uint64_t>pred;
	unordered_map<uint64_t, uint64_t>distance;
	uint64_t id_node_min_distance = _start;
	uint64_t distance_min;

	////
	// initialisation de graph (node_id, node_distance)
	for (auto station_iterator = stations_hashmap.begin(); station_iterator != stations_hashmap.end(); station_iterator++) {
		distance[station_iterator->first] = INF;
	}
	distance[id_node_min_distance] = 0;
	////
	

	while (!graph.empty() && id_node_min_distance != _end) {
		///// 
		// recherche du noeud avec distance minimal
		distance_min = INF;
		for (auto iterator = graph.begin(); iterator != graph.end(); iterator++) {
			
			if (distance[iterator->first] < distance_min) {
				distance_min = distance[iterator->first];
				id_node_min_distance = iterator->first;
			}
		} 
		
		graph.erase(id_node_min_distance);
		////
		
		////
		// Mise a jour des distances de voisins
		for (auto iterator = connections_hashmap[id_node_min_distance].begin(); iterator != connections_hashmap[id_node_min_distance].end(); iterator++) {
			
			if (distance_min + iterator->second < distance[iterator->first]) {
				
				distance[iterator->first] = distance_min + iterator->second;
				pred[iterator->first] = id_node_min_distance;
			}
		}
		////
	}
	

	////
	// engregistrement du meilleur chemin dans un vecteur
	uint64_t node = _end;
	vector<std::pair<uint64_t, uint64_t>> path;
	while (node != _start) {
		
		path.push_back(make_pair(node,connections_hashmap[pred[node]][node] ));
		node = pred[node];
	}	
	//
	return path;
}

vector<std::pair<uint64_t, uint64_t>> Parser::compute_and_display_travel(uint64_t _start, uint64_t _end) {
	vector<std::pair<uint64_t, uint64_t>> path = compute_travel(_start, _end);
	cout << "\n From:  "<< stations_hashmap[_start].name << ", to: " << stations_hashmap[_end].name << endl;
	uint64_t time = 0;
	// parcours inverse 
	for (auto it = path.rbegin(); it != path.rend(); ++it)
	{	
		
		time += it->second;
		cout << stations_hashmap[it->first] << "  ---" << time/60 << " minutes and "<< time - uint64_t(time / 60) * 60 <<" secs --- "<< endl;
		
	}
	
	cout << "\nTemps total : " << time/60 << " minutes et " << time - uint64_t(time/60)*60 << " seconds." << std::endl;

	return path;
}



