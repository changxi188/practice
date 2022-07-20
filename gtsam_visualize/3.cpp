#include <iostream>

#include <gtsam/geometry/Pose3.h>

using namespace std;

int main()
{
    gtsam::Pose3 pose1, pose2;
    pose1.compose(pose2);
    pose1.localCoordinates(pose2);
}