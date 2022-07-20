#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;


int main(){

	cv::Mat img1 = cv::imread("../000001.png");
	cv::Mat img2 = cv::imread("../000005.png");

	cv::Mat vc_result;
	cv::vconcat(img1, img2, vc_result);
	cv::imshow("vc", vc_result);
	cv::waitKey(0);

	return 0;
}
