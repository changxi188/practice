#include <iostream>
#include <g2o/core/g2o_core_api.h>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/block_sovler.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <Eigen/Core>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <chrono>

class CurveFittingVertex : public g2o::BaseVertex<3, Eigen::Vertex3d>{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW

	// reset
	virtual void setToOriginImpl() override{

	}

	// update
	virtual void oplusImpl(const double *update) override{
	
	}


	// read write 
	virtual void read(istream &in) {}
	virtual void write(ostream &out) {}


}


class CurveFittingEdege : public g2o::BaseUnaryEdge<1, double, CurveFittingVertex>{
public:


	virtual void read(istream &in){}
	virtual void write(ostrem &out) const{}


}
