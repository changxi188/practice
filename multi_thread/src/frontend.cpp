#include "frontend.h"
#include <chrono>

void Frontend::setMap(Map::Ptr map){
	map_ = map;
}

void Frontend::setViewer(Viewer::Ptr viewer){
	viewer_ = viewer;
}

void Frontend::addInt(const int& i){
	i_ = i;
	//std::this_thread::sleep_for(std::chrono::seconds(1));
	map_->insertInt(i_);
	viewer_->updateMap();
}


