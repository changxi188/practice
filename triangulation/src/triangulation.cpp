#include "triangulation.h"


void Triangulation::init(const cv::Mat& R, const cv::Mat& t, 
						 const std::vector<cv::Point2f>& pts_2d_1, const std::vector<cv::Point2f>& pts_2d_2){
	
	T1_ = (cv::Mat_<float> (3, 4) << 
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0);

	T2_ = (cv::Mat_<float> (3, 4) <<
			R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2), t.at<double>(0, 0),
			R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2), t.at<double>(1, 0),
			R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2), t.at<double>(2, 0));
	
	pts_2d_1_ = pts_2d_1;

	pts_2d_2_ = pts_2d_2;
	
}

cv::Point2f Triangulation::pixel2cam(const cv::Point2f& p){	
	return cv::Point2f(
					  (p.x - K_.at<double>(0, 2)) / K_.at<double>(0, 0), 
					  (p.y - K_.at<double>(1, 2)) / K_.at<double>(1, 1)
					  );
}

void Triangulation::triang(){

	// 将像素坐标转换道相机坐标
	for (size_t i = 0; i < pts_2d_1_.size(); ++i){
		pts_c_1_.push_back(pixel2cam(pts_2d_1_[i]));
		pts_c_2_.push_back(pixel2cam(pts_2d_2_[i]));
	}

	// 三角化
	cv::Mat pts_4d;
	cv::triangulatePoints(T1_, T2_, pts_c_1_, pts_c_2_, pts_4d);

	for (int i = 0; i < pts_4d.cols; i++){
		cv::Mat x = pts_4d.col(i);
		//std::cout << x << std::endl;
		x /= x.at<float>(3, 0);	// 归一化
		std::cout << x << std::endl;
		cv::Point3d p(
			x.at<float>(0, 0),
			x.at<float>(1, 0),
			x.at<float>(2, 0));

		pts_3d_.push_back(p);
	}
}
