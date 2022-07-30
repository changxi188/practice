#include "common_types.h"

Param params;

std::mutex points_and_lines_mutex;
Points     points;
Lines      lines;

std::mutex              imu_data_mutex;
std::vector<MotionData> imu_datas;
std::vector<MotionData> noised_imu_datas;

std::mutex euler_interg_mutex;
std::vector<MotionData> euler_integral_results;
std::vector<MotionData> euler_integral_noised_results;

std::mutex              camera_data_mutex;
std::vector<MotionData> camera_datas;
