#ifndef TEXT_QUERY_H_
#define TEXT_QUERY_H_
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>
// #include "query_result.h"
class QueryResult;
class TextQuery
{
public:
	TextQuery(std::ifstream& fin);

	QueryResult Query(std::string word);


private:
	// std::ifstream file_;
	std::shared_ptr<std::vector<std::string>> file_content_;
	std::map<std::string, std::shared_ptr<std::set<int>>> word_lines_;
};

#endif
