//
// Created by mr on 2020/9/5.
//

#ifndef UNTITLED_EDGE_H
#define UNTITLED_EDGE_H

#include <memory>
#include <string>
#include <backend/eigen_types.h>

namespace myslam{
namespace backend{

class Vertex;

/**
 * 边负责计算残差
 * 代价函数: 残差*信息*残差, 是一个数值, 由后端求和后最小化
 */

class Edge{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /*
     * 构造函数,自动化配雅可比的空间
     * @param residual_dimension 残差纬度
     * @param num_verticies 顶点数量
     * @param verticies_types 顶点类型名称, 不给的化check中不会检查
     */
    explicit Edge(int residual_dimension, int num_verticies,
            const std::vector<std::string> &verticies_types = std::vector<std::string>());

    virtual ~Edge();

    /// return id
    unsigned long Id() const {return id_;}

    /*
     * set a vertex
     * @param vertex
     */
    bool AddVertex(std::shared_ptr<Vertex> vertex){
        verticies_.emplace_back(vertex);
        return true;
    }

    /*
     * set some vertices
     * @param vertices sort order in reference
     * @return
     */
    bool SetVertex(const std::vector<std::shared_ptr<Vertex>> &vertices){
        verticies_ = vertices;
        return true;
    }

    // return ith vertex
    std::shared_ptr<Vertex> GetVertex(int i){
        return verticies_[i];
    }

    // return all verticies
    std::vector<std::shared_ptr<Vertex>> Verticies() const{
        return verticies_;
    }

    // return number of verticies
    size_t NumVerticies() const {return verticies_.size();}

    // return edge information,
    virtual std::string TypeInfo() const = 0;

    // compute residual, implement by chirdren class
    virtual void ComputeResidual() = 0;

    // compute jacobians, implement by chirdren class
    virtual void ComputeJacobians() = 0;

    // compute 平方误差
    double Chi2();

    // return residual
    VecX Residual() const {return residual_;}

    // return jacobian
    std::vector<MatXX> Jacobians() const {return jacobians_;}

    /// set information matrix
    void SetInformation(const MatXX &information){
        information_ = information;
    }

    // return information
    MatXX Information() const {
        return information_;
    }

    // set observation
    void SetObservation(const VecX &observation){
        observation_ = observation;
    }

    // return obserbation
    VecX Observation() const{
        return observation_;
    }

    // check all information about edge has down
    bool CheckValid();

    int OrderingId() const {return ordering_id_;}

    void SetOrderingId(int id) {ordering_id_ = id;}



protected:
    unsigned long id_;  // edge id
    int ordering_id_;   // edge id in problem
    std::vector<std::string> verticies_types_;  //
    std::vector<std::shared_ptr<Vertex>> verticies_;    // edge's verticies
    VecX residual_;     //
    std::vector<MatXX> jacobians_;      //
    MatXX information_;
    VecX observation_;
};
}
}

#endif //UNTITLED_EDGE_H
