#include "map.h"

void Map::insertInt(const int& i){
	shared_vector_.push_back(i);
}


std::vector<int> Map::getShared(){
	return shared_vector_;
}

