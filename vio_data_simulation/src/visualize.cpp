#include "visualize.h"
#include <eigen3/Eigen/src/Core/Matrix.h>
#include <pangolin/display/display.h>
#include <pangolin/display/opengl_render_state.h>
#include <algorithm>
#include <chrono>
#include <locale>
#include <mutex>
#include <numeric>
#include <vector>

void Visualizer::run()
{
    pangolin::CreateWindowAndBind("Main", 640, 480);
    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 320, 0.2, 100),
                                      //对应的是gluLookAt,摄像机位置,参考点位置,up vector(上向量)
                                      pangolin::ModelViewLookAt(20, 0, 30, 0, 0, 0, pangolin::AxisZ));

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    // setBounds 跟opengl的viewport 有关
    //看SimpleDisplay中边界的设置就知道
    pangolin::View& d_cam =
        pangolin::CreateDisplay().SetBounds(0.0, 1.0, 0.0, 1.0, -640.0f / 480.0f).SetHandler(&handler);

    while (!pangolin::ShouldQuit())
    {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        drawAxis();

        drawPointsAndLines();

        drawGTOdometry();

        drawEulerIntegral();

        drawEulerIntegralWithNoise();

        drawMedianIntegral();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }
}

void Visualizer::drawEulerIntegralWithNoise()
{
    std::unique_lock<std::mutex> e_lock(euler_interg_mutex);
    for (size_t i = 1; i < euler_integral_noised_results.size(); ++i)
    {
        MotionData      imu_data_1 = euler_integral_noised_results.at(i - 1);
        Eigen::Vector3d twb_1      = imu_data_1.twb;
        MotionData      imu_data_2 = euler_integral_noised_results.at(i);
        Eigen::Vector3d twb_2      = imu_data_2.twb;

        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(0.6, 0.2, 0.1);
        glVertex3d(twb_1.x(), twb_1.y(), twb_1.z());
        glVertex3d(twb_2.x(), twb_2.y(), twb_2.z());
        glEnd();
    }

    if (!euler_integral_noised_results.empty())
    {
        const auto imu_data = euler_integral_noised_results.back();
        drawCamera(imu_data);
    }
}

void Visualizer::drawEulerIntegral()
{
    std::unique_lock<std::mutex> e_lock(euler_interg_mutex);
    for (size_t i = 1; i < euler_integral_results.size(); ++i)
    {
        MotionData      imu_data_1 = euler_integral_results.at(i - 1);
        Eigen::Vector3d twb_1      = imu_data_1.twb;
        MotionData      imu_data_2 = euler_integral_results.at(i);
        Eigen::Vector3d twb_2      = imu_data_2.twb;

        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(0.0, 0.8, 0);
        glVertex3d(twb_1.x(), twb_1.y(), twb_1.z());
        glVertex3d(twb_2.x(), twb_2.y(), twb_2.z());
        glEnd();
    }

    if (!euler_integral_results.empty())
    {
        const auto imu_data = euler_integral_results.back();
        drawCamera(imu_data);
    }
}

void Visualizer::drawMedianIntegral()
{
}

void Visualizer::drawGTOdometry()
{

    // for (const auto imu_data : imu_datas)
    std::unique_lock<std::mutex> i_lock(imu_data_mutex);
    for (size_t i = 1; i < imu_datas.size(); ++i)
    {
        MotionData      imu_data_1 = imu_datas.at(i - 1);
        Eigen::Vector3d twb_1      = imu_data_1.twb;
        MotionData      imu_data_2 = imu_datas.at(i);
        Eigen::Vector3d twb_2      = imu_data_2.twb;

        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3f(1.0, 0, 0);
        glVertex3d(twb_1.x(), twb_1.y(), twb_1.z());
        glVertex3d(twb_2.x(), twb_2.y(), twb_2.z());
        glEnd();
    }

    if (!imu_datas.empty())
    {
        const auto imu_data = imu_datas.back();
        drawCamera(imu_data);
    }
}

void Visualizer::drawPointsAndLines()
{
    std::unique_lock<std::mutex> pl_lock(points_and_lines_mutex);

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0, 0.8, 0.6);

    for (const auto point : points)
    {
        glVertex3f(point(0), point(1), point(2));
    }
    glEnd();

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.8, 0.6, 0);
    for (const auto line : lines)
    {
        glVertex3f(line.first(0), line.first(1), line.first(2));
        glVertex3f(line.second(0), line.second(1), line.second(2));
    }
    glEnd();
}

void Visualizer::drawAxis()
{
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(1.0, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(2, 0, 0);

    glColor3f(0, 1.0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 2, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 2);

    glEnd();
}

void Visualizer::drawCamera(const MotionData& imu_data)
{
    Eigen::Matrix3d Rwb = imu_data.Rwb * params.R_bc;
    Eigen::Vector3d twb = imu_data.twb + Rwb * params.t_bc;
    /*
    cam.Rwb             = imu.Rwb * params.R_bc;            // cam frame in world frame
    cam.twb             = imu.twb + imu.Rwb * params.t_bc;  //  Tcw = Twb * Tbc ,  t = Rwb * tbc + twb
    */

    glPushMatrix();
    std::vector<GLdouble> Twb = {Rwb(0, 0), Rwb(1, 0), Rwb(2, 0), 0., Rwb(0, 1), Rwb(1, 1), Rwb(2, 1), 0.,
                                 Rwb(0, 2), Rwb(1, 2), Rwb(2, 2), 0., twb.x(),   twb.y(),   twb.z(),   1.};
    glMultMatrixd(Twb.data());

    const float w = 2;
    const float h = w * 0.75;
    const float z = w * 0.6;

    glLineWidth(2);

    glBegin(GL_LINES);

    glColor3f(0.0f, 1.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(w, h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(w, -h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(-w, -h, z);
    glVertex3f(0, 0, 0);
    glVertex3f(-w, h, z);
    glVertex3f(w, h, z);
    glVertex3f(w, -h, z);
    glVertex3f(-w, h, z);
    glVertex3f(-w, -h, z);
    glVertex3f(-w, h, z);
    glVertex3f(w, h, z);
    glVertex3f(-w, -h, z);
    glVertex3f(w, -h, z);

    glEnd();

    glPopMatrix();
}

