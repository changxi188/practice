#include <iostream>
#include <boost/circular_buffer.hpp>


using namespace std;

void TraverseBuffer(const boost::circular_buffer<int> buffer)
{
    std::cout << " ********************************** " << std::endl;
    for (const auto& i : buffer)
    {
        std::cout << i << std::endl;
    }
}

int main()
{

    boost::circular_buffer<int> cb_i(5);

    cb_i.push_back(1);
    cb_i.push_back(2);
    cb_i.push_back(3);
    cb_i.push_back(4);
    cb_i.push_back(5);

    std::cout << " ******************************** " << std::endl;
    std::cout << " buffer begin : " << cb_i.at(0) << std::endl;
    std::cout << " buffer begin : " << &cb_i.at(0) << std::endl;
    std::cout << " buffer begin : " << &*cb_i.begin() << std::endl;
    std::cout << " buffer second : " << cb_i.at(1) << std::endl;
    std::cout << " buffer second : " << &cb_i.at(1) << std::endl;


    cb_i.push_back(6);


    std::cout << "******************************** " << std::endl;
    std::cout << " buffer begin : " << cb_i.at(0) << std::endl;
    std::cout << " buffer begin : " << &cb_i.at(0) << std::endl;
    std::cout << " buffer end : " << *(&cb_i.at(0) - 2) << std::endl;
    std::cout << " buffer end : " << (&cb_i.at(0) - 2) << std::endl;

    return 0;
}
