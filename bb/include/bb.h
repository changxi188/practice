#include <iostream>
#include <initializer_list>
#include <memory>
#include <string>
#include <vector>


class StrBob{
 
public:
	StrBob();
	StrBob(std::initializer_list<std::string> il);
	size_t size() const { return data->size();}
	bool empty() const { return data->empty();}


	// element access
	std::string& front() const;
	std::string& back() const;
	void pop_back();


	// add and remove elements
	void push_back(const std::string &t){data->push_back(t);};


private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_t i, const std::string &msg) const;

};
