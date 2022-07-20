//
// Created by mr on 2020/7/18.
//

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;


int main(int argc, char** argv){

    if (argc != 3){
        cout << "please enter right image path" << endl;
        return  -1;
    }

    cv::Mat img_1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);

    if (img_1.empty() || img_2.empty()){
        cout << "image is None, please check image path" <<  endl;
        return -2;
    }

    vector<cv::KeyPoint> keypoints1, keypoints2;
    vector<cv::DMatch> matches;
    find_image_matches(img_1, img_2, keypoints1, keypoints2, matches);
    cout << matches.size() << endl;

    /*
    // dras match image
    cv::Mat imgMatch;
    cv::drawMatches(img_1, keypoints1, img_2, keypoints2, matches, imgMatch);
    cv::imshow("match_img", imgMatch);
    */

    // estimate relative movement
    cv::Mat R21, t;
    pose_estimate_2d2d(img_1, img_2, keypoints1, keypoints2, matches, R21, t);
    cout << "Rotation matrix is : \n" <<R21 << endl;
    cout << "translation is : \n"<< t << endl;


    // triangulation
    std::vector<cv::Point3d> points;
    triangulation(keypoints1, keypoints2, matches, R21, t, points);

    // vertify relation between triangulatized points and projection points
    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    cv::Mat img1_plot = img_1.clone();
    cv::Mat img2_plot = img_2.clone();

	typedef Eigen::Matrix<num_t, poseDim, poseDim, Eigen::ColMajor> poseMatrixType;
	typedef linearSolver<poseMatrixType> linearSolverType;

    for (int i = 0; i < matches.size(); ++i){
        // first image
        float depth1 = points[i].z;
        cout << " depth : " << depth1 << endl;
        cv::Point2d pt1_cam = pixel2camera(keypoints1[matches[i].queryIdx].pt, K);
        cv::circle(img1_plot, keypoints1[matches[i].queryIdx].pt, 2, get_color(depth1), 2);

        // second image
        cv::Mat pt2_trans = R21 * (cv::Mat_<double>(3, 1) << points[i].x, points[i].y, points[i].z ) + t;
        float depth2 = pt2_trans.at<double>(2, 0);
        cv::circle(img2_plot, keypoints2[matches[i].trainIdx].pt , 2, get_color(depth2), 2);
    }
    cv::imshow("img 1", img1_plot);
    cv::imshow("img 2", img2_plot);
    cv::waitKey(0);


    return 0;

}
