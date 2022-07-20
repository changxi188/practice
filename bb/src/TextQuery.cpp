//
// Created by mr on 2020/7/11.
//
#include "TextQuery.h"
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;


TextQuery::TextQuery(int idx, ifstream &ifile) : _idx(idx), _ifile(ifile) {}

string TextQuery::ReadFile(std::vector<std::string> &lines) {
    string temp;
    while(getline(_ifile, temp)){
        lines.push_back(temp);
    }
}

int main(int argc, char** argv){

    ifstream ifile("/home/mr/Downloads/practice/bb/bb.txt");

    vector<string> lines;

    TextQuery readFile(1, ifile);
    readFile.ReadFile(lines);

    for(const auto &line : lines){
        cout << line << endl;
    }

    map<string, size_t > word_count;
    set<string> exclude = {"the", "but", "and"};
    string word;
    while(cin >> word){
        if(exclude.find(word) == exclude.end())
            ++word_count[word];
    }
}