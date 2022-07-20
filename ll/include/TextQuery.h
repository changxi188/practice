//
// Created by mr on 2020/7/11.
//

#ifndef LL_TEXTQUERY_H
#define LL_TEXTQUERY_H
#include <map>
#include <set>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "QueryResult.h"

class QueryResult;
class TextQuery{

    using line_no = std::vector<std::string>::size_type ;
    TextQuery(std::ifstream&);
    QueryResult query(const std::string&) const ;

private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string , std::shared_ptr<std::set<line_no>>> wm;
};

#endif //LL_TEXTQUERY_H
