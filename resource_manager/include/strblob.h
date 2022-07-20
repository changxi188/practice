#ifndef __STRBLOB_H__
#define __STRBLOB_H__

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <thread>
#include "strblobptr.h"

using namespace std;



class Test{
public:
	Test(){
		cout << "Test() start " << endl;
	}

	~Test(){
		cout << "~Test() start" << endl;
	}
private:

	int a = 0;
};

// class StrBlobPtr;

class StrBlob{
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const {return data->size();}
	bool empty() const {return data->empty();}
	void push_back(const std::string& t) {data->push_back(t);}
	void pop_back();

	std::string& front();
	std::string& back();

	/*
	StrBlobPtr begin() {return StrBlobPtr(*this);}
	StrBlobPtr end(){
		auto ret = StrBlobPtr(*this, data->size());
		return ret;
	}
	*/

	friend class StrBlobPtr;

private:
	std::shared_ptr<std::vector<std::string>> data;
	std::shared_ptr<Test> test_data;
	void check(size_type i, const std::string &msg) const;
};

#endif

