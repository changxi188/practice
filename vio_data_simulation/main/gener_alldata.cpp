//
// Created by hyj on 17-6-22.
//

#include <sys/stat.h>
#include <fstream>
#include <utility>

#include "../src/common_types.h"
#include "../src/data_generation.h"
#include "../src/imu.h"
#include "../src/utilities.h"
#include "../src/visualize.h"

int main()
{
    // 建立keyframe文件夹
    mkdir("keyframe", 0777);

    Visualizer visualizer;

    // IMU model
    IMU   imu_gen(params);

    DataGeneration data_generation(imu_gen);

    data_generation.GeneratePointsAndLines();

    data_generation.GenerateImuDataAndNoisedData();

    data_generation.TestImu("imu_pose.txt", "imu_int_pose.txt", euler_integral_results);

    data_generation.TestImu("imu_pose_noise.txt", "imu_int_pose_noise.txt", euler_integral_noised_results);

    data_generation.GenerateCameraData();

    data_generation.GeneratePointsObs();

    data_generation.GenerateLinesObs();

    /*
    // lines obs in image
    for(int n = 0; n < camdata.size(); ++n)
    {
        MotionData data = camdata[n];
        Eigen::Matrix4d Twc = Eigen::Matrix4d::Identity();
        Twc.block(0, 0, 3, 3) = data.Rwb;
        Twc.block(0, 3, 3, 1) = data.twb;

        // 遍历所有的特征点，看哪些特征点在视野里
        // std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > points_cam;    //
    ３维点在当前cam视野里 std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > features_cam;  //
    对应的２维图像坐标 for (int i = 0; i < lines.size(); ++i) { Line linept = lines[i];

            Eigen::Vector4d pc1 = Twc.inverse() * linept.first; // T_wc.inverse() * Pw  -- > point in cam frame
            Eigen::Vector4d pc2 = Twc.inverse() * linept.second; // T_wc.inverse() * Pw  -- > point in cam frame

            if(pc1(2) < 0 || pc2(2) < 0) continue; // z必须大于０,在摄像机坐标系前方

            Eigen::Vector4d obs(pc1(0)/pc1(2), pc1(1)/pc1(2),
                                pc2(0)/pc2(2), pc2(1)/pc2(2));
            //if(obs(0) < params.image_h && obs(0) > 0 && obs(1)> 0 && obs(1) < params.image_w)
            {
                features_cam.push_back(obs);
            }
        }

        // save points
        std::stringstream filename1;
        filename1<<"keyframe/all_lines_"<<n<<".txt";
        save_lines(filename1.str(),features_cam);
    }
    */

    std::cout << "111111 " << std::endl;
    return 0;
}
