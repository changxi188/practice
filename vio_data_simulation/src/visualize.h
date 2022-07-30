#pragma once
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include <pangolin/pangolin.h>

#include "common_types.h"

class Visualizer
{
public:
    Visualizer()
    {
        visualize_thread_ = std::thread(&Visualizer::run, this);
    }

    virtual ~Visualizer()
    {
        visualize_thread_.join();
    }

private:
    void run();

    void drawAxis();

    void drawPointsAndLines();

    void drawGTOdometry();

    void drawEulerIntegral();

    void drawEulerIntegralWithNoise();

    void drawMedianIntegral();

    void drawCamera(const MotionData& imu_data);

private:
    std::thread visualize_thread_;
};

