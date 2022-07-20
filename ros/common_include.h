#include <Eigen/Core>



typedef Eigen::Matrix<double, Eigen::Dynamic, 1> VecX;
typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic> MatrixX;

typedef std::map<unsigned long, std::shared_ptr<Vertex>> HashVertices;
