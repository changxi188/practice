#include <boost/circular_buffer.hpp>
#include <boost/format.hpp>
#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
    }

    boost::circular_buffer<int> cb_i_;
    std::shared_ptr<int>        sp_;
};
int main()
{
    boost::format fmt("left_image_%d");
    for(int i = 0; i < 10; ++i){
        cout << (fmt % i) << endl;
    }

    A a;
    return 0;
}
