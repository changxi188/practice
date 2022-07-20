#include <iostream>
#include "lk.h"


int main(){

	std::sting data_path("./");

	std::shared_ptr<LK> lk = std::make_shared<LK>(data_path);

	if(!lk->ImageInit()){
		return -1;
	}

	lk->DetectCorner();

	return 0;

}
