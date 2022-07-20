//
// Created by mr on 2020/9/5.
//

#ifndef UNTITLED_PROBLEM_H
#define UNTITLED_PROBLEM_H

#include <unordered_map>
#include <map>
#include <memory>

#include "backend/eigen_types.h"
#include "backend/edge.h"
#include "backend/vertex.h"

typedef unsigned long ulong;

namespace myslam{
namespace backend{


class Problem{
public:
    /**
     * 问题的类型
     * SLAM问题还是通用的问题
     *
     * 如果是SLAM问题那么pose和landmark是区分开的，Hessian以稀疏方式存储
     * SLAM问题只接受一些特定的Vertex和Edge
     * 如果是通用问题那么hessian是稠密的，除非用户设定某些vertex为marginalized
     */

    enum class ProblemType{
        SLAM_PROBLEM,
        GENERIC_PROBLEM
    };

    typedef unsigned long ulong;
    typedef std::map<unsigned long, std::shared_ptr<Vertex>> HashVertex;
    typedef std::unordered_map<unsigned long, std::shared_ptr<Edge>> HashEdge;
    typedef std::unordered_multimap<unsigned long, std::shared_ptr<Edge>> HashVertexIdToEdge;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

    Problem(ProblemType problemType);

    ~Problem();

    bool AddVertex(std::shared_ptr<Vertex> vertex);

    bool AddEdge(std::shared_ptr<Edge> edge);

    /*
     * 求解问题
     * @param iterations
     * @return
     */

    bool Solve(int iterations);

private:
    // Solve的实现, 解通用问题
    bool SolveGenericProblem(int iterations);

    // Solve的实现, 解SLAM问题
    bool SolveSLAMProblem(int iterations);

    // 设置各顶点的ordering_index
    void SetOrdering();

    // set ordering for new vertex in slam problem
    void AddOrderingSLAM(std::shared_ptr<Vertex> v);

    // make hessian matrix
    void MakeHessian();

    // schur solve SBA
    void SchurSBA();

    // solve linear system
    void SolveLinearSystem();

    // update states();
    void UpdateStates();

    void RollbackStates();

    // compute and update Prior
    void ComputePrior();

    void LogoutVectorSize();


    // Levenberg
    // compute LM's Lambda
    void ComputeLambdaInitLM();

    // Hessian 对角线加上或减去 Lambda
    void AddLambdatoHessianLM();

    void RemoveLambdaHessianLM();


    // 判断上次算法中Lambda是否可以,以及如何所方Lambda
    bool IsGoodStepInLM();

    // PCG iterate linear solver
    VecX PCGSolver(const MatXX &A, const VecX &b, int maxIter);

    double currentLambda_;
    double currentChi_;
    double stopThresholdLM_;
    double ni_;


    ProblemType problemType_;

    // 整个信息矩阵
    MatXX Hessian_;
    VecX b_;
    VecX delta_x_;

    // 先验部分信息
    MatXX H_prior_;
    VecX b_prior_;
    MatXX Jt_prior_inv;
    VecX err_prior_;

    // SBA的pose部分
    MatXX H_pp_schur_;
    VecX b_pp_schur_;
    // Hessian 的Landmark 和pose部分
    MatXX H_pp_;
    VecX b_pp_;
    MatXX H_ll_;
    VecX b_ll_;

    // all vertices
    HashVertex verticies_;

    // all edges
    HashEdge edges_;

    // search edge by vertex id
    HashVertexIdToEdge vertexIdToEdge_;

    // Ordering related
    ulong ordering_poses_ = 0;
    ulong ordering_landmarks_ = 0;
    ulong ordering_generic_ = 0;
    std::map<unsigned long, std::shared_ptr<Vertex>> idx_pose_vertices_;
    std::map<unsigned long, std::shared_ptr<Vertex>> idx_landmark_vertices_;

    // verticies need to marg.
    HashVertex verticies_marg_;

    bool bDebug = false;
    double t_hessian_cost = 0.0;
    double t_PCGsolve_cost_ = 0.0;

};
}
}

#endif //UNTITLED_PROBLEM_H
