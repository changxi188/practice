//
// Created by mr on 2020/7/16.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <chrono>
#include "orb_self.h"


using namespace std;


void ComputeORB(const cv::Mat &img, vector<cv::KeyPoint> &keypoints, vector<DescType> &descriptors){
    const int half_patch_size = 8;
    const int half_boundary = 16;
    int bad_points = 0;

    for (auto &kp : keypoints){
        if (kp.pt.x < half_boundary || kp.pt.y < half_boundary || kp.pt.x >= img.cols - half_boundary || kp.pt.y >= img.rows - half_boundary){
            // outsid
            bad_points++;
            descriptors.push_back({});
            continue;
        }

        float m01 = 0, m10 = 0;
        /*
         *  row == heigh == Point.y
         *  col == width == Point.x
         *  Mat::at(Point(x, y)) == Mat::at(y,x)
         */
        for (int dx = -half_patch_size; dx < half_patch_size; ++dx){
            for (int dy = -half_patch_size; dy < half_patch_size; ++dy){
                uchar pixel = img.at<uchar>(kp.pt.y + dy, kp.pt.x + dx);
                m10 += dx * pixel;
                m01 += dy * pixel;
            }
        }
        float m_sqrt = sqrt(m01 * m01 + m10 * m10) + 1e - 18;
        float sin_theta = m01 / m_sqrt;
        float cos_theta = m10 / m_sqrt;

        DescType desc(8, 0);

        for (int i = 0; i < 8; ++i){
            uint32_t d = 0;
            for (int k = 0; k < 32; ++k){

            }
        }

    }
}

void BfMatch(const vector<DescType> &desc1, const vector<DescType> &desc2, vector<cv::DMatch> &matches){

}

int main(int argc, char** argv){

    cv::Mat img1 = cv::imread(argv[1]);
    cv::Mat img2 = cv::imread(argv[2]);

    vector<cv::KeyPoint> keypoints1, keypoints2;
    vector<DescType> descriptors1, descriptors2;
    vector<cv::DMatch> matches;

    cv::FAST(img1, keypoints1, 40);
    cv::FAST(img2, keypoints2, 40);

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    ComputeORB(img1, keypoints1, descriptors1);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();

    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);


    t1 = chrono::steady_clock::now();
    ComputeORB(img2, keypoints2, descriptors2);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    t1 = chrono::steady_clock::now();
    BfMatch(descriptors1, descriptors2, matches);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    cv::Mat img_show;
    cv::drawMatches(img1, keypoints1, img2, keypoints2, matches, img_show);
    cv::imwrite("matches.png", img_show);
    cv::imshow("matches", img_show);
    cv::waitKey(0);
}
