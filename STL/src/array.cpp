#include <iostream>
#include <array>
#include <string>

int main(){

	std::array<std::string, 5> mystring{"i", "love", "china"};
	mystring[0] = "fas;lflja;slfj;asfdj;lalsfj";
	mystring[4] = "falsfjalsfjlasdjafj;alfaslfjasl";

	std::cout << "sizeof(string)" <<  sizeof(std::string) << std::endl;

	for (size_t i = 0; i < mystring.size(); ++i){
		const char *p = mystring[i].c_str();

		std::cout << p << std::endl;
		std::cout << "对象地址" << &mystring[i] << std::endl;
		printf("所指字符串地址 : %p\n", p);
	}

	const char *p1 = "iloveaaa";
	const char *p2 = "iloveaaa";
	printf("所指字符串地址 : %p1\n", p1);
	printf("所指字符串地址 : %p2\n", p2);

}
