#include <iostream>
#include <thread>
#include <glog/logging.h>


using namespace std;

void th1(){
    
    while(true){
    
        LOG(INFO) << "sub thread1";
        sleep(1);
    }
}

void th2(){
    std::shared_ptr<int> a;

    while(true){
        LOG(WARNING) << "sub thread2";
        sleep(1);
        std::cout << *a << std::endl;
    }
}


int main(int argc, char* argv[]){

    std::string log_file("./a.log");
	google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::INFO, log_file.c_str());

    FLAGS_alsologtostderr = 1;
    FLAGS_minloglevel = 0;
    FLAGS_colorlogtostderr = true;
    LOG(INFO) << "test glog" << 1;


    std::string holo_root = std::getenv("HOLO_ROOT");
    std::cout << "holo_root : " << holo_root << std::endl;

    thread t1(th1);
    thread t2(th2);

    t1.join();
    t2.join();


	return 0;

}
