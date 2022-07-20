#include <iostream>
// opencv.hpp 模块几乎包含了所有的模块
#include <opencv2/opencv.hpp>
#include "pose_estimation_3d2d.cpp"

using namespace  std;



int main(int argc, char** argv) {

    if (argc != 3){
        std::cout << "don't have image path" << std::endl;
        return -1;;
    }

    cv::Mat img_1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);

    //
    cv::imshow("img_1", img_1);
    cv::imshow("img_2", img_2);

    if (img_1.empty() || img_2.empty()){
        std::cout << "image open errro" << std::endl;
        return -1;
    }

    std::vector<cv::KeyPoint> keypoints1, keypoints2;
    std::vector<cv::DMatch> matches;

    // 第一步 : 寻找匹配点
    find_feature_matches(img_1, img_2, keypoints1, keypoints2, matches);
    std::cout << "共找到 " << matches.size() << "组匹配点" << std::endl;

    // 第二步 : 估计两张图片间的相对位姿
    cv::Mat R, t;
    pose_estimation_2d2d(keypoints1, keypoints2, matches,R,t);
    cv::Mat matchImg;
    cv::drawMatches(img_1, keypoints1, img_2, keypoints2, matches, matchImg);
    cv::imshow("matchImg", matchImg);

    // 第三步 : 验证E = T^R*sacale
    cv::Mat t_x =
            (cv::Mat_<double>(3, 3) <<  0, -t.at<double>(2, 0), t.at<double>(1, 0),
                        t.at<double>(2,0), 0, -t.at<double>(0,0),
                        -t.at<double>(1,0), t.at<double>(0, 0), 0);

    std::cout << "t^R " << std::endl << t_x * R << std::endl;

    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    cout << matches.size() << endl;
    for (cv::DMatch m : matches){
        cv::Point2d pt1 = pixel2cam(keypoints1[m.queryIdx].pt, K);
        cv::Mat y1 = (cv::Mat_<double>(3, 1) << pt1.x, pt1.y, 1);
        cv::Point2d pt2 = pixel2cam(keypoints2[m.trainIdx].pt, K);
        cv::Mat y2 = (cv::Mat_<double>(3, 1) << pt2.x, pt2.y, 1);
        cv::Mat d = y2.t() * t_x * R * y1;
        cout << "epipolar constraint = " << d << endl;
    }
    cv::waitKey(0);
    return 0;

}

