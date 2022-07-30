#pragma once
#include <vector>
#include "../src/imu.h"
#include "../src/utilities.h"
#include "common_types.h"

class DataGeneration
{
public:
    DataGeneration(const IMU& imu_gen) : imu_gen_(imu_gen)
    {
    }

    void GeneratePointsAndLines();

    void GenerateImuDataAndNoisedData();

    void GenerateCameraData();

    void TestImu(const std::string& src, const std::string& dist, std::vector<MotionData>& integral_results);

    void GeneratePointsObs();

    void GenerateLinesObs();

    ~DataGeneration()
    {
    }

private:
    IMU imu_gen_;
};
