#include "pose_estimation_2d_2d.h"



void PoseEstimation2d2d::findEssentialMatrix(const std::vector<cv::DMatch>& matches,
											 const std::vector<cv::KeyPoint>& kps1,
											 const std::vector<cv::KeyPoint>& kps2){
	
	for (size_t i = 0; i < matches.size(); ++i){

		pts_2d_1_.push_back(kps1[matches[i].queryIdx].pt);
		pts_2d_2_.push_back(kps2[matches[i].trainIdx].pt);
	}
	
	// 计算本质矩阵
	essential_matrix_ = cv::findEssentialMat(pts_2d_1_, pts_2d_2_, focal_length_, principal_point_);
	//std::cout << focal_length_ << std::endl;

	// 从本质矩阵恢复R, t
	recoverPose(essential_matrix_, pts_2d_1_, pts_2d_2_, R_, t_, focal_length_, principal_point_);

}


