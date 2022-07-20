#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
int main(int argc, char** argv)
{
    cv::Mat img1;
    img1 = cv::imread(argv[1], cv::IMREAD_COLOR);
    if (img1.empty())
    {
        cout << "image read error" << endl;
        cout << "USAGE: ./1 img" << endl;
        return -1;
    }

    cv::Mat img2 = img1(cv::Range::all(), cv::Range(1, 3));

    cv::imshow("aaa", img1);
    cv::imshow("bbb", img2);
    cv::waitKey(0);

    cv::Mat R(cv::Size(2, 2), true);
    

    return 0;
}
