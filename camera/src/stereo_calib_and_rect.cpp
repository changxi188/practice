#include "stereo_calib_and_rect.h"


using namespace std;
using namespace cv;
bool StereoCalibAndRect::readStringList(){
	list_.resize(0);
	cv::FileStroage fs(filename_, FileStorage::READ);
	if (!fs.isOpened())
		return false;
	cv::FileNode n = fs.getFirstTopLevelNode();
	if (n.type() != cv::FileNode::SEQ)
		return false;
	//cv::FileNodeIterator it = n.begin(), it_end = n.end();
	for (cv::FileNodeIterator it = n.begin(); it != n.end(); ++it){
		list_.push_back((string)*it);
	}
	return true;
}

void StereoCalibAndRect::calcChessboardCorners(){
	coners_.resize(0);
	for (int i = 0; i < boardSize_.height; i++){
		for (int j = 0; j < boardSize_.width; ++j){
			corners_.push_back(Point3f(j * chessboard_square_size_, i * chessboard_square_size_, 0));
		}
	}
}
