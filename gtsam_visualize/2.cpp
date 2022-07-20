#include <iostream>

#include <gtsam/geometry/Pose2.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>
#include <gtsam/slam/BearingRangeFactor.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

using namespace std;

using gtsam::symbol_shorthand::L;
using gtsam::symbol_shorthand::X;

int main()
{
    gtsam::Key L1 = gtsam::Symbol('L', 1);
    gtsam::Key L2 = gtsam::Symbol('L', 2);

    gtsam::Key X1 = gtsam::Symbol('x', 1);
    gtsam::Key X2 = gtsam::Symbol('x', 2);
    gtsam::Key X3 = gtsam::Symbol('x', 3);

    // construct graph
    gtsam::NonlinearFactorGraph             graph;
    gtsam::Pose2                            prior_mean = gtsam::Pose2(0, 0, 0);
    gtsam::noiseModel::Diagonal::shared_ptr prior_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(0.5, 0.1, 0.5));
    graph.add(gtsam::PriorFactor<gtsam::Pose2>(X1, prior_mean, prior_noise));

    gtsam::Pose2                            odometry_measure = gtsam::Pose2(2.0, 0.0, 0.0);
    gtsam::noiseModel::Diagonal::shared_ptr odometry_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(0.2, 0.2, 0.1));
    graph.add(gtsam::BetweenFactor<gtsam::Pose2>(X1, X2, odometry_measure, odometry_noise));
    graph.add(gtsam::BetweenFactor<gtsam::Pose2>(X2, X3, odometry_measure, odometry_noise));

    double                                  degree   = M_PI / 180;
    gtsam::noiseModel::Diagonal::shared_ptr br_noise = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(0.2, 0.2));

    // construct values
    gtsam::Values initial_value;
    initial_value.insert(X1, gtsam::Pose2(0.5, 0.2, 0.1));
    initial_value.insert(X2, gtsam::Pose2(2.5, 0.2, -0.1));
    initial_value.insert(X3, gtsam::Pose2(3.5, -0.2, 0.3));

    // construct optimizer and do optimize
    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initial_value);
    gtsam::Values                      result = optimizer.optimize();

    result.print();

    return 0;
}