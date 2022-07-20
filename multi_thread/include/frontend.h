#ifndef __FRONTEND_H__
#define __FRONTEND_H__
#include "common_include.h"
#include "map.h"
#include "viewer.h"

class Frontend{
public:
	typedef std::shared_ptr<Frontend> Ptr;
	Frontend(){};
	void setMap(Map::Ptr map);

	void addInt(const int& i);

	void setViewer(Viewer::Ptr viewer);

private:
	Map::Ptr map_;
	Viewer::Ptr viewer_;
	int i_ = 0;




};

#endif

