//
// Created by hyj on 18-1-19.
//

#ifndef IMUSIMWITHPOINTLINE_IMU_H
#define IMUSIMWITHPOINTLINE_IMU_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Geometry>
#include <iostream>
#include "common_types.h"
#include "param.h"

// euler2Rotation:   body frame to interitail frame
Eigen::Matrix3d euler2Rotation( Eigen::Vector3d  eulerAngles);
Eigen::Matrix3d eulerRates2bodyRates(Eigen::Vector3d eulerAngles);


class IMU
{
public:
    IMU(Param p);
    MotionData MotionModel(double t);

    void addIMUnoise(MotionData& data);

public:
    Eigen::Vector3d init_velocity_;
    Eigen::Vector3d init_twb_;
    Eigen::Matrix3d init_Rwb_;

    Param param_;

private:

    Eigen::Vector3d gyro_bias_;
    Eigen::Vector3d acc_bias_;


};

#endif //IMUSIMWITHPOINTLINE_IMU_H
