#include <iostream>
#include <memory>


using namespace std;
class singleTon{
public:
	static std::shared_ptr<singleTon> setSingleTon(){
		if (singleTon_ == nullptr)	
			singleTon_ = shared_ptr<singleTon>(new singleTon);
		return singleTon_;
	}


	~singleTon(){
		cout << "~singleTon() start" << endl;
	}

private:
	singleTon(){
		cout << "singleTon() start" << endl;
	};

	static std::shared_ptr<singleTon> singleTon_;

};

std::shared_ptr<singleTon> singleTon::singleTon_ = nullptr;

int main(){
	cout << 1 << endl;
	auto s1 = singleTon::setSingleTon();
	cout << 2 << endl;
	auto s2 = s1;
	auto s3 = singleTon::setSingleTon();


	cout << 3 << endl;
	return 0;
}
