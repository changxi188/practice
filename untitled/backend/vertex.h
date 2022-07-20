//
// Created by mr on 2020/9/5.
//

#ifndef UNTITLED_VERTEX_H
#define UNTITLED_VERTEX_H

#include <backend/eigen_types.h>

namespace myslam{
namespace backend{

/*
 * @brief vertex is a parameter block
 * paramers store as VecX, need to
 */

class Vertex{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    /*
     * 构造函数
     * @param num_dimension 顶点自身纬度
     * @param local_dimension 本地参数化纬度, 为-1时认为本身纬度一样
     */

    explicit Vertex(int num_dimension, int local_dimension = -1);

    virtual ~Vertex();

    // return parameters dimension
    int Dimension() const;

    // return parameters local dimension
    int LocalDimension() const;

    // return vertex id
    unsigned long Id() const {return id_;}

    // return parameters value
    VecX Parameters() const {return parameters_;}

    // return parameters reference
    VecX &Parameters() {return parameters_;}

    // set paramters value
    void SetParameters(const VecX &params) { parameters_ = params;}

    // 加法
    virtual void Plus(const VecX &delta);

    // return vertex name, implement in chirdren class
    virtual std::string TypeInfo() const  = 0;

    int OrderingId() const { return ordering_id_;}

    void SetOrderingId(unsigned long id) {ordering_id_ = id;}

    // fixed value
    void SetFixed(bool fixed = true){
        fixed_ = fixed;
    }

    // check whether this vertex is fixed
    bool IsFixed() const {return fixed_;}


protected:
    VecX parameters_;   //
    int local_dimension_;   //
    unsigned long id_;      // id of vertex

    // ordering id
    unsigned long ordering_id_ = 0;

    bool fixed_ = false;    //

};
}
}

#endif //UNTITLED_VERTEX_H
