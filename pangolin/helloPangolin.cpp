#include <iostream>
#include <pangolin/pangolin.h>

int main(int argc, char **argv)
{
    //创建一个窗口
    pangolin::CreateWindowAndBind("Main",640,480);
    //启动深度测试
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 320, 0.2, 100),
                                      //对应的是gluLookAt,摄像机位置,参考点位置,up vector(上向量)
                                      pangolin::ModelViewLookAt(2, 0, 2, 0, 0, 0, pangolin::AxisNegY));

    // Create Interactive View in window
    pangolin::Handler3D handler(s_cam);
    //setBounds 跟opengl的viewport 有关
    //看SimpleDisplay中边界的设置就知道
    pangolin::View &d_cam = pangolin::CreateDisplay().SetBounds(0.0,1.0,0.0,1.0,-640.0f/480.0f)
                            .SetHandler(&handler);

    while(!pangolin::ShouldQuit())
    {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        d_cam.Activate(s_cam);

        // Render OpenGL Cube
        // pangolin::glDrawColouredCube();
        //坐标轴的创建
        pangolin::glDrawAxis(3);

        //点的创建
		/*
        glPointSize(10.0f);
        glBegin(GL_POINTS);
        glColor3f(1.0,1.0,1.0);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(1,0,0);
        glVertex3f(0,2,0);
        glEnd();
		*/

        //把下面的点都做一次旋转变换
        glPushMatrix();
        //col major
        std::vector<GLfloat> Twc = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
        glMultMatrixf(Twc.data());

        //直线的创建
        const float w = 2;
        const float h = w*0.75;
        const float z = w*0.6;
        glLineWidth(2);
        glColor3f(1.0,0,0);
        glBegin(GL_LINES);

        glVertex3f(0,0,0);
        glVertex3f(w,h,z);
        glVertex3f(0,0,0);
        glVertex3f(w,-h,z);
        glVertex3f(0,0,0);
        glVertex3f(-w,-h,z);
        glVertex3f(0,0,0);
        glVertex3f(-w,h,z);
        glVertex3f(w,h,z);
        glVertex3f(-w,h,z);
        glVertex3f(-w,h,z);
        glVertex3f(-w,-h,z);
        glVertex3f(-w,-h,z);
        glVertex3f(w,-h,z);
        glVertex3f(w,-h,z);
        glVertex3f(w,h,z);
        glEnd();

        glPopMatrix();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }

    return 0;

}
