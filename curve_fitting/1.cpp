#include <chrono>
#include <iostream>
#include <random>
#include <vector>

#include <pcl/visualization/pcl_plotter.h>
#include <Eigen/Core>
#include <opencv2/opencv.hpp>

#include <gtsam/base/Matrix.h>
#include <gtsam/base/Vector.h>
#include <gtsam/base/types.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/linear/NoiseModel.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/Values.h>

#include "g2o_type.h"

using namespace std;

class UnaryFactor : public gtsam::NoiseModelFactor1<gtsam::Vector4>
{
public:
    UnaryFactor(gtsam::Key j, double x, double y, const gtsam::SharedNoiseModel& model)
      : gtsam::NoiseModelFactor1<gtsam::Vector4>(model, j), mx_(x), my_(y)
    {
    }

    gtsam::Vector evaluateError(const gtsam::Vector4& q, const boost::optional<gtsam::Matrix&> H = boost::none) const
    {
        const gtsam::Vector1 error =
            gtsam::Vector1(my_ - q(0) - q(1) * mx_ - q(2) * mx_ * mx_ - q(3) * mx_ * mx_ * mx_);

        if (H)
        {
            (*H) = (gtsam::Matrix(1, 4) << -1, -mx_, -mx_ * mx_, -mx_ * mx_ * mx_).finished();
        }

        return error;
    }

private:
    double mx_, my_;
};

void PclDrawer(const std::vector<double>& xs, const std::vector<double>& ys, const Eigen::Vector4d& lls_coeff,
               const Eigen::Vector4d& gtsam_coeff)
{
    // construct raw dataset
    std::vector<std::pair<double, double>> data;
    for (size_t i = 0; i < xs.size(); ++i)
    {
        data.push_back(std::make_pair(xs[i], ys[i]));
    }

    // construct polynomial cofficients
    std::vector<double> gt_func(4, 0);
    for (size_t i = 0; i < 4; ++i)
    {
        gt_func[i] = i + 1;
    }

    // construct polynomial cofficients
    std::vector<double> lls_func(4, 0);
    for (size_t i = 0; i < 4; ++i)
    {
        lls_func[i] = lls_coeff[i];
    }

    // construct polynomial cofficients
    std::vector<double> gtsam_func(4, 0);
    for (size_t i = 0; i < 4; ++i)
    {
        gtsam_func[i] = gtsam_coeff[i];
    }

    pcl::visualization::PCLPlotter* plotter = new pcl::visualization::PCLPlotter();

    plotter->addPlotData(gt_func, xs.front(), xs.back(), "gt");

    plotter->addPlotData(lls_func, xs.front(), xs.back(), "lls_est");

    plotter->addPlotData(gtsam_func, xs.front(), xs.back(), "gtsam_est");

    plotter->addPlotData(data, "raw_data");

    plotter->setShowLegend(true);  // show legends

    plotter->plot();
}

void DatasetGenerateWithNose(std::vector<double>& xs, std::vector<double>& ys)
{
    double w_sigma = 1;
    double a_0 = 1.0, a_1 = 2.0, a_2 = 3.0, a_3 = 4.0;

    std::default_random_engine       generator;
    std::normal_distribution<double> noise(0, w_sigma);

    for (int i = 0; i < 100; ++i)
    {
        double noise_result = noise(generator);
        double x            = i / 100.0;
        // double y            = std::exp(a * x * x + b * x + c) + noise_result;
        double y = a_0 + a_1 * x + a_2 * x * x + a_3 * x * x * x + noise_result;
        xs.push_back(x);
        ys.push_back(y);
    }
}

