#pragma once
#ifndef __POSE_ESTIMATION_2D_2D_H__
#define __POSE_ESTIMATION_2D_2D_H__
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>

class PoseEstimation2d2d{
public:
	
	PoseEstimation2d2d(const cv::Mat& K) : K_(K), 
				principal_point_(cv::Point2d(K_.at<double>(0, 2), K_.at<double>(1, 2))), 
				focal_length_(K_.at<double>(1, 1)) {}

	void findEssentialMatrix(const std::vector<cv::DMatch>& matches, 
							 const std::vector<cv::KeyPoint>& kps1,
							 const std::vector<cv::KeyPoint>& kps2);
	
	void getRt(cv::Mat& R, cv::Mat& t);

	void getMatchPoints(std::vector<cv::Point2f>& p1, std::vector<cv::Point2f>& p2);

private:

	// 相机内参
	cv::Mat K_;
	
	// 相机主点
	cv::Point2d principal_point_;

	// 焦距
	int focal_length_;
	
	// 匹配的2d点
	std::vector<cv::Point2f> pts_2d_1_, pts_2d_2_;

	

	// 基础矩阵
	cv::Mat fundamental_matrix_;	

	// 本质矩阵
	cv::Mat essential_matrix_;

	// 旋转平移
	cv::Mat R_, t_;

};
inline
void PoseEstimation2d2d::getRt(cv::Mat& R, cv::Mat& t){
	R = R_;
	t = t_;
}

inline
void PoseEstimation2d2d::getMatchPoints(std::vector<cv::Point2f>& pts_2d_1, 
										std::vector<cv::Point2f>& pts_2d_2){
	pts_2d_1 = pts_2d_1_;
	pts_2d_2 = pts_2d_2_;
}
#endif
