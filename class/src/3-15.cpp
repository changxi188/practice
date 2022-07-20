#include <iostream>
#include <vector>
#include <string>



using namespace std;


class A{
public:
	A() {};
	A(int i, int j, int k = 0) {};
};


class B : public A{
public:	
	using A::A;

};


class Grand{	
public:
	Grand(int i) : m_gvalue(i) {
		cout << "Grand::Grand(int i) start" << endl;
	}

	virtual ~Grand(){
		cout << "virtual Grand::~Grand() start" << endl;
	}

private:
	int m_gvalue;

};

class Father1 : public virtual Grand{
public:
	Father1(int i) : Grand(i), m_f1value(i){
		cout << "Father1::Fathre1(int i) start" << endl;
	}

	virtual ~Father1(){
		cout << "virtual Father1::~Father1() start" << endl;
	}

private:
	int m_f1value;

};

class Father3 : public virtual Grand{
public:
	Father3(int i) : Grand(i), m_f3value(i){
		cout << "Father3::Father3(int i) start" << endl;
	}

	virtual ~Father3(){

		cout << "virtual Father3::~Father3() start" << endl;
	}

private:
	int m_f3value;
};

class Father2{
public:
	Father2(int i) : m_f2value(i) {
		cout << "Fathre2::Father2(int i) start" << endl;
	}
	
	virtual ~Father2(){
		cout << "virtual Father2::~Father2() start" << endl;
	}
private:
	int m_f2value;

};

class Children : public Father1, public Father2, public Father3{
public:
	Children(int i, int j, int k) : Father1(i), Father2(j), Father3(k), Grand(k), m_cvalue(k){
		cout << "Children::Children(int i, int j, int k) start" << endl;
	};
	
	virtual ~Children(){
		cout << "virtual Children::~Children() start" << endl;
	}
private:
	int m_cvalue;
};


int main(){
	/*
	B ac(3, 4);
	B ef();
	*/

	Children child1(1, 2, 3);
}