Eigen::Vector4d SolveLinearLeastSquare(const std::vector<double>& xs, const std::vector<double>& ys)
{
    std::chrono::steady_clock::time_point t1   = std::chrono::steady_clock::now();
    const int                        rows = xs.size();
    Eigen::MatrixXd                  X(rows, 4);
    Eigen::MatrixXd                  Y(rows, 1);
    std::cout << "xs.size : " << xs.size() << std::endl;
    std::cout << "X : " << X.rows() << " x " << X.cols() << std::endl;

    for (size_t i = 0; i < xs.size(); ++i)
    {
        X(i, 0) = 1;
        X(i, 1) = xs[i];
        X(i, 2) = xs[i] * xs[i];
        X(i, 3) = xs[i] * xs[i] * xs[i];

        Y(i, 0) = ys[i];
    }

    Eigen::Matrix4d left  = X.transpose() * X;
    Eigen::Vector4d right = X.transpose() * Y;

    // solve XA = Y
    Eigen::Vector4d A = left.ldlt().solve(right);
    // Eigen::Vector4d A = left.inverse() * right;

    chrono::steady_clock::time_point t2        = chrono::steady_clock::now();
    chrono::duration<double>         time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    std::cout << "linear cost : " << time_used.count() << ", A : " << A.transpose() << std::endl;
    return A;
}

const Eigen::Vector4d GtsamSolveLinearSquare(const std::vector<double>& xs, const std::vector<double>& ys)
{
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    gtsam::NonlinearFactorGraph graph;

    gtsam::Values initial;

    gtsam::Key B1 = gtsam::Symbol('B', 1);

    initial.insert(B1, gtsam::Vector4(0, 0, 0, 0));

    gtsam::noiseModel::Diagonal::shared_ptr unary_noise = gtsam::noiseModel::Diagonal::Sigmas(gtsam::Vector1(1));

    for (size_t i = 0; i < xs.size(); ++i)
    {
        graph.add(boost::make_shared<UnaryFactor>(B1, xs[i], ys[i], unary_noise));
    }

    gtsam::LevenbergMarquardtOptimizer optimizer(graph, initial);

    gtsam::Values result = optimizer.optimize();

    chrono::steady_clock::time_point t2        = chrono::steady_clock::now();
    chrono::duration<double>         time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    const auto A = result.at(B1).cast<gtsam::Vector4>();

    std::cout << "gtsam cost : " << time_used.count() << ", A : " << A.transpose() << std::endl;

    return A;
}

const Eigen::Vector4d G2oSolveLinearSquare(const std::vector<double>& xs, const std::vector<double>& ys)
{
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();

    typedef g2o::BlockSolver<g2o::BlockSolverTraits<4, 1>> BlockSolverType;

    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

    auto solver = new g2o::OptimizationAlgorithmLevenberg(
        g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));

    g2o::SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);
    optimizer.setVerbose(false);

    CurveFittingVertex* v = new CurveFittingVertex();
    v->setEstimate(Eigen::Vector4d(0, 0, 0, 0));
    v->setId(0);
    optimizer.addVertex(v);

    for (int i = 0; i < xs.size(); i++)
    {
        CurveFittingEdge* edge = new CurveFittingEdge(xs[i], ys[i]);
        edge->setId(i);

        edge->setVertex(0, v);

        // 观测数值
        edge->setMeasurement(ys[i]);
        edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (1 * 1));
        optimizer.addEdge(edge);
    }

    // 执行优化
    optimizer.initializeOptimization();
    optimizer.optimize(10);

    chrono::steady_clock::time_point t2        = chrono::steady_clock::now();
    chrono::duration<double>         time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    // 输出优化量
    Eigen::Vector4d A = v->estimate();
    std::cout << "g2o cost : " << time_used.count() << ", A : " << A.transpose() << std::endl;
}

int main()
{
    std::vector<double> xs, ys;

    DatasetGenerateWithNose(xs, ys);

    const Eigen::Vector4d lls_coeff = SolveLinearLeastSquare(xs, ys);

    const Eigen::Vector4d gtsam_coeff = GtsamSolveLinearSquare(xs, ys);

    const Eigen::Vector4d g2o_coeff = G2oSolveLinearSquare(xs, ys);

    PclDrawer(xs, ys, lls_coeff, gtsam_coeff);

    return 0;
}
