#include <vector>
#include <string>
#include <Eigen/Core>
#include <memory>
#include <memory>
#include <map>


int global_edge_id = 0;

class Edge{

public:
	Edge(int residual_dimension, int num_verticies,
		const std::vector<std::string> &verticies_types){

		residual_.resize(residual_dimension, 1);

		if(!vertices_tpyes_.empty()){
			verticies_types_ = vertices_types;
		}

		jacobians_.resize(num_verticies);

		id_ = global_edge_id++;

		Eigen::MatrixXd information(redidual_dimension, residual_dimension);

		information.setIdentity();

		information_ = information;
		}



	void SetVertex(const std::vector<std::shared_ptr<Vertex>>& edge_vertex){
		verticies_ = edge_vertex;
	}



	int Id(){ return id_;

	virtual ~Edge(){};


private:

	VecX residual_;

	std::vector<std::string> verticies_types_;

	std::vector<std::shared_ptr<Vertex>> verticies_;

	std::vector<MatXX> jacobians_;

	int id_;

	int ordering_id_;

	MatXX information_;

	VecX observation_;
	
};
