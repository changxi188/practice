#include "common_include.h"
#include <vector>
#include <string>
#include "vertex.h"
#include <memory>
#include <map>

typedef std::map<unsigned long, std::shared_ptr<Vertex>> HashVertices;

typedef std::map<unsigned long, std::shared_ptr<Edge>> HashEdges;

class Problem{
public:
	enum class ProblemType{
		SLAM_PROBLEM,
		GENERIC_PROBLEM
	};

	

	bool AddVertex(std::shared_ptr<Vertex> vertex){	

		if(vertices_.find(vertex->Id()) != vertices_.end()){
			return false;
		} else{
			vertics_.insert(std::pair<unsigned long, std::shared_ptr<Vertex>(vertex->Id(), vertex));
		}
		return true;
	}


	bool AddEdge(std::shared_ptr<Edge> edge){
		
		if(edges_.find(edge->Id() != edges_.end(){
			return false;
		} else{
		
			edges_.insert(std::pair<unsigned long ,std::shared_ptr<Edge>(edge->Id(), edge));
		}
	}

	bool SetOrdering(){

		int ordering_generic_ = 0;

		for(auto &vertex : verticies_){
			ordering_generic_ += vertex.second->Local_dimension();
		}
	}

	bool Solve(int iterations){
	
		if (edges_.size() == 0 || vertices_size() == 0){
			std::cerr << " Cannot solve problem " << std::endl;
			return false;
		}
	VecX jacobians_;

		SetOrdering();
	}	
	

private:

	HashVertices vertices_;

	HashEdges edges_;

	int ordering_poses_ = 0;
	
	int ordering_generic_ = 0;

	int ordering_landmarks_ = 0;


};
