#ifndef __CURVE_FITTING_G2O_H__
#define __CURVE_FITTING_G2O_H__
#include "common_include.h"
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/block_solver.h>
#include <g2o/solvers/dense/linear_solver_dense.h>


class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    virtual void setToOriginImpl() override {
        _estimate << 0, 0, 0;
    }

    virtual void oplusImpl(const double *update) override {
        _estimate += Eigen::Vector3d(update);
    }

    virtual bool read(std::istream& in) override {
        return true;
    }

    virtual bool write(std::ostream& out) const {
        return true;
    }

};

class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW
    CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x) {}

    virtual void computeError() override {
        const CurveFittingVertex *v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        _error(0, 0) = _measurement - std::exp(abc(0, 0) * _x * _x + abc(1, 0) * _x + abc(2, 0));
    }

    virtual void linearizeOplus() override {
        const CurveFittingVertex *v = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        double y = std::exp(abc[0] * _x * _x + abc[1] * _x + abc[2]);
        _jacobianOplusXi[0] = -_x * _x * y;
        _jacobianOplusXi[1] = -_x * y;
        _jacobianOplusXi[2] = -y;
    }

    virtual bool read(std::istream& in){
        return true;
    }

    virtual bool write(std::ostream& out) const {
        return true;
    }

private:
    double _x;

};


class CurverFitting_G2O{
public:
    typedef std::shared_ptr<CurverFitting_G2O> Ptr;
    CurverFitting_G2O(){
        makeDataset();
    };

    CurverFitting_G2O(double a_e, double b_e, double c_e)
        : a_e_(a_e), b_e_(b_e), c_e_(c_e) {
        makeDataset();
    };
    // 构建数据集
    void makeDataset();

    // 构建优化
    void startOptimize();


private:
    double a_t_ = 1, b_t_ = 2, c_t_ = 3;
    double a_e_ = 3, b_e_ = 5, c_e_ = 2;
    int num_dataset_ = 100, iterations_ = 10;
    std::vector<double> xs_, ys_;
    double w_sigma_ = 1;
    cv::RNG rng;


};

#endif