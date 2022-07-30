#include "data_generation.h"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <algorithm>
#include <chrono>
#include <set>
#include <thread>
#include <vector>

void DataGeneration::GeneratePointsAndLines()
{

    std::ifstream f;
    f.open("house_model/house.txt");

    while (!f.eof())
    {
        std::string s;
        std::getline(f, s);
        if (!s.empty())
        {
            std::stringstream ss;
            ss << s;
            double x, y, z;
            ss >> x;
            ss >> y;
            ss >> z;
            Eigen::Vector4d pt0(x, y, z, 1);
            ss >> x;
            ss >> y;
            ss >> z;
            Eigen::Vector4d pt1(x, y, z, 1);

            bool isHistoryPoint = false;
            for (int i = 0; i < points.size(); ++i)
            {
                Eigen::Vector4d pt = points[i];
                if (pt == pt0)
                {
                    isHistoryPoint = true;
                }
            }
            if (!isHistoryPoint)
            {
                std::unique_lock<std::mutex> pAl_lock(points_and_lines_mutex);
                points.push_back(pt0);
            }

            isHistoryPoint = false;
            for (int i = 0; i < points.size(); ++i)
            {
                Eigen::Vector4d pt = points[i];
                if (pt == pt1)
                {
                    isHistoryPoint = true;
                }
            }
            if (!isHistoryPoint)
            {
                std::unique_lock<std::mutex> pAl_lock(points_and_lines_mutex);
                points.push_back(pt1);
            }

            // pt0 = Twl * pt0;
            // pt1 = Twl * pt1;

            {
                std::unique_lock<std::mutex> pAl_lock(points_and_lines_mutex);
                lines.emplace_back(pt0, pt1);  // lines
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    // create more 3d points, you can comment this code
    int n = points.size();
    for (int j = 0; j < n; ++j)
    {
        Eigen::Vector4d p = points[j] + Eigen::Vector4d(0.5, 0.5, -0.5, 0);
        {
            std::unique_lock<std::mutex> pAl_lock(points_and_lines_mutex);
            points.push_back(p);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // save points
    save_points("all_points.txt", points);
}

void DataGeneration::GenerateImuDataAndNoisedData()
{
    bool is_first_iter = true;

    // create imu data
    // imu pose gyro acc
    for (float t = imu_gen_.param_.t_start; t < imu_gen_.param_.t_end;)
    {
        MotionData data = imu_gen_.MotionModel(t);

        {
            std::unique_lock<std::mutex> i_lock(imu_data_mutex);
            imu_datas.push_back(data);
        }

        // add imu noise
        MotionData noised_imu_data = data;
        imu_gen_.addIMUnoise(noised_imu_data);
        noised_imu_datas.push_back(noised_imu_data);

        t += imu_gen_.param_.imu_timestep;

        if (is_first_iter)
        {
            imu_gen_.init_velocity_ = imu_datas[0].imu_velocity;
            imu_gen_.init_twb_      = imu_datas.at(0).twb;
            imu_gen_.init_Rwb_      = imu_datas.at(0).Rwb;
            is_first_iter           = false;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(imu_gen_.param_.imu_timestep * 1e3)));
    }

    save_Pose("./imu_pose.txt", imu_datas);
    save_Pose("./imu_pose_noise.txt", noised_imu_datas);

}

void DataGeneration::TestImu(const std::string& src, const std::string& dist, std::vector<MotionData>& integral_results)
{
    std::vector<MotionData> imudata;
    LoadPose(src, imudata);

    std::ofstream save_points;
    save_points.open(dist);

    double             dt  = imu_gen_.param_.imu_timestep;
    Eigen::Vector3d    Pwb = imu_gen_.init_twb_;      // position :    from  imu measurements
    Eigen::Quaterniond Qwb(imu_gen_.init_Rwb_);       // quaterniond:  from imu measurements
    Eigen::Vector3d    Vw = imu_gen_.init_velocity_;  // velocity  :   from imu measurements
    Eigen::Vector3d    gw(0, 0, -9.81);      // ENU frame
    Eigen::Vector3d    temp_a;
    Eigen::Vector3d    theta;

    for (int i = 1; i < imudata.size(); ++i)
    {
        MotionData last_imupose = imudata[i - 1];
        MotionData curr_imupose = imudata[i];

        MotionData integral_result;

        // delta_q = [1 , 1/2 * thetax , 1/2 * theta_y, 1/2 * theta_z]
        Eigen::Quaterniond dq;
        Eigen::Vector3d    dtheta_half = (last_imupose.imu_gyro + curr_imupose.imu_gyro) * dt / 4.0;
        // Eigen::Vector3d dtheta_half
        dq.w()                         = 1;
        dq.x()                         = dtheta_half.x();
        dq.y()                         = dtheta_half.y();
        dq.z()                         = dtheta_half.z();
        dq.normalize();

        /// imu 动力学模型 欧拉积分
        // **** ...... ****

        /// 中值积分
        Eigen::Vector3d last_acc_w = Qwb * (last_imupose.imu_acc) + gw;  // aw = Rwb * ( acc_body - acc_bias ) + gw
        Qwb                        = Qwb * dq;
        Eigen::Vector3d curr_acc_w = Qwb * (curr_imupose.imu_acc) + gw;
        Eigen::Vector3d acc_w      = (last_acc_w + curr_acc_w) / 2.0;
        Pwb                        = Pwb + Vw * dt + 0.5 * dt * dt * acc_w;
        Vw                         = Vw + acc_w * dt;

        integral_result.Rwb = Qwb.toRotationMatrix();
        integral_result.twb = Pwb;

        {
            std::unique_lock<std::mutex> e_lock(euler_interg_mutex);
            integral_results.push_back(integral_result);
        }


        //　按着imu postion, imu quaternion , cam postion, cam quaternion 的格式存储，由于没有cam，所以imu存了两次
        save_points << curr_imupose.timestamp << " " << Qwb.w() << " " << Qwb.x() << " " << Qwb.y() << " " << Qwb.z()
                    << " " << Pwb(0) << " " << Pwb(1) << " " << Pwb(2) << " " << Qwb.w() << " " << Qwb.x() << " "
                    << Qwb.y() << " " << Qwb.z() << " " << Pwb(0) << " " << Pwb(1) << " " << Pwb(2) << " " << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(imu_gen_.param_.imu_timestep * 1e3)));
    }

    std::cout << "test　end" << std::endl;
}

void DataGeneration::GenerateCameraData()
{
    // cam pose
    for (float t = imu_gen_.param_.t_start; t < imu_gen_.param_.t_end;)
    {
        MotionData imu = imu_gen_.MotionModel(t);  // imu body frame to world frame motion
        MotionData cam;

        cam.timestamp = imu.timestamp;
        cam.Rwb       = imu.Rwb * imu_gen_.param_.R_bc;   // cam frame in world frame
        cam.twb       = imu.twb + imu.Rwb * imu_gen_.param_.t_bc;  //  Tcw = Twb * Tbc ,  t = Rwb * tbc + twb

        camera_datas.push_back(cam);
        t += imu_gen_.param_.cam_timestep;
    }

    save_Pose("cam_pose.txt", camera_datas);
    save_Pose_asTUM("cam_pose_tum.txt", camera_datas);
}

void DataGeneration::GeneratePointsObs()
{
    for (int n = 0; n < camera_datas.size(); ++n)
    {
        MotionData      data  = camera_datas.at(n);
        Eigen::Matrix4d Twc   = Eigen::Matrix4d::Identity();
        Twc.block(0, 0, 3, 3) = data.Rwb;
        Twc.block(0, 3, 3, 1) = data.twb;

        // 遍历所有的特征点，看哪些特征点在视野里
        std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > points_cam;  // ３维点在当前cam 视野里
        std::vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d> > features_cam;  // 对应的２维图像> 坐标

        for (int i = 0; i < points.size(); ++i)
        {
            Eigen::Vector4d pw  = points[i];           // 最后一位存着feature id
            pw[3]               = 1;                   //改成齐次坐标最后一位
            Eigen::Vector4d pc1 = Twc.inverse() * pw;  // T_wc.inverse() * Pw  -- > point in cam frame

            if (pc1(2) < 0)
                continue;  // z必须大于０,在摄像机坐标系前方

            Eigen::Vector2d obs(pc1(0) / pc1(2), pc1(1) / pc1(2));
            // if( (obs(0)*460 + 255) < params.image_h && ( obs(0) * 460 + 255) > 0 &&
            // (obs(1)*460 + 255) > 0 && ( obs(1)* 460 + 255) < params.image_w )
            {
                points_cam.push_back(points[i]);
                features_cam.push_back(obs);
            }
        }

        if (points.size() != points_cam.size())
        {
            std::cout << "111111111111111111111111111111 " << std::endl;
            std::cout << "camera i : " << n << std::endl;
            std::cout << "points size : " << points.size() << std::endl;
            std::cout << "points_cam size : " << points_cam.size() << std::endl;
            std::cout << "111111111111111111111111111111 " << std::endl;
        }

        // save points
        std::stringstream filename1;
        filename1 << "keyframe/all_points_" << n << ".txt";
        save_features(filename1.str(), points_cam, features_cam);
    }
}

void DataGeneration::GenerateLinesObs()
{
    // lines obs in image
    for (int n = 0; n < camera_datas.size(); ++n)
    {
        MotionData      data  = camera_datas[n];
        Eigen::Matrix4d Twc   = Eigen::Matrix4d::Identity();
        Twc.block(0, 0, 3, 3) = data.Rwb;
        Twc.block(0, 3, 3, 1) = data.twb;

        // 遍历所有的特征点，看哪些特征点在视野里
        // std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > points_cam;
        // ３维点在当前cam视野里
        std::vector<Eigen::Vector4d, Eigen::aligned_allocator<Eigen::Vector4d> > features_cam;  // 对应的２维图像>坐标
        for (int i = 0; i < lines.size(); ++i)
        {
            Line linept = lines[i];

            Eigen::Vector4d pc1 = Twc.inverse() * linept.first;   // T_wc.inverse() * Pw  -- > point in cam frame
            Eigen::Vector4d pc2 = Twc.inverse() * linept.second;  // T_wc.inverse() * Pw  -- > point in cam frame

            if (pc1(2) < 0 || pc2(2) < 0)
            {
                continue;  // z必须大于０,在摄像机坐标系前方
            }

            Eigen::Vector4d obs(pc1(0) / pc1(2), pc1(1) / pc1(2), pc2(0) / pc2(2), pc2(1) / pc2(2));
            // if(obs(0) < params.image_h && obs(0) > 0 && obs(1)> 0 && obs(1) < params.image_w)
            {
                features_cam.push_back(obs);
            }
        }

        if (lines.size() != features_cam.size())
        {
            std::cout << "111111111111111111111111111111 " << std::endl;
            std::cout << "camera i : " << n << std::endl;
            std::cout << "points size : " << lines.size() << std::endl;
            std::cout << "points_cam size : " << features_cam.size() << std::endl;
            std::cout << "111111111111111111111111111111 " << std::endl;
        }

        // save points
        std::stringstream filename1;
        filename1 << "keyframe/all_lines_" << n << ".txt";
        save_lines(filename1.str(), features_cam);
    }
}

