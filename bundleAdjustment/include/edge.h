#ifndef __EDGE_H__
#define __EDGE_H__
#include "common_include.h"
#include "vertex.h"
namespace Backend {
    class Edge {
    public:
        typedef std::shared_ptr<Edge> Ptr;

        EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        explicit Edge(int residual_dimension, int num_verticies,
                const std::vector<std::string> &verticies_types = std::vector<std::string>());

        virtual ~Edge();

        unsigned long GetId() const{
            return id_;
        }
       /*!
         *
         * @param i
         * @return : 返回第i个顶点
         */
        Vertex::Ptr GetVertex(int i){
            return verticies_[i];
        }

        /*!
         *
         * @return 返回所有顶点
         */
        std::vector<Vertex::Ptr> GetAllVerticies(){
            return verticies_;
        }

        Eigen::VectorXd GetObservation() const {
            return observation_;
        }

        //
        Eigen::VectorXd GetResidual() const {
            return residual_;
        }

        std::vector<Eigen::MatrixXd> GetJacobians() const {
            return jacobians_;
        }

        Eigen::MatrixXd GetInformation() const {
            return information_;
        }

        // 返回边的类型,
        virtual std::string TypeInfo() const = 0;

        bool AddVertex(const Vertex::Ptr& vertex);

        bool SetVertices(const std::vector<Vertex::Ptr>& verticies);

        bool SetObservation(const Eigen::VectorXd& observation);

        // 计算残差
        virtual void ComputeResidual() = 0;

        // 计算雅可比
        virtual void ComputeJacobians() = 0;

        bool SetInformation(const Eigen::MatrixXd& information);


        // 计算平方误差, 会乘上信息矩阵
        double Chi2();

        // 检查边的信息是否全部设置
        bool CheckValid();






    private:
        // 边编号
        unsigned long id_;
        // 所有顶点类型
        std::vector<std::string> verticies_types_;
        // 所有的顶点
        std::vector<Vertex::Ptr> verticies_;
        // 观测信息 (N * 1)
        Eigen::VectorXd observation_;
        // 残差信息 (N * 1)
        Eigen::VectorXd residual_;
        // 每个雅可比的维度是 (N * verticies_[i].GetDimension())
        std::vector<Eigen::MatrixXd> jacobians_;
        // 信息矩阵 (N * N)
        Eigen::MatrixXd information_;

    };
}

#endif