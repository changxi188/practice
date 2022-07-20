#include <iostream>
#include <opencv2/opencv.hpp>


using namespace cv;
using namespace std;
int main(int argc, char** argv){

	Mat img = imread(argv[1], 1);
	if (img.empty()){
		cout << "cannont open image" << endl;
		return -1;
	}
	imshow("aa", img);
	waitKey(0);
	
	return 0;
}
