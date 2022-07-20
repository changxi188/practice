#include "common_include.h"
#include "map.h"
#include "frontend.h"
#include "viewer.h"
#include <chrono>

using namespace std;

int main(){

	Map::Ptr map = std::make_shared<Map>();

	Viewer::Ptr viewer = std::make_shared<Viewer>();
	viewer->setMap(map);

	Frontend::Ptr frontend = std::make_shared<Frontend>();
	frontend->setMap(map);
	frontend->setViewer(viewer);

	for(int i = 0; i < 10000000; ++i){
		frontend->addInt(i);	
		std::cout << "from main thread : " << map->getShared().back() << std::endl;
	}

	viewer->viewerStop();

	return 0;
}

