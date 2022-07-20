//
// Created by mr on 2020/7/16.
//

#ifndef ORB_ORB_SELF_H
#define ORB_ORB_SELF_H
#pragma once

#include <opencv2/core/mat.hpp>

// global variables
std::string firt_file = "./../1.png";
std::string second_file = "./../2.png";

// 32 bit unsigned int, will have 8, 8 * 32 = 256
typedef std::vector<uint32_t> DescType;

void ComputeORB(const cv::Mat &img, std::vector<cv::KeyPoint> &keypoints, std::vector<DescType> &descriptors);


void BfMatch(const std::vector<DescType> &desc1, const std::vector<DescType> &desc2, std::vector<cv::DMatch> &matches);



#endif //ORB_ORB_SELF_H
