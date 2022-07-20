#include <iostream>
#include <Eigen/Core>
#include <Eigen/Geometry>
#include <sophus/se3.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <boost/format.hpp>


using namespace std;


int main(){

	std::string dataset_path("/home/mr/Downloads/practice/qTe/rgbd/");
	std::string pose_file(dataset_path + "pose.txt");

	boost::format relative_pose_file(dataset_path + "t_%02ds.txt");
	boost::format intrinsics_file(dataset_path + "cam_%02d.txt");
	
	ifstream fin(pose_file);
	//ofstream fout(relative_pose_file);
	if (!fin){
		cout << " file open error" << endl;
		return -1;
	}
	//vector<Eigen::Vector3d> translations;
	//vector<Eigen::Quaterniond> quaternionds;
	double tx, ty, tz;
	double w, x, y, z;
	vector<Sophus::SE3d> poses;

	// 读取pose文件, 构建SE3d
	for (int i = 0; i < 5; ++i){
		fin >> tx >> ty >> tz;
		fin >> x >>  y >> z >> w;
		Eigen::Vector3d temTrans(tx, ty, tz);
		Eigen::Quaterniond temQua(w, x, y, z);
		Sophus::SE3d temPose(temQua, temTrans);
		//translations.push_back(temTrans);
		//quaternionds.push_back(temQua);
		poses.push_back(temPose);
		
	}

	// 计算Tst
	Sophus::SE3d relative_pose;
	Sophus::SE3d tgt_poses = poses[0];

	/*
	for (size_t i = 1; i < poses.size() - 1; ++i){
		//cout << poses[i].matrix() << endl;
		//cout << "-------------------------------------------------------------" << endl;

		relative_pose = poses[i + 1] * poses[i].inverse();
		cout << relative_pose.matrix() << endl;

		Eigen::Matrix3d rotation_matrix = relative_pose.rotationMatrix();
		Eigen::Vector3d eA = rotation_matrix.eulerAngles(0, 1, 2);
		cout << eA.transpose() << endl;


		Eigen::Vector3d translation = relative_pose.translation();
		cout << translation.transpose() << endl;
		fout <<  translation[0]  << " " << translation[1]  << " " << translation[2] << " "  << eA[0] << " " << eA[1]  << " " << eA[2] << " "<< endl;

		cout << poses[i].matrix() << endl;
		cout << poses[i].inverse().matrix() << endl;
		cout << "-------------------------------------------------------------" << endl;
	}
	*/

	// 写入poses文件
	for (size_t i = 1; i < poses.size(); ++i){
		relative_pose = poses[i] * tgt_poses.inverse();
		ofstream fout((relative_pose_file % i).str());
		// rx, ry, rz
		Eigen::Vector3d eulerAngles = relative_pose.rotationMatrix().eulerAngles(0, 1, 2);
		Eigen::Vector3d translation = relative_pose.translation();
		fout << translation[0] << " " << translation[1] << " " << translation[2] << " " << eulerAngles[0] << " " << eulerAngles[1] << " " << eulerAngles[2];
	}

	// 写入intrinsics文件
	for (size_t i = 1; i < poses.size(); ++i){
		ofstream fout((intrinsics_file % i).str());
		fout << 518.0 << " " << 0	  << " " << 325.5 << " " 
			 << 0	  << " " << 519.0 << " " << 253.5 << " " 
			 << 0	  << " " << 0	  << " " << 1;

	}

	return 0;

}

