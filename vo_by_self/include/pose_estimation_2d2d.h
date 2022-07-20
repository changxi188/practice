//
// Created by mr on 2020/7/18.
//

#ifndef VO_BY_SELF_POSE_ESTIMATION_2D2D_H
#define VO_BY_SELF_POSE_ESTIMATION_2D2D_H

#include <opencv2/opencv.hpp>
#include <iostream>


void find_feature_matches(const cv::Mat &img_1, const cv::Mat &img_2,
        std::vector<cv::KeyPoint> &keypoints1,
        std::vector<cv::KeyPoint> &keypoints2,
        std::vector<cv::DMatch> &matches){

    // 初始化
    cv::Mat descriptors1, descriptors2;
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");


    // 第一步 : 检测Oriented FAST角点
    detector->detect(img_1, keypoints1);
    detector->detect(img_2, keypoints2);

    // 第二步 : 根据角点位置计算BRIEF描述子
    descriptor->compute(img_1, keypoints1, descriptors1);
    descriptor->compute(img_2, keypoints2, descriptors2);

    // 第三步 : 对两幅图像中的BRIEF描述子进行匹配, 使用Hamming距离
    std::vector<cv::DMatch> match;
    matcher->match(descriptors1,descriptors2, match);

    // 第四步 : 匹配点筛选
    // 计算最大距离和最小距离
    double min_dist = 1000, max_dist = 10;
    for (int i = 0; i < descriptors1.rows; ++i){
        double dist = match[i].distance;
        if (dist < min_dist) min_dist = dist;
        if (dist > max_dist) max_dist = dist;
    }

    std::cout << " min distance is " << min_dist << std::endl;
    std::cout << " max distance is " << max_dist << std::endl;

    // 描述子间的距离大于最小距离两倍时就认为是误匹配, 但有时距离非常小翔设置一个经验值30作为下限
    for (int i = 0; i < descriptors1.rows; ++i){
        if(match[i].distance <= std::max(2 * min_dist, 30.0)){
            matches.push_back(match[i]);
        }
    }
}

void pose_estimation_2d2d(const std::vector<cv::KeyPoint> &keypoints1,
                          const std::vector<cv::KeyPoint> &keypoints2,
                          const std::vector<cv::DMatch> &matches,
                          cv::Mat &R, cv::Mat &t){
    // 相内参, TUM Freiburg2;
    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    // 把匹配点换成point2f的形式
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;

    for (int i = 0; i < matches.size(); ++i){
        points1.push_back(keypoints1[matches[i].queryIdx].pt);
        points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    // 计算基础矩阵
    cv::Mat fundamental_matrix;
    fundamental_matrix = cv::findFundamentalMat(points1, points2, CV_FM_8POINT);

    // 计算本质矩阵
    // 相机光心, TUM dataset标定值
    cv::Point2d principal_point(325.1, 249.7);
    // 相机焦距, TUM dataset标定值
    double focal_length = 521;
    cv::Mat essential_matrix;
    essential_matrix = cv::findEssentialMat(points1, points2, focal_length, principal_point);
    std::cout << "homography_matrix is" << std::endl << essential_matrix << std::endl;


    // 计算单应矩阵
    cv::Mat homography_matrix;
    homography_matrix = cv::findHomography(points1, points2, cv::RANSAC, 3);

    // 从本质矩阵中恢复旋转和平移信息
    // 此函数仅在Opencv3中提供
    cv::recoverPose(essential_matrix, points1, points2, R, t, focal_length, principal_point);
    std::cout << "R is " << std::endl << R << std::endl;
    std::cout << "t is " << std::endl << t << std::endl;

}

cv::Point2d pixel2cam(const cv::Point2d &keypoint, const cv::Mat K){
    return cv::Point2d(
            (keypoint.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
            (keypoint.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
                    );
}

#endif //VO_BY_SELF_POSE_ESTIMATION_2D2D_H
