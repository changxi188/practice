#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;



int main(int argc, char** argv){
	cv::Mat img1 = cv::imread(argv[1], 1);
	cv::Mat img2 = cv::imread(argv[2], 1);
	if(img1.empty() || img2.empty()){
		cout << "error open image" << endl;
		return -1;
	}

	std::vector<cv::KeyPoint> kps1;

	cv::Ptr<cv::GFTTDetector> gftt = cv::GFTTDetector::create(200, 0.01, 20);

	gftt->detect(img1, kps1);

	std::vector<cv::Point2f> ps1, ps2, ps3;

	for(auto kp : kps1) 
		ps1.push_back(kp.pt);
	std::vector<uchar> status;

	std::vector<float> error;

	cv::calcOpticalFlowPyrLK(img1, img2, ps1, ps2, status, error);

	for(int i = 0; i < ps2.size(); ++i){
		if(status[i]){
			cv::circle(img2, ps2[i], 2, cv::Scalar(0, 250, 0), 2);
			cv::line(img2, ps1[i], ps2[i], cv::Scalar(0, 250, 0));

		}

	}
	cv::imshow("LK", img2);
	cv::waitKey(0);


	return 0;
}
