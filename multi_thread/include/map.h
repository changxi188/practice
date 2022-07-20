#ifndef __MAP_H__
#define __MAP_H__
#include "common_include.h"
class Map{
public:
	typedef std::shared_ptr<Map> Ptr;
	Map(){};

	void insertInt(const int& i);

	std::vector<int> getShared();

	void removeInt();


private:
	std::mutex map_mutex_; 
	std::vector<int> shared_vector_;

};

#endif
