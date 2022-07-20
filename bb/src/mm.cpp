#include "bb.cpp"

using namespace std;

int main(){
	initializer_list<string> ils;
	StrBob bob1;
    {
        StrBob bob2{"a", "an", "the"};
        bob1 = bob2;
        bob2.push_back("about");

    }

    cout << bob1.front() << endl;

}
