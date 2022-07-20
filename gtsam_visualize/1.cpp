#include <iostream>

#include <gtsam/geometry/Point2.h>
#include <gtsam/geometry/Pose2.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/slam/PriorFactor.h>

class UnaryFactor : public gtsam::NoiseModelFactor1<gtsam::Pose2>
{
public:
    UnaryFactor(gtsam::Key j, double x, double y, const gtsam::SharedNoiseModel& model)
      : gtsam::NoiseModelFactor1<gtsam::Pose2>(model, j), mx_(x), my_(y)
    {
    }

    gtsam::Vector evaluateError(const gtsam::Pose2& q, boost::optional<gtsam::Matrix&> H = boost::none) const
    {
        const gtsam::Vector2 error = gtsam::Vector2(q.x() - mx_, q.y() - my_);

        if (H)
        {
            (*H) = (gtsam::Matrix(2, 3) << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0).finished();
        }

        return error;
    }

private:
    double mx_, my_;
};

int main()
{
    gtsam::NonlinearFactorGraph             graph;
    gtsam::Pose2                            prior_mean(0.0, 0.0, 0.0);
    gtsam::noiseModel::Diagonal::shared_ptr prior_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(10.0, 3.0, 1));

    // graph.add(gtsam::PriorFactor<gtsam::Pose2>(1, prior_mean, prior_noise));

    gtsam::Pose2                            odometry(2.0, 0.0, 0.0);
    gtsam::noiseModel::Diagonal::shared_ptr odometry_noise =
        gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector3(0.2, 0.2, 0.1));

    graph.add(gtsam::BetweenFactor<gtsam::Pose2>(1, 2, odometry, odometry_noise));
    graph.add(gtsam::BetweenFactor<gtsam::Pose2>(2, 3, odometry, odometry_noise));
    // gtsam::

    graph.print();

    gtsam::Values initial;
    initial.insert(1, gtsam::Pose2(0.5, 0.0, 0.2));
    initial.insert(2, gtsam::Pose2(2.3, 0.1, -0.2));
    initial.insert(3, gtsam::Pose2(4.1, 0.1, 0.1));

    gtsam::noiseModel::Diagonal::shared_ptr unary_noise = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector2(0.1, 0.1));

    graph.add(boost::make_shared<UnaryFactor>(1, 0.0, 0.0, unary_noise));
    graph.add(boost::make_shared<UnaryFactor>(2, 2.0, 0.0, unary_noise));
    graph.add(boost::make_shared<UnaryFactor>(3, 4.0, 0.0, unary_noise));

    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initial);
    gtsam::Values                      result = optimizer.optimize();

    initial.print();
    result.print();
    gtsam::Marginals marginals(graph, result);
    std::cout << "x1 covariance : \n " << marginals.marginalCovariance(1) << std::endl;
    std::cout << "x2 covariance : \n " << marginals.marginalCovariance(2) << std::endl;
    std::cout << "x3 covariance : \n " << marginals.marginalCovariance(3) << std::endl;
}