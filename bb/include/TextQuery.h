//
// Created by mr on 2020/7/11.
//

#ifndef BB_TEXTQUERY_H
#define BB_TEXTQUERY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class TextQuery{
public:

    TextQuery(int idx, std::ifstream &ifile);

    std::string ReadFile(std::vector<std::string> &lines);

private:
    int _idx;
    std::ifstream &_ifile;
};

#endif //BB_TEXTQUERY_H
