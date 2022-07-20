#include "vertex.h"
namespace Backend{

    Vertex::Vertex(int num_dimension, int local_dimension) {
        static unsigned long global_id = 0;
        parameters_.resize(num_dimension, 1);
        local_dimension_ = local_dimension > 0 ? local_dimension : num_dimension;
        id_ = global_id++;
    }

    Vertex::~Vertex() {}

    /*
    Vertex::Ptr Vertex::CreateVertex(int num_dimension, int local_dimension) {
        static unsigned long global_vertex_id = 0;
        std::shared_ptr<Vertex> new_vertex = std::make_shared<Backend::Vertex>(num_dimension, local_dimension);
        new_vertex->id_ = global_vertex_id++;
        return new_vertex;
    }
     */

    void Vertex::Plus(const Eigen::VectorXd &delta) {
        parameters_ += delta;
    }

    void Vertex::SetFixed(bool fixed) {
        fixed_ = fixed;
    }


}

