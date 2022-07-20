#include "text_query.h"
// #include "query_result.h"

#include <iostream>


using namespace std;


int main(){

	std::ifstream fin("../1.txt");

	if(!fin)
	{
		std::cout << "can't open file " << std::endl;
	}
	std::shared_ptr<TextQuery> tq = std::make_shared<TextQuery>(fin);




	return 0;
}

