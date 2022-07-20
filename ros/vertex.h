#include <iostream>
#include "common_include.h"
#include <vector>
#include <string>
#include <Eigen/Core>


typedef Eigen::Matrix<double, Eigen::Dynamic, Eige::Dynamic> MatrixX;
typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VecX;


unsigned long global_vertex_id = 0;

class Vertex{
public:
	
	Vertex(int num_dimension, int local_dimension = -1){

		parameters_.resize(num_dimension, 1);

		local_dimension_ = local_dimension > 0 ? local_dimension, num_dimension;

		id_ = global_vertex_id++;
	}

	unsigned long Id(){

		return id_;
	}
	
	void SetParameters(const VecX& param){
		
		parameters_ = param;
	}

	int Local_dimension() { return local_dimension_;}

virtual ~Vertex(){}

private:
	Eigen::Matrix<double, Eigen::Dynamic, 1> parameters_;

	unsigned long id_ = 0;

	int local_dimension_;

	unsigned long ordering_id_ = 0;

	bool fixed_- = false;

};
