#pragma once
#ifndef __LK_H__
#define __LK_H__
#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;


class LK{

public:

	LK(string data_path) : data_path_(data_path) {
		gftt_ = cv::GFTTDetector::create();
	};
	
	// init img1_ and img2_
	bool ImageInit();

	// detect corner in img1_
	void DetectCorner();




private:
	// use for gftt detect
	cv::Ptr<cv::GFTTDetector> gftt_;
	
	// two image will be used for LK track;
	cv::Mat img1_, img2_;

	// dataset path
	string data_path_;

	// keypoints detectd by GFTT
	std::vector<cv::KeyPoint> key_points_;

};

#endif
