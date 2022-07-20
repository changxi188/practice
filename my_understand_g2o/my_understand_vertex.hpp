#include <eigen3/Eigen/Core>

typedef double num_t;

// D 是顶点维度, T 是顶点类型
template<int D, typename T>
class MyBaseVertex{
public:
	// 设置初值
	void setEstimate(const T& et) {_estimate = et};
	// 设置顶点ID
	void setId(int i) {_id = i;};
	// 设置为0
	virtual void setToOriginImpl() = 0;
	// 设置增量方程, 由子类完成
	virtual void oplusImpl(const num_t *update) = 0;
	
	// 留空
	virtual bool read(istream &in) {}
	virtual bool write(ostream &out) const {}



	// 调用增量方程
	void oplus(const number_t* v) { oplusImpl(v); }
	// 调用设置为0
	void setToOrigin() {setToOriginImpl;}
	// 顶点维度
	static const int Dimension = D;

	// return current estimate of the vertex
	const E& estimate() const {return _estimate;};

protected:
	// 顶点ID
	int _id;
	// 估计值
	T _estimate;
	// 对应的H矩阵, J.transpose()*J
	Eigen::Map<Eigen::Matrix<num_t, D, D, Eigen::ColMajor>, Eigen::Matrix<num_t, D, D, Eigen::ColMaj>> _hessian;
	// 对应的b矩阵
	Eigen::Matrix<num_t, D, 1> _b;
};

class MyCurveFitVertex : public MyBaseVertex<3, Eigen::vector3d>{
public:
	virtual void setToOriginImpl(){
		_estimate << 0, 0, 0;
	};
	virtual void oplusImpl(const num_t *update) {
		_estimate += Eigen::Vector3d(update);
	}
};

