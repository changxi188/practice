#include <iostream>
#include <string>
#include <vector>


using namespace std;


class CTempValue{
public:
	int val1_;
	int val2_;

	CTempValue(int val1, int val2);
	CTempValue(const CTempValue& a);
	CTempValue& operator=(const CTempValue& ctempv);

	virtual ~CTempValue();


public:
	
	int sum(CTempValue& b);


};

CTempValue::CTempValue(int val1 = 0, int val2 = 0) : val1_(val1), val2_(val2) {
	cout << "CTempValue::CTempValue(int val1, int val2) start" << endl;
	cout << "val1_ : " << val1_ << endl;
	cout << "val2_ : " << val2_ << endl;
}

CTempValue::CTempValue(const CTempValue & a) : val1_(a.val1_), val2_(a.val2_){
	cout << "CTempValue::CTempValue(const CTempValue &a) start" << endl;	
}

CTempValue& CTempValue::operator=(const CTempValue& ctempv){

	val1_ = ctempv.val1_;
	val2_ = ctempv.val2_;
	cout << "CTempValue& CTempValue::operator(const CTempValue& ctempv) start" << endl;
}

CTempValue::~CTempValue(){
	cout << "CTempValue::~CTempValue() start" << endl;
}

int CTempValue::sum(CTempValue& b){

	int temp = b.val1_ + b.val2_;

	b.val1_ = 10000;
	
	return temp;
}

using namespace std;

int main(){

	/*
	CTempValue tm(10, 20);

	int s = tm.sum(tm);
	cout << s << endl;
	cout << tm.val1_ << endl;
	*/

	/*
	CTempValue tm;
	tm = 100;
	cout << tm.val1_ << endl;
	*/

	CTempValue tm = 1000;

	

	return 0;
}
