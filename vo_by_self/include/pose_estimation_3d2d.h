//
// Created by mr on 2020/7/19.
//

#ifndef VO_BY_SELF_POSE_ESTIMATION_3D2D_H
#define VO_BY_SELF_POSE_ESTIMATION_3D2D_H

#include <opencv2/opencv.hpp>
#include <g2o/core/base_vertex.h>
#include <g2o/core/base_unary_edge.h>
#include <g2o/core/base_binary_edge.h>
#include <g2o/core/sparse_optimizer.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/solver.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>
#include <sophus/se3.hpp>
#include <Eigen/Core>

typedef std::vector<Eigen::Vector2d, Eigen::aligned_allocator<Eigen::Vector2d>> VecVector2d;
typedef std::vector<Eigen::Vector3d, Eigen::aligned_allocator<Eigen::Vector3d>> VecVector3d;

cv::Point2f pixel2cam(const cv::Point2f &p, const cv::Mat &K){
    return cv::Point2f(
            (p.x - K.at<double>(0, 2)) / K.at<double>(0, 0),
            (p.y - K.at<double>(1, 2)) / K.at<double>(1, 1)
    );
}

Eigen::Vector2d cam2pixel(const Eigen::Vector3d p3d, double fx, double fy, double cx, double cy){
    return Eigen::Vector2d(
            p3d[0] * fx / p3d[2] - cx,
            p3d[1] * fy / p3d[2] - cy
            );

}


void find_feature_matches(const cv::Mat &img_1, const cv::Mat &img_2,
                          std::vector<cv::KeyPoint> &keypoints_1,
                          std::vector<cv::KeyPoint> &keypoints_2,
                          std::vector<cv::DMatch> &matches){

    cv::Ptr<cv::FeatureDetector> detector = cv::ORB::create();
    cv::Ptr<cv::DescriptorExtractor> descriptor = cv::ORB::create();
    cv::Ptr<cv::DescriptorMatcher> matcher = cv::DescriptorMatcher::create("BruteForce-Hamming");

    detector->detect(img_1, keypoints_1);
    detector->detect(img_2, keypoints_2);

    cv::Mat descriptors_1, descriptors_2;
    descriptor->compute(img_1, keypoints_1, descriptors_1);
    descriptor->compute(img_2, keypoints_2, descriptors_2);

    std::vector<cv::DMatch> match;
    matcher->match(descriptors_1, descriptors_2, match);

    double min_dist = 1000, max_dist = 10;
    for (const auto  &m : match){
        if (m.distance < min_dist) min_dist = m.distance;
        if (m.distance > max_dist) max_dist = m.distance;
    }

    std::cout << "min_dist = " << min_dist << std::endl;
    std::cout << "max_dist = " << max_dist << std::endl;

    for (const auto &m : match){
        if (m.distance < std::max(min_dist * 2, 30.0)){
            matches.push_back(m);
        }
    }

    std::cout << "matches : " << matches.size() << std::endl;
}


void bundleAdjustmentGaussNewton(
        const VecVector2d &points_2d,
        const VecVector3d &points_3d,
        const cv::Mat &K,
        Sophus::SE3d &pose){
    typedef Eigen::Matrix<double, 6, 1> Vector6d;
    const int iteration = 10;
    double cost = 0, lastcost= 0;
    double fx = K.at<double>(0, 0);
    double fy = K.at<double>(1, 1);
    double cx = K.at<double>(0, 2);
    double cy = K.at<double>(1, 2);

    for (int iter = 0; iter < iteration; ++iter){
        Eigen::Matrix<double, 6, 6> H = Eigen::Matrix<double, 6, 6>::Zero();
        Vector6d b = Vector6d::Zero();

        cost = 0;

        for (int i = 0; i < points_3d.size(); ++i){
            Eigen::Vector3d pc = pose * points_3d[i];
            double inv_z = 1.0 / pc[2];
            double inv_z2 = inv_z * inv_z;
            Eigen::Vector2d proj( cam2pixel(pc, fx, fy, cx, cy));

            Eigen::Vector2d e = points_2d[i] - proj;

            cost += e.squaredNorm();

            Eigen::Matrix<double, 2, 6> J;

            J << -fx * inv_z, 0, fx * pc[0] * inv_z2, fx * pc[0] * pc[1] * inv_z2, -(fx + fx * pc[0] * pc[0] * inv_z2), fx * pc[1] * inv_z2,
                 0, -fy * inv_z, fy * pc[1] * pc[1] * inv_z2, fy + fy * pc[1] * pc[1] * inv_z2, fy * pc[0] * pc[1] * inv_z2, fy * pc[0] * inv_z;

            H += J.transpose() * J;
            b += -J.transpose() * e;
        }

        Vector6d dx;
        dx = H.ldlt().solve(b);
        if (isnan(dx[0])){
            std::cout << "result is nan!" << std::endl;
            break;
        }

        if (iter > 0 && cost >= lastcost){
            std::cout << "cost : " << cost << ", last cost " << lastcost << std::endl;
            break;
        }

        pose = Sophus::SE3d::exp(dx) * pose;
        lastcost = cost;
        std::cout << "iteration " << iter << " cost = " << std::setprecision(12) << cost << std::endl;
        if (dx.norm() < 1e-6){
            break;
        }
    }
    std::cout << "pose by g-n : \n" << pose.matrix() << std::endl;

}

