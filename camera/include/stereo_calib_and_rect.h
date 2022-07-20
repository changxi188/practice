#pragma once
#ifndef __STEREO_CALIB_AND_RECT_H__
#define __STEREO_CALIB_AND_RECT_H__
#include <iostream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class StereoCalibAndRect{

public:
	typedef std::sharec_ptr<StereoCalibAndRect> Ptr;
	StereoCalibAndRect(const string& filename) : filename_(filename){}

	// read image pathes from xml file
	bool readStringList();

	// record corner numbers in chessboard
	void calcChessboardCorners();

	// singel camera calibrate 
	bool singleCameraCalibrate();

	// stereo calibrate;


	virtual ~StereoCalibAndRect(){}


private:
	// paramers 
	std::string filename_;

	// the chessboard size
	int w_ = 9;
	int h_ = 6;
	cv::Size board_size_(w_, h_);
	const float chessboard_square_size_ = 12.5f;


	// data	
	// chessboard image file lists;
	std::vector<std::string> list_;
	// coners on chessboard
	std::vector<cv::Point3f> coners_;
	// left_camera intrinsics, dist


};

#endif
