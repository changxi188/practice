#include <iostream>
#include <vector>
#include <string>



using namespace std;


class B{
public:
	B() : m_bm(100){
	
		cout << "B::B() start" << endl;
	}
	
	B(const B& b) : m_bm(b.m_bm) {
		cout << "B::B(const B& b) start" << endl;

	}

	virtual ~B(){

		cout << "virtual ~B() start" << endl;
	}


	int m_bm;

}; 

class A{
public:
	A() : p_bm(new B()){
		cout << "A::A() start" << endl;
	}

	A(const A& a) : p_bm(new B(*(a.p_bm))){

		cout << "A::A(const A& a) start" << endl;
	}
	

	A(A &&tmpa) : p_bm(tmpa.p_bm){
		tmpa.p_bm = nullptr;
		cout <<"A::A(A &&tmpa) start" << endl;
	}

	virtual ~A(){
		delete p_bm;

		cout << "virtual ~A() start" << endl;
	}

private:
	B *p_bm;


};

static A getA(){
	A a;
	return a;
}

int main(){


	/*
	B *pb = new B;
	pb->m_bm = 20;

	B *pb2(new B(*pb));
	pb2->m_bm = 10;

	delete pb;
	delete pb2;
	*/

	//getA();
	A a = getA();
	A a1(std::move(a));
	return 0;
}

