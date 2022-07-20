#include "edge.h"

#include <utility>
namespace Backend{

    Edge::Edge(int residual_dimension, int num_verticies, const std::vector<std::string> &verticies_types) {
        static unsigned long global_id = 0;
        id_ = global_id++;
        if(!verticies_types.empty()){
            verticies_types_ = verticies_types;
        }
        residual_.resize(residual_dimension, 1);
        jacobians_.resize(num_verticies);

        Eigen::MatrixXd information(residual_dimension, residual_dimension);
        information.setIdentity();
        information_ = information;

    }

    Edge::~Edge() = default;

    bool Edge::AddVertex(const Vertex::Ptr& vertex) {
        verticies_.emplace_back(vertex);
        return true;
    }

    bool Edge::SetVertices(const std::vector<Vertex::Ptr>& verticies) {
        verticies_ = verticies;
        return true;
    }

    bool Edge::SetObservation(const Eigen::VectorXd& observation) {
        observation_ = observation;
        return true;
    }

    bool Edge::SetInformation(const Eigen::MatrixXd &information) {
        information_ = information;
        return true;
    }

    double Edge::Chi2() {
        return residual_.transpose() * information_ * residual_;
    }

    bool Edge::CheckValid() {
        if(!verticies_types_.empty()){
            for(size_t i = 0; i < verticies_.size(); ++i){
                if(verticies_types_[i] != verticies_[i]->TypeInfo()){
                    std::cout << "Vertex type does not match, should be " << verticies_types_[i] <<
                     ", but set to " << verticies_[i]->TypeInfo() << std::endl;
                    return false;
                }

                }
            }
        return true;
    }
}