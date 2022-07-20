#ifndef __VERTEX_H__
#define __VERTEX_H__
#include "common_include.h"
namespace Backend {
    class Vertex {
    public:
        typedef std::shared_ptr<Vertex> Ptr;
        explicit Vertex(int num_dimension, int local_dimension = -1);
        virtual ~Vertex();

        // TODO : 因为纯虚函数的存在, 导致这里的工厂模式不能用
        // static Vertex::Ptr CreateVertex(int num_dimension, int local_dimension);

        /*!
         *
         * @return 返回参数维度
         */
        int GetDimension() const {
            return parameters_.rows();
        };

        int GetLocalDimension() const{
            return local_dimension_;
        };

        /*!
         *
         * @return 返回顶点编号
         */
        unsigned long GetId() const {
            return id_;
        };

        Eigen::VectorXd GetParameters() const {
            return parameters_;
        };

        Eigen::VectorXd& GetParameters(){
            return parameters_;
        };

        bool IsFixed() const{
            return fixed_;
        };

        /*!
         *
         * @param fixed : TODO : 暂时不知道是干什么的
         */
        void SetFixed(bool fixed = true);

        // 默认是加法, 后面可以重构
        virtual void Plus(const Eigen::VectorXd& delta);

        virtual std::string TypeInfo() const = 0;



    private:
        // 实际存储的变量值
        Eigen::VectorXd parameters_;
        // 局部参数化维度
        int local_dimension_;
        // 顶点编号
        unsigned long id_;
        // 是否固定
        bool fixed_ = false;
    };
}


#endif