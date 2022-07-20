#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
#include <string>
#include "textquery.h"
#include "queryresult.h"


using namespace std;


void runQueries(ifstream &infile){
	TextQuery tq(infile);
	while(true){

		cout << "enter word to look for, or q to quit : ";

		string s;

		if(!(cin >> s) || s == "q") 
			break;
		print(cout, tq.query(s)) << endl;
	}
}

int main(){
	ifstream file("/home/mr/Downloads/practice/primer/contianer/data/storyDataFile");

	runQueries(file);
	return 0;
}
