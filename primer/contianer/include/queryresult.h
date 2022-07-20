#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include "common_include.h"


class QueryResult{
friend std::ostream& print(std::ostream&, const QueryResult);
public:
	using line_no = std::vector<std::string>::size_type; 
	QueryResult(std::string s,
			std::shared_ptr<std::set<line_no>> p,
			std::shared_ptr<std::vector<std::string>> f)
		:sought(s), lines(p), file(f);


private:

	std::string sought;
	// 出现的行号
	std::shared_ptr<std::set<line_no>> lines;
	// 输入文件
	std::shared_ptr<std::vector<std::string>> file;

};



#endif
