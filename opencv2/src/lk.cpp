#include "lk.h"
#include <boost/format.hpp>


bool LK::ImageInit(){

	boost::format fmt("%s/%06d.jpg");

	img1_ = cv::imread((fmt % data_path_ % 0).str());

	img2_ = cv::imread((fmt % data_path_ % 1).str());

	if (img1_.empty() || img2_.empty()){

		std::cout << "please enter write image path" << std::endl;

		return false;
	}

	return true;
}

void LK::DetectCorner(){
	gftt_->detect(img1_, key_points_);

	// through all key_points_
	for (auto kp : key_points_){
		cv::circle(img1_, kp.pt, 2, cv::Scalar(0, 0, 128));
	}

	cv::imshow("GFTT_Points", img1_);
	cv::waitKey(0);

}

