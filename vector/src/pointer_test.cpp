#include <iostream>
#include <vector>
#include <memory>
#include <string>




using namespace std;

class A;
class B;


class A{
public:
	A(){}

	vector<std::shared_ptr<B>> sp_b;

private:
	int ai_;	
};

class B{
public:
	B(int bi) : bi_(bi) {}	


	int bi_;


private:

};

int main(){

	auto a = std::make_shared<A>();

	auto b = std::make_shared<B>(1);


	a->sp_b.push_back(b);

	b->bi_ = 0;

	for (auto iter = a->sp_b.begin(); iter != a->sp_b.end(); ++iter){
		cout << (*iter)->bi_ << endl;
	}

	for (size_t i = 0;  i < a->sp_b.size(); ++i){
		cout << a->sp_b[i]->bi_ << std::endl;
	}

	b->bi_ = 1;;

	for (const auto &bb : a->sp_b){
		cout << bb->bi_ << endl;
	}

	cout << a->sp_b[0]->bi_ << std::endl;

	
	return 0;
}
