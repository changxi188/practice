#include <fstream>
#include <iostream>


using namespace std;

int main(){

	ofstream fout("lambda.dat", ios::binary);

	fout << 1 << "\n";
	fout << 2 << "\n";

	fout.close();



	return 0;
}
