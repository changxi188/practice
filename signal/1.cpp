#include <iostream>
#include <unistd.h>

#include <csignal>


using namespace std;


void signalHandler(int signum){

	cout << "signum : " << signum << endl;

	exit(signum);
}

int main(){

	signal(SIGINT, signalHandler);
	while(1){

		cout << "111 << " << endl;
		sleep(1);
	}

	return 0;
}
