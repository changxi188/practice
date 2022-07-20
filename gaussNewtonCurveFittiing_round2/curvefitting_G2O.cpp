#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <eigen3/Eigen/Core>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/linear_solver.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/core/sparse_optimizer.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vector3d>{

	virtual void setToOrigin() override{
		_estimate << 0, 0, 0;
	}

	virtual void oplusImpl(const double *update) override{
		_estimate += Eigen::Vector3d(update);

	}

	virtual bool read(std::istream &in) {}

	virtual bool write(std::ostream &out) {}

};


class CurveFittingEdge : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>{
	virtual void computeError() override{
		_error = 	
	}

	virtual void computeOpuls() override{
		_jacobianXi[0] = 	
	}
};



int main(){
	double a_t = 1., b_t = 2., c_t = 3.;
	double a_e = 6., b_e = 5., c_e = 4.;

	double sigma = 1.;
	double inv_sigma = 1 / sigma;

	cv::RNG rng;
	std::vector<double> x_, y_;

	int data_n = 100;
	int iter_n = 10;

	for(int i = 0; i < data_n; ++i){
		x_.push_back(i / 100.);
		y_.push_back(std::exp(a_t * x_[i] * x_[i] + b_t * x_[i] + c_t) + rng.gaussian(sigma * sigma));
	}

	typedef g2o::BlockSolver<g2o::BlockSolverTraits<3, 1>> BlockSolverType;
	typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

	auto algorithm = new g2o::OptimizationAlgorithmGaussNewton(
		g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));
	g2o::SparseOptimizer optimizer;
	optimizer.setAlgorithm(algorithm);
	optimizer.setVerbose(true);


	CurveFittingVertex* v = new CurveFittingVertex();
	v->setId(0);
	v->setEstimate(Eigen::Vector3d(a_e, b_e, c_e));
	optimizer.addVertex(v);

	for (int i = 0; i < data_n, ++i){
		CurveFittingVertex* edge = new CurveFittingEdge(x_[i]);
		edge->setId(i);
		edge->setMeasurement(y_[i]);
		edge->setVertex(0, v);
		edge->setInformation(Eigen::Matrix<double, 1, 1>(inv_sigma));
		optimizer.addEdge(edge);
	}




	return 0;
}
