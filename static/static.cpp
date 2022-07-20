#include <iostream>

using namespace std;


class TestStatic{
public:
    TestStatic(const int& _b): b(_b)
    {      
    }

    static int a;
    int b;

    static TestStatic StaticFunc(){
        std::cout << a << std::endl; 
        // std::cout << b << std::endl;
        return TestStatic(a);
    }


};

int TestStatic::a = 0;

int main(){
    TestStatic s1(1);

    TestStatic test = TestStatic::StaticFunc();

    std::cout << test.a << std::endl;


    return 0;
}
