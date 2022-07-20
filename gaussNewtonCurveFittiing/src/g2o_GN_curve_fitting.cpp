#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Core>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>


class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d>{
public:

	virtual void setToOriginImpl() override {
		// _estimate : Eigen::Vector3d
		_estimate << 0, 0, 0;
	}
	void oplusImpl(const double *update) override {
		_estimate += Eigen::Vector3d(update);
	}
	virtual bool read(std::istream &in){}

	virtual bool write(std::ostream &out) const {}
};


class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double ,CurveFittingVertex>{
public:
	CurveFittingEdge(double x) : BaseUnaryEdge(), x_(x){}
	virtual void computeError() override {
		const CurveFittingVertex* v = static_cast<CurveFittingVertex*> (_vertices[0]);
		const Eigen::Vector3d abc = v->estimate();
		// _error : Eigen::Matrix<double, 1, 1> 
		_error[0] = _measurement - std::exp(abc(0, 0) * x_ * x_ + abc(1, 0) * x_ + abc(2, 0));
	}

	virtual void linearizeOplus() override{
		const CurveFittingVertex* v = static_cast<CurveFittingVertex*> (_vertices[0]);
		const Eigen::Vector3d abc = v->estimate();
		double jac_com = std::exp(abc(0, 0) * x_ * x_ + abc(1, 0) * x_ + abc(2, 0));
		// _jacobianOplusXi : Eigen::Matrix<double, 1, CurveFittingVertex::Dimension>
		_jacobianOplusXi[0] = - x_ * x_ * jac_com;
		_jacobianOplusXi[1] = - x_ * jac_com;
		_jacobianOplusXi[2] = - jac_com;
	}

	virtual bool read(std::istream &in){}

	virtual bool write(std::ostream & out) const {}


public:
	double x_;
};


int main(){

	double a_t = 1., b_t = 2., c_t = 1.;
	double a_e = -2., b_e = 5., c_e = 2.;
	int N = 100;
	double sigma = 1.0;
	double inv_sigma = 1 /sigma;
	cv::RNG rng;
	std::vector<double> x_;
	std::vector<double> y_;
	x_.reserve(N);
	y_.reserve(N);

	// 构造数据集
	for (int i = 0; i < N; ++i){
		x_[i] = i / 100.;
		y_[i] = std::exp(a_t * x_[i] * x_[i] + b_t * x_[i] + c_t) + rng.gaussian(sigma * sigma);
	}

	/*

	typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
	typedef g2o::LinearSolver<BlockSolverType::PoseMatrixType> LinearSolverType;

	auto solver = new g2o::OptimizationAlgorithmGaussNewton(g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
	g2o::SparseOptimizer optimer;
	optimer.setAlgorithm(solver);
	optimer.setVerbose(true);
	*/

  // 构建图优化，先设定g2o
	typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;  // 每个误差项优化变量维度为3，误差值维度为1
	typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType; // 线性求解器类型

  // 梯度下降方法，可以从GN, LM, DogLeg 中选
  auto solver = new g2o::OptimizationAlgorithmGaussNewton(
    g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
  g2o::SparseOptimizer optimizer;     // 图模型
  optimizer.setAlgorithm(solver);   // 设置求解器
  optimizer.setVerbose(true);       // 打开调试输出


	CurveFittingVertex* v1 = new CurveFittingVertex;
	v1->setId(0);
	v1->setEstimate(Eigen::Vector3d(a_e, b_e, c_e));
	optimizer.addVertex(v1);


	for(int i = 0; i < N; ++i){
		CurveFittingEdge* e = new CurveFittingEdge(x_[i]);
		e->setId(i);
		e->setVertex(0, v1);
		e->setMeasurement(y_[i]);
		e->setInformation(Eigen::Matrix<double, 1, 1>::Identity() * 1 / (sigma * sigma));
		optimizer.addEdge(e);

	}


	optimizer.initializeOptimization();


	optimizer.optimize(10, false);


	Eigen::Vector3d abc_estimate = v1->estimate();
	std::cout << "estimated model : " << abc_estimate.transpose() << std::endl;

}

