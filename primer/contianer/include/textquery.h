#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__

#include <sstream>
#include "common_include.h"

class QueryResult;
class TextQuery{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream &infile) : file(new std::vector<std::string>){
		std::string text;
		while(std::getline(infile, text)){
			file->push_back(text);
			int n = file->size() - 1;

			// 将行文本分解为单词
			std::istringstream line(text);
			std::string word;
			while(line >> word){
				auto &lines = wm[word];
				// 第一次遇到这个单词,此指针为空
				if(!lines){
					lines.reset(new std::set<line_no>);
				}
				lines->insert(n);
			}
		}

	}
	QueryResult query(const std::string &sought) const;

private:

	// 把文件分成一行一行的放在vector中
	std::shared_ptr<std::vector<std::string>> file;
	// 每个单词到对应所有行号的集合的映射
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;

};

#endif
