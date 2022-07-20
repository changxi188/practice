//
// Created by mr on 2020/7/19.
//
#include "pose_estimation_3d2d.h"
#include <Eigen/Core>


using namespace std;

int main(int argc, char** argv){

    if(argc != 5){
       cout << "usage : pose_estimation_3d2d img1 img2 depth1 depth2 " << endl;
        return -1;
    }

    cv::Mat img_1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
    if (img_1.empty() || img_2.empty()){
        cout << "don't open right image " << endl;
        return -2;
    }

    vector<cv::KeyPoint> keypoints_1, keypoints_2;
    vector<cv::DMatch> matches;
    find_feature_matches(img_1, img_2, keypoints_1, keypoints_2, matches);

    cv::Mat img_show;
    cv::drawMatches(img_1, keypoints_1, img_2, keypoints_2, matches, img_show);
    cv::imshow("matches image", img_show);

    cv::Mat d1 = cv::imread(argv[3], CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 0, 521.0, 249.7, 0, 0, 1);
    vector<cv::Point3f> pts_3d;
    vector<cv::Point2f> pts_2d;

    for (const auto &m : matches){
        ushort d = d1.ptr<unsigned short>(int(keypoints_1[m.queryIdx].pt.y))[int(keypoints_1[m.queryIdx].pt.x)];
        if (d == 0)
            continue;
        float dd = d / 5000.0;
        cv::Point2d p1 = pixel2cam(keypoints_1[m.queryIdx].pt, K);
        pts_3d.push_back(cv::Point3f(p1.x * dd , p1.y * dd, dd));
        pts_2d.push_back(keypoints_2[m.trainIdx].pt);
    }

    cout << "3d - 2d pairs : " << pts_3d.size() << endl;

    chrono::steady_clock::time_point t1 =  chrono::steady_clock::now();
    cv::Mat r, t;
    cv::solvePnP(pts_3d, pts_2d, K, cv::Mat(), r, t, false);
    cv::Mat R;
    cv::Rodrigues(r, R);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "compute R by opencv pnp  equal : \n" << R << endl;
    cout << "compute t by opencv pnp equal : \n" << t << endl;
    cout << "solve pnp in opencv cost time : " << time_used.count()  <<  " seconds" << endl;


    VecVector2d pts_2d_eigen;
    VecVector3d pts_3d_eigen;
    for (std::size_t i = 0; i < pts_3d.size(); ++i){
        pts_2d_eigen.push_back(Eigen::Vector2d(pts_2d[i].x, pts_2d[i].y));
        pts_3d_eigen.push_back(Eigen::Vector3d(pts_3d[i].x, pts_3d[i].y, pts_3d[i].z));
    }

    std::cout << "calling bundle adjustment by gauss newton" << std::endl;
    Sophus::SE3d pose_gn;
    t1 = chrono::steady_clock::now();
    bundleAdjustmentGaussNewton(pts_2d_eigen, pts_3d_eigen, K, pose_gn);
    t2 = chrono::steady_clock::now();
    time_used = chrono::duration_cast<chrono::duration<double>>( t2 - t1);
    std::cout << "solve pnp by gauss newton cost time " << std::endl;


    std::cout << "calling bundle adjustment by g2o " << std::endl;
    Sophus::SE3d pose_g2o;
    t1 = chrono::steady_clock::now();
    bundleAdjustmentG2O(pts_2d_eigen, pts_3d_eigen, K, pose_g2o);



    cv::waitKey(0);
}

