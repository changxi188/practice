#include "viewer.h"
Viewer::Viewer(){
	viewer_running_ = true;
	viewer_thread_ = std::thread(std::bind(&Viewer::viewerLoop, this));	
}



void Viewer::setMap(Map::Ptr map){
	map_ = map;
}


void Viewer::viewerLoop(){
	while(viewer_running_){
		std::unique_lock<std::mutex> lck(viewer_mutex_);
		std::unique_lock<std::mutex> lck2(viewer_mutex2_);
		std::cout << "from viewer thread : " <<  shared_vector_.size() << std::endl;
		if(!shared_vector_.empty()){
			std::cout << "shared_vector_.back() : " <<  shared_vector_.back() << std::endl;
		}
		//lck.unlock();
		//std::this_thread::sleep_for(std::chrono::milliseconds(70));

	}
}


void Viewer::updateMap(){
	std::unique_lock<std::mutex> lck(viewer_mutex_);
	std::unique_lock<std::mutex> lck2(viewer_mutex2_);
	shared_vector_ = map_->getShared();
}

void Viewer::viewerStop(){
	viewer_running_ = false;
	viewer_thread_.join();
}

