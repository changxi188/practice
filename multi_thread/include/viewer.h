#ifndef __VIEWER_H__
#define __VIEWER_H__
#include <chrono>
#include "common_include.h"
#include "map.h"

class Viewer{
public:
	typedef std::shared_ptr<Viewer> Ptr;
	Viewer();

	void setMap(Map::Ptr map);

	void viewerStop();

	void updateMap();
	

private:
	void viewerLoop();

private:
	std::thread viewer_thread_;
	std::mutex viewer_mutex_;
	std::mutex viewer_mutex2_;
	Map::Ptr map_;
	bool viewer_running_;
	std::vector<int> shared_vector_;


};

#endif
