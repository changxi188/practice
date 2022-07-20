//
// Created by mr on 2020/7/16.
//

#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>

#include "g2o_type.h"

using namespace std;

using namespace Eigen;

/*
 *  c++ 函数前面和后面 使用const 的作用：
 *
 *  前面使用const 表示返回值为const
 *
 *  后面加 const表示函数不可以修改class的成员
 */
int main(){

    double ar = 1.0, br = 2.0, cr = 3.0;
    double ae = 3.0, be = 3.0, ce = 1.0;
    int N =100, iteration = 100;
    double w_sigma = 1.0;
    double inv_w_sigma = 1.0 / w_sigma;
    cv::RNG rng;
    vector<double> x_data, y_data;
    for (int i = 0; i < N; ++i)
	{
        double x = i / 100.0;
        x_data.push_back(i);
        y_data.push_back(exp(ar * i * i + br * i + cr) + rng.gaussian(w_sigma * w_sigma));
    }

    // 构建图优化, 先设定g2o

    // 每个误差项优化变量维度为3, 误差维度为1
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;

    // 线性求解器类型
    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

    // 梯度下降方法, LM, gaussan-newton, DogLeg
    auto solver = new g2o::OptimizationAlgorithmLevenberg(g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));

    // 图模型
    g2o::SparseOptimizer optimizer;

    // 设置求解器
    optimizer.setAlgorithm(solver);

    // 打开调试输出
    optimizer.setVerbose(true);


    // 向图中增加节点
    CurveFittingVertex *v = new CurveFittingVertex();
    v->setEstimate(Vector3d(ae, be, ce));
    v->setId(0);
    optimizer.addVertex(v);


    // 向图中添加节点
    for (int i = 0; i < N; i++){
        CurveFittingEdge *edge = new CurveFittingEdge(x_data[i]);
        edge->setId(i);

        // 设置连接的顶点
        edge->setVertex(0, v);

        // 观测数值
        edge->setMeasurement(y_data[i]);
        edge->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (w_sigma * w_sigma));
        optimizer.addEdge(edge);
    }


    // 执行优化
    cout << "start optimization " << endl;
    chrono::steady_clock::time_point  t1 = chrono::steady_clock::now();
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    chrono::steady_clock::time_point  t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "solve time cost = " << time_used.count() << "seconds. " << endl;


    // 输出优化量
    Eigen::Vector3d abc_estimate = v->estimate();
    cout << "estimated model: " << abc_estimate.transpose() << endl;

    return 0;

}

