#include "bb.h"


using namespace std;


StrBob::StrBob() : data(make_shared<vector<string>> ()) {}

StrBob::StrBob(initializer_list<std::string> il) : data(make_shared<vector<string>> (il)) {}

void StrBob::check(size_t i, const string &msg) const{
	
	if ( i >= data->size())
		throw out_of_range(msg);
}



string& StrBob::front() const{

	check(0, "front on empty StrBlob");
	return data->front();

}



string& StrBob::back() const{

	check(0, "back on empty StroBob");
	return data->back();

}



void StrBob::pop_back(){
	
	check(0, "pop_back on empty StrBob");
	data->pop_back();

}


