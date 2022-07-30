#pragma once

#include <mutex>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>

#include "param.h"

using Point  = Eigen::Vector4d;
using Points = std::vector<Point, Eigen::aligned_allocator<Point> >;
using Line   = std::pair<Eigen::Vector4d, Eigen::Vector4d>;
using Lines  = std::vector<Line, Eigen::aligned_allocator<Line> >;

struct MotionData
{
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    double          timestamp;
    Eigen::Matrix3d Rwb;
    Eigen::Vector3d twb;
    Eigen::Vector3d imu_acc;
    Eigen::Vector3d imu_gyro;

    Eigen::Vector3d imu_gyro_bias;
    Eigen::Vector3d imu_acc_bias;

    Eigen::Vector3d imu_velocity;
};

extern Param      params;
extern std::mutex points_and_lines_mutex;
extern Points     points;
extern Lines      lines;

extern std::mutex       imu_data_mutex;
extern std::vector<MotionData> imu_datas;
extern std::vector<MotionData> noised_imu_datas;

extern std::mutex euler_interg_mutex;
extern std::vector<MotionData> euler_integral_results;
extern std::vector<MotionData> euler_integral_noised_results;

extern std::mutex              camera_data_mutex;
extern std::vector<MotionData> camera_datas;

