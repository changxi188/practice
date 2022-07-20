#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class Student
{
public:
    int  i;
    char        a[4];
    std::string b;
};

int main()
{
    Student s1;
    s1.i = 1;
    strcpy(s1.a, "aaa");
    s1.b = "bbb";

    std::ofstream outfile("2.bin", ios::out | ios::binary);
    outfile.write((char*)&s1, sizeof(Student));
    outfile.close();

    std::cout << "s1.a : " << s1.a << std::endl;
    std::cout << "s1.b : " << s1.b << std::endl;

    std::cout << "s1.size" << sizeof(s1) << std::endl;
    std::cout << "student size" << sizeof(Student) << std::endl;

    return 0;
}
