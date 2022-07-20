#include <iostream>
#include <vector>

using namespace std;

int main(){
    // cout << 101 % 2 << endl;
    std::vector<int> a;
    a.push_back(0);
    a.push_back(1);
    a.push_back(2);
    std::cout << "a: " << a.at(0) << std::endl;
    return 0;
}
