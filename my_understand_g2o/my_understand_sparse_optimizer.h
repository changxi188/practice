#include "my_understand_vertex.hpp"
#include "my_understand_edge.hpp"
#include <eigen3/Eigen/Core>
#include <map>
#include <unordered_map>
#include <set>


class SparseOptimizer{
public:
	void update(const double* update);

	bool addVertex(MyCurveFitVertex* v);

	bool addEdge(MyCurveFitEdge* edge);

private:
	std::vector<MyVertex* > _ivMap;
	std::set<Edge*> _edges;
	std::unordered_map<int, MyCurveFitVertex*> _vertices;

};

void SparseOptimizer::update(const double* update){
	for(size_t i = 0; i < _ivMap.size(); ++i){
		MyVertex* v =_ivMap[i];

		v->oplus(update);
		update += v->Dimension;
	}
}



bool SparseOptimizer::addVertex(MyCurveFitVertex* v){
    _vertices.insert( std::make_pair(v->id(),v) );
    return true;
}

bool 
