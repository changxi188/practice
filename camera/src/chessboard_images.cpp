#include <boost/format.hpp>
#include "chessboard_images.h"

//ChessboardImages::ChessboardImages


cv::Mat ChessboardImages::nextImage(){
	boost::format left_fmt("%s/data/left_img/left_img_%2d");
	boost::format right_fmt("%s/data/right_img/right_img_%2d");
	cv::Mat left_chessboard, right_chessboard;
	left_chessboard = cv::imread((left_fmt % dataset_path_ % current_img_index_).str());
	right_chessboard = cv::imread((right_fmt % dataset_path_ % current_img_index_).str());

	if (left_chessboard.data == nullptr || right_chessboard.data == nullptr){
		std::cout << "cannot open chessboard image" << std::endl;
		
		return nullptr;
	}
	current_img_index++;
}

