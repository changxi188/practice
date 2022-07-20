//
// Created by mr on 2020/7/18.
//

#ifndef VO_BY_SELF_TRIANGULATION_H
#define VO_BY_SELF_TRIANGULATION_H

#include <iostream>
#include <opencv2/opencv.hpp>

// image match
void find_image_matches(const cv::Mat &img_1, const cv::Mat &img_2,
                        std::vector<cv::KeyPoint> &keypoints1,
                        std::vector<cv::KeyPoint> &keypoints2,
                        std::vector<cv::DMatch> &matches){

    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");

    // 1. find keypoints
    detector->detect(img_1, keypoints1);
    detector->detect(img_2, keypoints2);

    // 2. compute descript
    cv::Mat descriptors1, descriptors2;
    descriptor->compute(img_1, keypoints1, descriptors1);
    descriptor->compute(img_2, keypoints2, descriptors2);

    //descriptors1.convertTo(descriptors1, CV_32F);
    //descriptors2.convertTo(descriptors2, CV_32F);

    // 3. compute matcher
    std::vector<cv::DMatch> match;
    matcher->match(descriptors1, descriptors2, match);

    double minDist = 1000, maxDist = 10;
    for (int i = 0; i < descriptors1.rows; ++i){
        if (match[i].distance < minDist) minDist = match[i].distance;
        if (match[i].distance > maxDist) maxDist = match[i].distance;
    }

    std::cout << minDist << std::endl;
    std::cout << maxDist << std::endl;
    std::cout << match.size() << std::endl;
    for (int i = 0; i < descriptors1.rows; ++i){
        if (match[i].distance <= std::max(2 * minDist, 30.0)){
            matches.push_back(match[i]);
        }
    }

};

// pose estimate
void pose_estimate_2d2d(const cv::Mat &img_1, const cv::Mat &img_2,
                        const std::vector<cv::KeyPoint> &keypoints1,
                        const std::vector<cv::KeyPoint> &keypoints2,
                        const std::vector<cv::DMatch> &matches,
                        cv::Mat &R, cv::Mat &t){

    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);

    // switch cv::KeyPoint to cv::Point2f
    std::vector<cv::Point2f> points1;
    std::vector<cv::Point2f> points2;

    for (int i = 0; i < matches.size(); ++i){
        points1.push_back(keypoints1[matches[i].queryIdx].pt);
        points2.push_back(keypoints2[matches[i].trainIdx].pt);
    }

    // compute Essential matrix

    // carmera center point
    cv::Point2f principal_point(325.1, 249.7);
    // camera focal_length
    int focal_length = 521;
    cv::Mat essential_matrix;
    essential_matrix = cv::findEssentialMat(points1, points2, focal_length, principal_point);

    // recover R and t from essential matrix
    cv::recoverPose(essential_matrix, points1, points2, R, t, focal_length, principal_point);

}


cv::Point2f pixel2camera(const cv::Point2f p, const cv::Mat &K){
    return cv::Point2f (
            (p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
            (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
    );
}
void triangulation(const std::vector<cv::KeyPoint> &keypoints1,
                   const std::vector<cv::KeyPoint> &keypoints2,
                   const std::vector<cv::DMatch> &matches,
                   const cv::Mat &R, const cv::Mat &t,
                   std::vector<cv::Point3d> &points){
    cv::Mat K =(cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    cv::Mat T1 = (cv::Mat_<float>(3, 4)<<
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0);
    cv::Mat T2 = (cv::Mat_<float>(3, 4) <<
            R.at<double>(0, 0), R.at<double>(0, 1), R.at<double>(0, 2), t.at<double>(0, 0),
            R.at<double>(1, 0), R.at<double>(1, 1), R.at<double>(1, 2), t.at<double>(0, 1),
            R.at<double>(2, 0), R.at<double>(2, 1), R.at<double>(2, 2), t.at<double>(0, 2));

    std::vector<cv::Point2f> pts_1, pts_2;

    for (cv::DMatch m : matches){
        // switch pixel coordinate to camera coordinate
        pts_1.push_back(pixel2camera(keypoints1[m.queryIdx].pt, K));
        pts_2.push_back(pixel2camera(keypoints2[m.trainIdx].pt, K));
    }

    cv::Mat pts_4d;
    cv::triangulatePoints(T1, T2, pts_1, pts_2, pts_4d);

    // 转换成非齐次坐标
    for (int i = 0; i < pts_4d.cols; ++i){
        cv::Mat x = pts_4d.col(i);
        x /= x.at<float>(3, 0);
        cv::Point3d p(
                x.at<float>(0, 0),
                x.at<float>(1, 0),
                x.at<float>(2, 0)
                );
        points.push_back(p);
    }
}

inline cv::Scalar get_color(float depth){
    float up_th = 50, low_th = 10, th_range = up_th- low_th;
    if (depth > up_th) depth = up_th;
    if (depth < low_th) depth = low_th;
    return cv::Scalar(255 * depth / th_range, 0, 255 * (1 - depth /th_range));
}

#endif //VO_BY_SELF_TRIANGULATION_H
