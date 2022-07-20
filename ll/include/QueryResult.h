//
// Created by mr on 2020/7/11.
//

#ifndef LL_QUERYRESULT_H
#define LL_QUERYRESULT_H
#include <iostream>
#include <memory>
#include <set>
#include <vector>
#include <string>
#include <map>
#include "TextQuery.h"


class QueryResult{

friend std::ostream& print(std::ostream&, const QueryResult&);

using line_no = std::vector<std::string>::size_type;
public:
    QueryResult(std::string s,
                std::shared_ptr<std::set<line_no>> p,
                std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) {};

private:
    static std::string sought;
    std::shared_ptr<std::set<line_no>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};
#endif //LL_QUERYRESULT_H
