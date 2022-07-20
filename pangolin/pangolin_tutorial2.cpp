#include <pangolin/pangolin.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

void SampleMethod()
{
    std::cout << "You typed ctrl-r or pushed reset" << std::endl;
    // std::cout << "Window width: " << i << std::endl;
}

void PushAButton()
{
    std::cout << "You pushed A button." << std::endl;
}

int main(/*int argc, char* argv[]*/)
{
    // 创建视窗
    pangolin::CreateWindowAndBind("Main", 640, 480);
    // 启动深度测试
    glEnable(GL_DEPTH_TEST);
    // 创建一个摄像机
    pangolin::OpenGlRenderState s_cam(pangolin::ProjectionMatrix(640, 480, 420, 420, 320, 240, 0.1, 1000),
                                      pangolin::ModelViewLookAt(-0, 0.5, -3, 0, 0, 0, pangolin::AxisY));
    // 分割视窗
    const int UI_WIDTH = 300;

    // 右侧用于显示视口
    pangolin::View& d_cam = pangolin::CreateDisplay()
                                .SetBounds(0.0, 1.0, pangolin::Attach::Pix(UI_WIDTH), 1.0, -640.0f / 480.0f)
                                .SetHandler(new pangolin::Handler3D(s_cam));

    pangolin::View& cv_img_1 = pangolin::Display("image_1")
                                   .SetBounds(2 / 3.0f, 1.0f, 0., 1 / 3.0f, 752 / 480.)
                                   // .SetBounds(0., 1 / 3.0f, 2 / 3.0f, 1.0, 752 / 480.)
                                   .SetLock(pangolin::LockLeft, pangolin::LockTop);

    pangolin::View& cv_img_2 = pangolin::Display("image_2")
                                   .SetBounds(0., 1 / 3.0f, 2 / 3.0f, 1.0, 752 / 480.)
                                   .SetLock(pangolin::LockRight, pangolin::LockBottom);

    // 创建glTexture容器用于读取图像
    pangolin::GlTexture imgTexture1(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);
    pangolin::GlTexture imgTexture2(752, 480, GL_RGB, false, 0, GL_BGR, GL_UNSIGNED_BYTE);

    // 左侧用于创建控制面板
    pangolin::CreatePanel("ui").SetBounds(0.0, 0.5, 0.0, pangolin::Attach::Pix(UI_WIDTH));

    // 创建控制面板的控件对象，pangolin中
    pangolin::Var<bool>        A_Button("ui.a_button", false, false);     // 按钮
    pangolin::Var<bool>        A_Checkbox("ui.a_checkbox", false, true);  // 选框
    pangolin::Var<double>      Double_Slider("ui.double_slider", 3, 0, 5);  // double滑条
    pangolin::Var<int>         Int_Slider("ui.int_slider", 2, 0, 5);        // int滑条
    pangolin::Var<std::string> A_string("ui.a_string", "Hello Pangolin");

    pangolin::Var<bool> SAVE_IMG("ui.save_img", false, false);      // 按钮
    pangolin::Var<bool> SAVE_WIN("ui.save_win", false, false);      // 按钮
    pangolin::Var<bool> RECORD_WIN("ui.record_win", false, false);  // 按钮

    pangolin::Var<std::function<void()>> reset("ui.Reset", SampleMethod);  //

    // 绑定键盘快捷键
    // Demonstration of how we can register a keyboard hook to alter a Var
    pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'b', pangolin::SetVarFunctor<double>("ui.a_slider", 3.5));

    // Demonstration of how we can register a keyboard hook to trigger a method
    pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'r', SampleMethod);
    // Default hooks for exiting (Esc) and fullscreen (tab).
    while (!pangolin::ShouldQuit())
    {
        // Clear entire screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 各控件的回调函数
        if (pangolin::Pushed(A_Button))
        {
            PushAButton();
        }

        if (A_Checkbox)
            Int_Slider = Double_Slider;
        // 保存整个win
        if (pangolin::Pushed(SAVE_WIN))
            pangolin::SaveWindowOnRender("window");
        // 保存view
        if (pangolin::Pushed(SAVE_IMG))
            d_cam.SaveOnRender("cube");
        // 录像
        if (pangolin::Pushed(RECORD_WIN))
            pangolin::DisplayBase().RecordOnRender("ffmpeg:[fps=50,bps=8388608,unique_filename]//screencap.avi");
        d_cam.Activate(s_cam);
        // glColor3f(1.0,0.0,1.0);
        pangolin::glDrawColouredCube();

        // 从文件读取图像
        cv::Mat img1 = cv::imread("./1.png");
        cv::Mat img2 = cv::imread("./2.png");
        // 向GPU装载图像
        imgTexture1.Upload(img1.data, GL_BGR, GL_UNSIGNED_BYTE);
        imgTexture2.Upload(img2.data, GL_BGR, GL_UNSIGNED_BYTE);
        // 显示图像
        cv_img_1.Activate();
        glColor3f(1.0f, 1.0f, 1.0f);  // 设置默认背景色，对于显示图片来说，不设置也没关系
        imgTexture1.RenderToViewportFlipY();  // 需要反转Y轴，否则输出是倒着的

        cv_img_2.Activate();
        glColor3f(1.0f, 1.0f, 1.0f);  // 设置默认背景色，对于显示图片来说，不设置也没关系
        imgTexture2.RenderToViewportFlipY();

        // Swap frames and Process Events
        pangolin::FinishFrame();
    }

    return 0;
}
