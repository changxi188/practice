#pragma once
#ifndef __ORB_H__
#define __ORB_H__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <nmmintrin.h>

typedef std::vector<uint32_t> DescType;

class MyORB{
public:
	MyORB(const cv::Mat& first_image, const cv::Mat& second_image) : first_image_(first_image), second_image_(second_image) {}

	// TODO : define my self KeyPoint and DMatch (其他的基础类也可以尝试去定义)
	struct KeyPoint{ 
		cv::Point2f pt;

	};
	struct DMatch{ 
		int q_id;
		int t_id;
		float distance;
	};

	// 计算左图ORB特征
	void computeLeftORB();

	// 计算右图ORB特征
	void computeRightORB();

	// 暴力匹配
	void bfMatch();

	// 获取匹配结果
	std::vector<cv::DMatch> getMatches();
	// 获取特征点
	std::vector<cv::KeyPoint> getFirstKeyPoints();
	std::vector<cv::KeyPoint> getSecondKeyPoints();

	~MyORB(){}
	

private:
	// functions
	// 提取特征点, 计算描述子
	void computeORB(const cv::Mat& img, std::vector<cv::KeyPoint>& keypoints, std::vector<DescType>& descs);



private:
	
	// parameters
	const int half_boundary_ = 16;
	const int half_patch_size_ = 8;

	const int max_dist_ = 60;

	// datas
	// 左右图像
	cv::Mat first_image_, second_image_;
	// 特征点
	std::vector<cv::KeyPoint> keypoints1_, keypoints2_;
	// 描述子
	std::vector<DescType> descriptors1_, descriptors2_;		
	// 匹配
	std::vector<cv::DMatch> matches_;
};

inline
std::vector<cv::DMatch> MyORB::getMatches(){
	return matches_;
}

inline
std::vector<cv::KeyPoint> MyORB::getFirstKeyPoints(){
	return keypoints1_;
}

inline
std::vector<cv::KeyPoint> MyORB::getSecondKeyPoints(){
	return keypoints2_;
}


#endif
