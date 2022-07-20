#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include "common_include.h"
#include "vertex.h"
#include "edge.h"

class Problem{
public:
    enum class ProblemType{
        SLAM_PROBLEM,
        GENERIC_PROBLEM
    };

private:
    ProblemType problemtype_;

    Eigen::Matrix<double, 3, 3> A;


};


#endif