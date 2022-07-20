#include "text_query.h"

TextQuery::TextQuery( std::ifstream& fin) : file_content_(new std::vector<std::string>)
{
	// std::istringstream words;
	std::string words;
	while(std::getline(fin, words))
	{
		file_content_->push_back(words);
		int n = file_content_->size() - 1;
		std::istringstream words_stream(words);
		std::string word;	
		while(words_stream >> word)
		{
			std::shared_ptr<std::set<int>> line_nums = word_lines_[word];	
			if(!line_nums)
				line_nums = std::make_shared<std::set<int>>();
			line_nums->insert(n);
		}
	}
}

QueryResult TextQuery::Query(std::string word)
{
}
