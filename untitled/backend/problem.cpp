//
// Created by mr on 2020/9/5.
//

#include "backend/problem.h"
#include <iostream>
#include <eigen3/Eigen/Dense>
#include "utils/tic_toc.h"

using namespace std;

namespace myslam{

namespace backend{

Problem::Problem(ProblemType problemType) {
    problemType_ = problemType;
    LogoutVectorSize();
    verticies_marg_.clear();
}

Problem::~Problem() {}

void Problem::LogoutVectorSize() {

}


bool Problem::AddVertex(std::shared_ptr<Vertex> vertex) {

    if (verticies_.find(vertex->Id()) != verticies_.end()){
        return false;
    } else{
        verticies_.insert(std::pair<unsigned long, std::shared_ptr<Vertex>>(vertex->Id(), vertex));
    }

    return true;
}

bool Problem::AddEdge(std::shared_ptr<Edge> edge) {

    if (edges_.find(edge->Id()) == edges_.end()){
        edges_.insert(pair<unsigned long, shared_ptr<Edge>>(edge->Id(), edge));
    } else{
        return false;
    }

    for(auto &vertex : edge->Verticies()){
        vertexIdToEdge_.insert(pair<ulong, shared_ptr<Edge>>(vertex->Id(), edge));
    }
    return true;
}

void Problem::SetOrdering() {
    // 每次重新计数
    ordering_poses_ = 0;
    ordering_generic_ = 0;
    ordering_landmarks_ = 0;


    // verticies is map type,
    // 统计待估计的所有变量的总维度
    for(auto vertex : verticies_){
        // 所有优化变量的总维数
        ordering_generic_ += vertex.second->LocalDimension();
    }
}

void Problem::MakeHessian() {
    TicToc t_h;

    // 直接构造大的H矩阵
    ulong size = ordering_generic_;
    MatXX H(MatXX::Zero(size, size));
    VecX b(VecX::Zero(size));

    // TODO:: accelate, accelate, accelate


    // 遍历每个残差, 计算他们的雅可比, 道道最后的 H = J^T * J
    for (auto &edge : edges_){
        edge.second -> ComputeResidual();
        edge.second -> ComputeJacobians();
        auto jacobians = edge.second->Jacobians();
        auto verticies = edge.second->Verticies();
        assert(jacobians.size() == verticies.size());
        for (size_t i = 0; i < verticies.size(); ++i){
            auto v_i = verticies[i];
            if (v_i->IsFixed()) continue;

            auto jacobian_i = jacobians[i];
            ulong index_i = v_i->OrderingId();
            ulong dim_i = v_i->LocalDimension();

            MatXX JtW = jacobian_i.transpose() * edge.second->Information();
            for (size_t j = i; j < verticies.size(); ++j){
                auto v_j = verticies[j];

                if (v_j->IsFixed()) continue;

                auto jacobian_j = jacobians[j];
                ulong index_j = v_j->OrderingId();
                ulong dim_j = v_j->LocalDimension();

                assert(v_j -> OrderingId() != -1);
                MatXX hessian = JtW * jacobian_j;

                H.block(index_i, index_j, dim_i, dim_j).noalias() += hessian;
                if(j != i){
                    H.block(index_j, index_i, dim_j, dim_i).noalias() += hessian.transpose();
                }
            }
            b.segment(index_i, dim_i).noalias() -= JtW * edge.second->Residual();
        }
    }
    Hessian_ = H;

    b_ = b;
    t_hessian_cost += t_h.toc();

    delta_x_ = VecX::Zero(size);
}

/// LM
void Problem::ComputeLambdaInitLM() {
   ni_ = 2.;
   currentLambda_ = -1;
   currentChi_ = 0.0;

   // TODO:: robust cost chi2
   for (auto edge : edges_){
       currentChi_ += edge.second->Chi2();
   }

   if (err_prior_.rows() > 0)
       currentChi_ += err_prior_.norm();

   stopThresholdLM_ = 1e-6 * currentChi_;

   double maxDiagonal = 0;

   ulong size = Hessian_.cols();
   assert(Hessian_.rows() == Hessian_.cols() && "Hessian is not square");

   for (ulong i = 0; i < size; ++i){
       maxDiagonal = std::max(fabs(Hessian_(i, i)), maxDiagonal);
   }

   double tau = 1e-5;
   currentLambda_ = tau * maxDiagonal;
}

void Problem::AddLambdatoHessianLM() {
    ulong size = Hessian_.cols();
    assert(Hessian_.rows() == Hessian_.cols() && "Hessian is not square");
    for (ulong i = 0; i < size; ++i){
        Hessian_(i, i) += currentLambda_;
    }
}

void Problem::SolveLinearSystem() {
    delta_x_ = Hessian_.inverse() * b_;
}

void Problem::RemoveLambdaHessianLM() {
    ulong size = Hessian_.cols();
    assert(Hessian_.rows() == Hessian_.cols() && "Hessian is not square");
    for (ulong i = 0; i < size; ++i){
        Hessian_(i, i) -= currentLambda_;
    }
}

void Problem::UpdateStates() {
    for (auto vertex: verticies_){
        ulong idx = vertex.second->OrderingId();
        ulong dim = vertex.second->LocalDimension();
        VecX delta = delta_x_.segment(idx, dim);

        vertex.second->Plus(delta);
    }

}

bool Problem::IsGoodStepInLM() {
    double scale = 0;
    scale = delta_x_.transpose() * (currentLambda_ * delta_x_ + b_);
    scale += 1e-3;

    // recompute residuals after update state
    double tempChi = 0.0;
    for (auto edge : edges_){
        edge.second->ComputeResidual();
        tempChi += edge.second->Chi2();
    }

    double rho = (currentChi_ - tempChi) /scale;
    if (rho > 0 && isfinite(tempChi)){
        double alpha = 1. - pow((2 * rho - 1), 3);
        alpha = std::min(alpha, 2. / 3.);
        double scaleFactor = (std::max)(1. /3. ,alpha);
        currentLambda_ *= scaleFactor;
        ni_ = 2;
        currentChi_ = tempChi;
        return true;
    } else{
        currentLambda_ *= ni_;
        ni_ *= 2;
        return false;
    }
}

void Problem::RollbackStates() {
    for(auto vertex: verticies_){
        ulong idx = vertex.second->OrderingId();
        ulong dim = vertex.second->LocalDimension();
        VecX delta = delta_x_.segment(idx, dim);

        vertex.second->Plus(-delta);
    }
}

bool Problem::Solve(int iterations) {
    if (edges_.size() == 0 || verticies_.size() == 0){
        std::cerr << "cannot solve problem without edges or verticies" << std::endl;
        return false;
    }
    TicToc t_solve;

    // 统计变量维度, 为构建H矩阵作准备
    SetOrdering();

    // 遍历Edge, 构建 H = J^T * J 矩阵
    MakeHessian();

    // LM 初始化
    ComputeLambdaInitLM();

    // LM 算法迭代求解
    bool stop = false;
    int iter = 0;
    while(!stop && (iter < iterations)){
        std::cout << "iter: " << iter << ", chi = " << currentChi_ << ", Lambda= "
         << currentLambda_ << std::endl;

        bool oneStepSuccess = false;
        int false_cnt = 0;
        while(!oneStepSuccess){
            // setLambda
            AddLambdatoHessianLM();

            // 第四步, 解线性方程 H*X = B
            SolveLinearSystem();

            //
            RemoveLambdaHessianLM();


            // 优化退出条件1: delta_x_ 很小退出
            if (delta_x_.squaredNorm() <= 1e-6 || false_cnt > 10){
                stop = true;
                break;
            }


            // 更新状态量 X = X + delta_x
            UpdateStates();

            // 判断当前步是否可行, 以及 LM 的lambda怎么更新
            oneStepSuccess = IsGoodStepInLM();

            // 后续处理
            if (oneStepSuccess){
                MakeHessian();
                false_cnt = 0;
            } else{
                false_cnt++;
                RollbackStates();
            }
        }
        iter++;

        // 优化退出条件3: currentChi_ 根第一次的
        if(sqrt(currentChi_) <= stopThresholdLM_)
            stop = true;
    }
    std::cout << "problem solve cost: " << t_solve.toc() << " ms" << std::endl;
    std::cout << " makeHessian cost: " << t_hessian_cost << " ms " << std::endl;
    return true;

}

}
}