#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    int         i;
    char        a[4];
    std::string b;
};

int main()
{
    Student       s2;
    std::cout << "111111 " << std::endl;
    std::ifstream infile("2.bin", ios::in | ios::binary);
    std::cout << "111111 " << std::endl;
    infile.read((char*)&s2, sizeof(Student));
    std::cout << "111111 " << std::endl;
    infile.close();
    std::cout << "s2.a : " << s2.a << std::endl;
    std::cout << "s2.b : " << s2.b << std::endl;

    return 0;
}
