#pragma once
#ifndef __TRIANGULATION_H__
#define __TRIANGULATION_H__
#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>


class Triangulation{
public:
	Triangulation(const cv::Mat& K) : K_(K) {}
	
	// 初始化参数
	void init(const cv::Mat& R, const cv::Mat& t, 
			  const std::vector<cv::Point2f>& pts_1, const std::vector<cv::Point2f>& pts_2);
	
	// 像素坐标到相机坐标的转换
	cv::Point2f pixel2cam(const cv::Point2f& p);
	
	// 三角化
	void triang();

	// 获取最终三角化后的结果:
	void getPw(std::vector<cv::Point3f>& pts_w);
	
private:
	
	// 内参
	cv::Mat K_;

	// 变换矩阵
	cv::Mat T1_, T2_;

	// 匹配的特征点
	std::vector<cv::Point2f> pts_2d_1_, pts_2d_2_;

	// 相机坐标系下特征点
	std::vector<cv::Point2f> pts_c_1_, pts_c_2_;

	// 世界坐标系下三维空间点
	std::vector<cv::Point3f> pts_3d_;
	
};

inline
void Triangulation::getPw(std::vector<cv::Point3d>& pts_w){
	pts_w = pts_3d_;
}


#endif
