#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <opencv2/opencv.hpp>
#include "orb.h"
#include "pose_estimation_2d_2d.h"
#include "triangulation.h"
#include "visiual.h"

using namespace std;
using namespace cv;

int main(){

	// 相机内参
	cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
	

	// read image
	cv::Mat first_image = cv::imread("/home/mr/Downloads/practice/triangulation/1.png", 0);
	cv::Mat second_image = cv::imread("/home/mr/Downloads/practice/triangulation/2.png", 0);	
	if (first_image.data == nullptr || second_image.data == nullptr){
		cout << "cannot open image" << endl;
	}

	auto orb = std::make_shared<MyORB>(first_image, second_image);

	auto pose = std::make_shared<PoseEstimation2d2d>(K);

	auto tri = std::make_shared<Triangulation>(K);

	// ORB特帧点提取, 特征点描述	
	orb->computeLeftORB();
	orb->computeRightORB();

	// 特征点匹配
	orb->bfMatch();

	// 读取ORB结果
	std::vector<cv::DMatch> matches = orb->getMatches();
	std::vector<cv::KeyPoint> first_keypoints = orb->getFirstKeyPoints();
	std::vector<cv::KeyPoint> second_keypoints = orb->getSecondKeyPoints();

	// plot the matches
	cout << "共有匹配点 : " << matches.size() << " 个" << endl;
	cv::Mat image_show;
	cv::drawMatches(first_image, first_keypoints, second_image, second_keypoints, matches, image_show);
	cv::imshow("matches", image_show);
	cv::waitKey(0);

	
	// 旋转和平移
	cv::Mat R, t;
	// 2d匹配点
	std::vector<cv::Point2f> pts_2d_1, pts_2d_2;
	// 2D-2D对极几何求解R, t
	pose->findEssentialMatrix(matches, first_keypoints, second_keypoints);

	pose->getRt(R, t);
	pose->getMatchPoints(pts_2d_1, pts_2d_2);
	cout << "R : " << endl;
	cout << R << endl;
	cout << "t : " << endl;
	cout << t << endl;
	
	// 三角化
	std::vector<cv::Point3f> pts_w;
	tri->init(R, t, pts_2d_1, pts_2d_2);
	tri->triang();
	tri->getPw(pts_w);
	//cout << pts_w.size() << endl;
	//cout << pts_w[0].x << endl;

	// 可视化
	showPointCloud(pts_w);


	return 0;
}
