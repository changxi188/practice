//
// Created by mr on 2020/7/16.
//

#ifndef GAUSSNEWTON_G2O_TYPE_H
#define GAUSSNEWTON_G2O_TYPE_H
#pragma once

#include <g2o/core/g2o_core_api.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

#include <iostream>

// 模板参数 : 优化变量维度, 数据类型
class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d>{

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    // 重置
    virtual void setToOriginImpl() override {
        _estimate << 0, 0, 0;
    }

    // 更新
    virtual void oplusImpl(const double *update) override {
        _estimate += Eigen::Vector3d(update);
    }

    // 存盘和读盘 : 留空
    virtual bool read(std::istream &in){}
    virtual bool write(std::ostream &out) const{}

};
// 模板参数 : 观测值维度, 类型, 连接顶点类型
class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>{

public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    CurveFittingEdge(double x) : BaseUnaryEdge(), _x(x) {}

    // 计算曲线模型误差
    virtual void computeError() override {
        const CurveFittingVertex *v = static_cast<const CurveFittingVertex *>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        _error(0, 0) = _measurement - std::exp(abc(0, 0) * _x * _x + abc(1, 0) * _x + abc(2, 0));
    }

    // 计算雅可比矩阵
    virtual void linearizeOplus() override {
        const CurveFittingVertex *v = static_cast<const CurveFittingVertex *>(_vertices[0]);
        const Eigen::Vector3d abc = v->estimate();
        double y = exp(abc[0] * _x * _x - abc[1] * _x + abc[2]);
        _jacobianOplusXi[0] = -_x * _x * y;
        _jacobianOplusXi[1] = _x * y;
        _jacobianOplusXi[2] = -y;
    }

    virtual bool read(std::istream &in){}
    virtual bool write(std::ostream &out) const {}


public:

    // x, y 为测量值
    double _x;

};

#endif //GAUSSNEWTON_G2O_TYPE_H
