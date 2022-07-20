#include "curve_fitting_g2o.h"

void CurverFitting_G2O::makeDataset() {
    for(int i = 0; i < num_dataset_; ++i){
        double x = i / 100.;
        xs_.push_back(x);
        ys_.push_back(std::exp(x * x * a_t_ + x * b_t_ + c_t_) + rng.gaussian(w_sigma_ * w_sigma_));
    }
}

void CurverFitting_G2O::startOptimize() {
    // 块求解器类型
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
    // 线性求解器类型
    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

    // 设置非线性优化方法
    auto solver = new g2o::OptimizationAlgorithmLevenberg(
            g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));

    // 图模型
    g2o::SparseOptimizer optimizer;
    // 对图模型添加非线性优化方法
    optimizer.setAlgorithm(solver);
    // 显示详细输出信息
    optimizer.setVerbose(true);

    CurveFittingVertex* v = new CurveFittingVertex();
    v->setId(0);
    v->setEstimate(Eigen::Vector3d(a_e_, b_e_, c_e_));
    optimizer.addVertex(v);

    for (int i = 0; i < num_dataset_; ++i){
        CurveFittingEdge* e = new CurveFittingEdge(xs_[i]);
        e->setId(i);
        e->setVertex(0, v);
        e->setMeasurement(ys_[i]);
        e->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (w_sigma_ * w_sigma_));
        optimizer.addEdge(e);
    }

    optimizer.initializeOptimization();
    optimizer.optimize(iterations_);

    Eigen::Vector3d v_estimate = v->estimate();
    a_e_ = v_estimate[0];
    b_e_ = v_estimate[1];
    c_e_ = v_estimate[2];
    std::cout << "g2o over : " << std::endl;
    std::cout << "a_e : " << a_e_ << ", b_e_ : " << b_e_ << ", c_e : " << c_e_ << std::endl;
    std::cout << v_estimate.transpose() << std::endl;


}