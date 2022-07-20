#ifndef __FRAME_H__
#define __FRAME_H__
#include "common_include.h"
class Frame{
public:
    typedef std::shared_ptr<Frame> Ptr;
    Frame();



private:
    unsigned long id_;
    cv::Mat color_image_, depth_image_;

};


#endif