// 顶点维度6, 内在类型为SE3d
class VertexPose : public g2o::BaseVertex<6, Sophus::SE3d> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    virtual void setToOriginImpl() override {
        _estimate = Sophus::SE3d();
    }

    // left multiplication on SE3
    virtual void oplusImpl(const double *update) override {
        Eigen::Matrix<double, 6, 1> update_eigen;
        update_eigen << update[0], update[1], update[2], update[3], update[4], update[5];
        _estimate = Sophus::SE3d::exp(update_eigen) * _estimate;
    }

    virtual bool read(std::istream &in) override {}

    virtual bool write(std::ostream &out) const override {}

};

// 误差维度2, 测量值类型Vector2d, 顶点类型VertexPose
class EdgeProjection : public g2o::BaseUnaryEdge<2, Eigen::Vector2d, VertexPose>{
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

    EdgeProjection(const Eigen::Vector3d &pos, const Eigen::Matrix3d &K) : _pos3d(pos), _K(K) {}

    virtual void computeError() override {
        const VertexPose *v = static_cast<VertexPose *>(_vertices[0]);
        Sophus::SE3d T = v->estimate();
        Eigen::Vector3d pos_pixel = _K * (T * _pos3d);
        pos_pixel /= pos_pixel[2];
        _error = _measurement - pos_pixel.head<2>();
    }

    virtual void linearizeOplus() override {

        const VertexPose *v = static_cast<VertexPose *>(_vertices[0]);

        Sophus::SE3d T = v->estimate();
        Eigen::Vector3d pos_cam = T * _pos3d;
        double fx = _K(0, 0);
        double fy = _K(1, 1);
        double cx = _K(0, 2);
        double cy = _K(1, 2);
        double X = pos_cam[0];
        double Y = pos_cam[1];
        double Z = pos_cam[2];
        double Z2 = Z * Z;
        _jacobianOplusXi
            << -fx / Z, 0, fx * X / Z2, fx * X * Y / Z2, -fx -fx * X * X / Z2, fx * Y / Z,
            0, -fy / Z, fy * Y / Z2, fy + fy * Y * Y / Z2, -fy * X * Y/ Z2, -fy * X / Z;
    }

    virtual bool read(std::istream &in) override {}
    virtual bool write(std::ostream &out) const override {}
private:
    Eigen::Vector3d _pos3d;
    Eigen::Matrix3d _K;
};
void bundleAdjustmentG2O(
        const VecVector2d &pts_2d_eigen,
        const VecVector3d &pts_3d_eigen,
        const cv::Mat &K,
        Sophus::SE3d &pose_g2o){

    // set g2o
    // pose is 6, landmar is 3
    typedef g2o::BlockSolver<g2o::BlockSolverTraits<6, 3>> BlockSolverType;
    // 线性求解器类型
    typedef g2o::LinearSolverDense<BlockSolverType::PoseMatrixType> LinearSolverType;

    // 梯度下降法, 可以从GN, LM, DogLeg中选择
    g2o::OptimizationAlgorithmGaussNewton *optimizationAlgorithmType =
            new g2o::OptimizationAlgorithmGaussNewton(
            g2o::make_unique<BlockSolverType>(g2o::make_unique<LinearSolverType>()));

    // 图模型
    g2o::SparseOptimizer optimizer;


    // 设置求解器
    optimizer.setAlgorithm(optimizationAlgorithmType);
    // 打开调试输出
    optimizer.setVerbose(true);

    // vertex
    VertexPose *vertex_pose = new VertexPose();
    vertex_pose->setId(0);
    vertex_pose->setEstimate(Sophus::SE3d());
    optimizer.addVertex(vertex_pose);

    // K
    Eigen::Matrix3d K_eigen;
    K_eigen <<
        K.at<double>(0, 0), K.at<double>(0, 1), K.at<double>(0, 2),
        K.at<double>(1, 0), K.at<double>(1, 1), K.at<double>(1, 2),
        K.at<double>(2, 0), K.at<double>(2, 1), K.at<double>(2, 2);

    // edges
    int index = 1;
    for (size_t i = 0; i < pts_2d_eigen.size(); ++i){
        auto p2d = pts_2d_eigen[i];
        auto p3d = pts_3d_eigen[i];
        EdgeProjection *edge = new EdgeProjection(p3d, K_eigen);
        edge->setId(index);
        edge->setVertex(0, vertex_pose);
        edge->setMeasurement(p2d);
        edge->setInformation(Eigen::Matrix2d::Identity());
        optimizer.addEdge(edge);
        index++;
    }

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    optimizer.setVerbose(true);
    optimizer.initializeOptimization();
    optimizer.optimize(10);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    std::chrono::duration<double> time_used = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
    std::cout << "optimization costs time " << time_used.count() << "seconds " << std::endl;
    std::cout << "pose estimated by g2o " << vertex_pose->estimate().matrix() << std::endl;

}

#endif //VO_BY_SELF_POSE_ESTIMATION_3D2D_H
