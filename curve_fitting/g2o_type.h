#pragma once

#include <Eigen/src/Core/util/Constants.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/g2o_core_api.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/solvers/dense/linear_solver_dense.h>


// 模板参数 : 优化变量维度, 数据类型
class CurveFittingVertex : public g2o::BaseVertex<4, Eigen::Vector4d>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    // 重置
    virtual void setToOriginImpl() override
    {
        _estimate << 0, 0, 0, 0;
    }

    // 更新
    virtual void oplusImpl(const double* update) override
    {
        _estimate += Eigen::Vector4d(update);
    }

    // 存盘和读盘 : 留空
    virtual bool read(std::istream& in)
    {
    }
    virtual bool write(std::ostream& out) const
    {
    }
};

// 模板参数 : 观测值维度, 类型, 连接顶点类型
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>
{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    CurveFittingEdge(double x, double y) : BaseUnaryEdge(), _x(x), _y(y)
    {
    }

    // 计算曲线模型误差
    virtual void computeError() override
    {
        const CurveFittingVertex* v   = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector4d     q   = v->estimate();
        _error(0, 0)                  = _measurement - q(0) - q(1) * _x - q(2) * _x * _x - q(3) * _x * _x * _x;
    }

    // 计算雅可比矩阵
    virtual void linearizeOplus() override
    {
        const CurveFittingVertex* v   = static_cast<const CurveFittingVertex*>(_vertices[0]);
        const Eigen::Vector4d     q   = v->estimate();
        _jacobianOplusXi[0]           = -1;
        _jacobianOplusXi[1]           = -_x;
        _jacobianOplusXi[2]           = -_x * _x;
        _jacobianOplusXi[3]           = -_x * _x * _x;
    }

    virtual bool read(std::istream& in)
    {
    }
    virtual bool write(std::ostream& out) const
    {
    }

public:
    // x, y 为测量值
    double _x;
    double _y;
};

