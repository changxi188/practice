#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <Eigen/Core>
#include <sophus/se3.hpp>
#include <chrono>
#include <iomanip>

using namespace std;

typedef vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> VecVector2d;
typedef vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> VecVector3d;


cv::Point2d pixel2cam(const cv::Point2d &p, const cv::Mat &K){

    cv::Point2d temp;
    temp.x = (p.x - K.at<int>(0, 2)) / K.at<int>(0, 0);
    temp.y = (p.y - K.at<int> (1 ,2)) / K.at<int>(1, 1);
    return temp;
};

void find_feature_matches(const cv::Mat &img_1, const cv::Mat &img_2,
        vector<cv::KeyPoint> &kps1,
        vector<cv::KeyPoint> &kps2,
        vector<cv::DMatch> &mts){
    cv::Mat descriptors_1, descriptors_2;
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();

    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");

    detector->detect(img_1, kps1);
    detector->detect(img_2, kps2);

    descriptor->compute(img_1, kps1, descriptors_1);
    descriptor->compute(img_2, kps2, descriptors_2);

    vector<cv::DMatch> match;
    matcher->match(descriptors_1, descriptors_2, match);

    double min_dist = 10000, max_dist = 0;

    for(int i = 0; i < descriptors_1.rows; i++){
        double  dist = match[i].distance;
        if(dist < min_dist) min_dist = dist;
        if(dist > max_dist) max_dist = dist;
    }

    cout << "Max dist " << max_dist << endl;
    cout << "Min dist " << min_dist << endl;

    for(int i = 0; i < descriptors_1.rows; ++i){
        if(match[i].distance <= max(2 * min_dist, 30.0)){
            mts.push_back(match[i]);
        }
    }

    cout << mts.size() << endl;
}

void bundleAdjustmentGaussNewton(
        const VecVector3d &points_3d,
        const VecVector2d &points_2d,
        const cv::Mat &K,
        Sophus::SE3d &pose) {
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    const int iterations = 10;
    double cost = 0, lastCost = 0;
    double fx = K.at<double>(0, 0);
    double fy = K.at<double>(1, 1);
    double cx = K.at<double>(0, 2);
    double cy = K.at<double>(1, 2);

    for (int iter = 0; iter < iterations; iter++) {
        Eigen::Matrix<double, 6, 6> H = Eigen::Matrix<double, 6, 6>::Zero();
        Vector6d b = Vector6d::Zero();

        cost = 0;
        // compute cost
        for (int i = 0; i < points_3d.size(); i++) {
            Eigen::Vector3d pc = pose * points_3d[i];
            double inv_z = 1.0 / pc[2];
            double inv_z2 = inv_z * inv_z;
            Eigen::Vector2d proj(fx * pc[0] / pc[2] + cx, fy * pc[1] / pc[2] + cy);

            Eigen::Vector2d e = points_2d[i] - proj;

            cost += e.squaredNorm();
            Eigen::Matrix<double, 2, 6> J;
            J << -fx * inv_z,
                    0,
                    fx * pc[0] * inv_z2,
                    fx * pc[0] * pc[1] * inv_z2,
                    -fx - fx * pc[0] * pc[0] * inv_z2,
                    fx * pc[1] * inv_z,
                    0,
                    -fy * inv_z,
                    fy * pc[1] * inv_z2,
                    fy + fy * pc[1] * pc[1] * inv_z2,
                    -fy * pc[0] * pc[1] * inv_z2,
                    -fy * pc[0] * inv_z;

            H += J.transpose() * J;
            b += -J.transpose() * e;
        }

        Vector6d dx;
        dx = H.ldlt().solve(b);

        if (isnan(dx[0])) {
            cout << "result is nan!" << endl;
            break;
        }

        if (iter > 0 && cost >= lastCost) {
            // cost increase, update is not good
            cout << "cost: " << cost << ", last cost: " << lastCost << endl;
            break;
        }

        // update your estimation
        pose = Sophus::SE3d::exp(dx) * pose;
        lastCost = cost;

        cout << "iteration " << iter << " cost=" << std::setprecision(12) << cost << endl;
        if (dx.norm() < 1e-6) {
            // converge
            break;
        }
    }

    cout << "pose by g-n: \n" << pose.matrix() << endl;
}

int main(int argc, char**argv){

    cout << "usage: ./1 img1 img2 depth1 depth2" << endl;

    cv::Mat img1 = cv::imread(argv[1], 1);
    cv::Mat img2 = cv::imread(argv[2], 1);
    assert(img1.data && img2.data &&"Can not load images");

    vector<cv::KeyPoint> keypoints_1, keypoints_2;
    vector<cv::DMatch> matches;
    find_feature_matches(img1, img2, keypoints_1, keypoints_2, matches);

    // 16位无符号数, 单通道图像
    cv::Mat d1 = cv::imread(argv[3], CV_LOAD_IMAGE_UNCHANGED);
    cv::Mat K = (cv::Mat_<double>(3, 3) << 520.9, 0, 325.1, 521.0, 249.7, 0, 0, 1);
    vector<cv::Point3f> ptf_3d;
    vector<cv::Point2f> ptf_2d;

    // 建立3D点
    for(auto m : matches){

        ushort d = d1.ptr<unsigned short>(int(keypoints_1[m.queryIdx].pt.y))[int(keypoints_1[m.queryIdx].pt.x)];
        if(d == 0)
            continue;
        float dd = d / 5000.0;
        cv::Point2d p1 = pixel2cam(keypoints_1[m.queryIdx].pt, K);
        ptf_3d.push_back(cv::Point3f(p1.x * dd, p1.y * dd, dd));
        ptf_2d.push_back(keypoints_2[m.trainIdx].pt);
    }

    cout << "3d-2d pairs" << ptf_3d.size() << endl;

    VecVector3d pts_3d_eigen;
    VecVector2d pts_2d_eigen;
    for(std::size_t i = 0; i < ptf_3d.size(); ++i){
        pts_3d_eigen.push_back(Eigen::Vector3d(ptf_3d[i].x, ptf_3d[i].y, ptf_3d[i].z));
        pts_2d_eigen.push_back(Eigen::Vector2d(ptf_2d[i].x, ptf_2d[i].y));
    }

    Sophus::SE3d pose_gn;
    bundleAdjustmentGaussNewton(pts_3d_eigen, pts_2d_eigen, K, pose_gn);



    return 0;
}





