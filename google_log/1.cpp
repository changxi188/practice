#include <glog/logging.h>
#include <iostream>
#include <memory>

using namespace std;

void SignalHandle(const char* data, int size)
{
    LOG(ERROR) << std::string(data, size);
}

void cored_dumpedd()
{
    std::shared_ptr<int> a;
    {
        // std::runtime_error("1111");
        std::cout << *a << std::endl;
    }
}

int main(int argc, char** argv)
{
    google::InitGoogleLogging(argv[0]);

    FLAGS_colorlogtostderr = true;
    FLAGS_alsologtostderr  = true;
    FLAGS_minloglevel      = 0;

    google::SetLogDestination(google::INFO, "log/holo_vslam_app.log");

    google::InstallFailureSignalHandler();

    google::InstallFailureWriter(&SignalHandle);

    for (size_t i = 0; i < 10; ++i)
    {
        LOG(INFO) << " hello, glog ";
    }

    LOG(ERROR) << " ssss ";

    cored_dumpedd();
    google::ShutdownGoogleLogging();
    return 0;
}
