//
// Created by mr on 2020/7/11.
//

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <string>

using namespace std;

int main(){

    vector<int> ivec;

    for(vector<int>::size_type i = 0; i !=10; ++i){
        ivec.push_back(i);
        ivec.push_back(i);
    }

    set<int> iset(ivec.cbegin(), ivec.cend());
    multiset<int> mset(ivec.cbegin(), ivec.cend());
    unorder_map<int, string> a;
}
