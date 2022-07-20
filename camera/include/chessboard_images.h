#pragma once
#ifndef __CHESSBOARD_IMAGES_H__
#define __CHESSBOARD_ImAGES_H__

#include <iostream>
#include <opencv2/core/core.hpp>

class ChessboardImages{
public:
	typedef std::shared_ptr<ChessboardImage> Ptr;
	ChessboardImage(const std::string& dataset_path) : dataset_path_(dataset_path) {}


	cv::Mat nextImage();

private:
	std::string dataset_path_;

	int current_img_index = 0;
};


#endif


