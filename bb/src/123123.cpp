#include <iostream>
#include <string>
#include <vector>
#include <sstream>

struct PersonInfo{

	std::string name;
	std::vector<std::string> phones;

};


void ReadLine(std::vector<PersonInfo> &people){

	std::string line, word;
	int n = 0;
	std::cout << "enter name and phone numbers" << std::endl;
	while(n++ < 3){
		getline(std::cin, line);
		PersonInfo info;
		std::istringstream record(line);
		record >> info.name;
		while(record >> word){
			info.phones.push_back(word);
		}
		people.push_back(info);
	}

}

void print(std::vector<PersonInfo> &people){

	for(const auto &person : people){
		
		std::cout << "Name : " <<person.name << std::endl;
		std::cout << "phone number :";
		for (const auto &phone : person.phones)
			std::cout << phone << "\t";
		std::cout << std::endl;
	}

}

int main(){

	std::string line, word;
	std::vector<PersonInfo> people;

	// 读取信息
	ReadLine(people);

	// 输出信息
	print(people);


}
