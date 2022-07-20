#include <eigen3/Eigen/Core>
#include "my_understand_vertex.hpp"

typedef double num_t;

template <int D, typename E>
class MyBaseEdge{
public:
	static const int Dimension = D;

	virtual void computeError() = 0;

	virtual void linearOplus() = 0;

	virtual num_t chi2() const{
		return _error.dot(_information * _error);
	}

	void setId(int id) { _id = id};
	void setMeasurement(const E& measurement) { _measurement = measurement;}


protected:
	int _id;
	E _measurement;
	Eigen::Matrix<num_t, D, 1> _error;
	Eigen::Matrix<num_t, D, D> _information;
};

template <int D, typename E, typename VertexXi>
class MyUnaryEdge : public MyBaseEdge<D, E>{
public:
	MyUnaryEdge() : MyBaseEdge<D, E>(), _jacobianOplusXi(0, D, VertexXi::Dimension){
		_vertices.resize(1, nullptr);
	}

	void setVertex(size_t i, VertexXi* v) {
		assert(i < _vertices.size() && "index out of bounds");
		_vertices[i] = v;
	}


protected:

	Eigen::Matrix<num_t, D, VertexXi::Dimension> _jacobianOplusXi;

	std::vector<VertexXi*> _vertices;

};

class MyCurveFitEdge : MyUnaryEdge<1, double, MyCurveFitVertex>{
public:
	MyCurveFitEdge(double x) : MyUnaryEdge(), _x(x) {}

	virtual void linearOplus() override {
		const MyCurveFitVertex *v = static_cast<const MyCurveFitEdge *> (_vertices[0]);
		const Eigen::Vector3d abc = v->estimate();
		double y = exp(abc[0] * _x * _x + abc[1] * _x + abc[2];
		_jacobianOplusXi[0] = -_x * _x * y;
		_jacobianOplusXi[1] = -_x * y;
		_jacobianOplusXi[2] = -y;
	}

	virtual void computeError() override {
		const MyCurveFitVertex* v = static_cast<const MyCurveFitVertex*> (_vertices[0]);
		const Eigen::Vector3d abc = v->estimate();
		_error(0, 0) = _measurement - std::exp(abc(0, 0) * _x * _x + abc(1, 0) * _x + abck(2, 0);
	}

	virtual bool read(istream &in){}

	virtual bool write(ostream &out) const {}
private:
	double _x;
};
