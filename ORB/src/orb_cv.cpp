#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>

using namespace std;

int main(int argc, char** argv){

    if (argc != 3){
        cout << "usage: feature_extraction img1 img2" << endl;
        return 1;
    }

    cv::Mat img_1 = cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
    cv::Mat img_2 = cv::imread(argv[2], CV_LOAD_IMAGE_COLOR);
    assert(img_1.data != nullptr && img_2.data != nullptr);

    // 初始化
    std::vector<cv::KeyPoint> keypoint1, keypoint2;
    cv::Mat descriptors_1, descriptors_2;
    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");

    // 第一步 : 检测Orented Fast 角点位置
    chrono::steady_clock::time_point  t1 = chrono::steady_clock::now();
    detector->detect(img_1, keypoint1);
    detector->detect(img_2, keypoint2);

    // 第二步 : 根据角点位置计算BRIEF描述子
    descriptor->compute(img_1, keypoint1, descriptors_1);
    descriptor->compute(img_2, keypoint2, descriptors_2);
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_uesed = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "extract ORB cost = " << time_uesed.count() << "seconds" << endl;

    cv::Mat outimg1;
    cv::drawKeypoints(img_1, keypoint1, outimg1, cv::Scalar::all(-1), cv::DrawMatchesFlags::DEFAULT);
    cv::imshow("ORB features", outimg1);

    // 第三步 : 对两幅图像中BRIEF描述子进行匹配, 使用Hamming距离
    vector<cv::DMatch> matches;
    t1 = chrono::steady_clock::now();
    matcher->match(descriptors_1, descriptors_2, matches);
    t2 = chrono::steady_clock::now();
    time_uesed = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "match ORB cost = " << time_uesed.count() << "seconds" << endl;

    // 第四步 : 匹配点对筛选
    auto min_max = minmax_element(matches.begin(), matches.end(), [](const cv::DMatch &m1, const cv::DMatch &m2) {return m1.distance < m2.distance;});
    double min_dist = min_max.first->distance;
    double max_dist = min_max.second->distance;


    cout << "--- Max dist : %f \n" << max_dist << endl;
    cout << "--- Min dist : %f \n" << min_dist << endl;

    std::vector<cv::DMatch> good_matches;
    for (int i = 0; i < descriptors_1.rows; ++i) {
        if (matches[i].distance <= max(2 * min_dist, 30.0)){
            good_matches.push_back(matches[i]);
        }
    }

    // 第五步 : 绘制匹配结果
    cv::Mat img_match;
    cv::Mat img_goodmatch;
    cv::drawMatches(img_1, keypoint1, img_2, keypoint2, matches, img_match);
    cv::drawMatches(img_1, keypoint1, img_2, keypoint2, good_matches, img_goodmatch);
    cv::imshow("all matches", img_match);
    cv::imshow("good matches", img_goodmatch);
    cv::waitKey(0);

}
