#include <iostream>
#include <opencv2/opencv.hpp>


using namespace std;

using namespace cv;

int main(int argc, char** argv){

	cv::Mat img1 = cv::imread(argv[1], 1);

	cv::Ptr<cv::GFTTDetector> gftt = cv::GFTTDetector::create(200, 0.01, 20);

	std::vector<cv::KeyPoint> keypoints;

	gftt->detect(img1, keypoints);
	
	for (const auto &kp : keypoints){
		cv::rectangle(img1, kp.pt - cv::Point2f(10, 10), kp.pt + cv::Point2f(10, 10), 128, 2);	
	}

	cv::imshow("aaa", img1);

	cv::waitKey(0);

	return 0;
}
