#pragma once
#include <opencv2/opencv.hpp>

class ImageModel
{
private:
	const int TILESIZE = 100;
	const int MAPLENGTH = 6;
	const int MAPSIZE = TILESIZE * MAPLENGTH;
	cv::Mat _playerCarImage;
	cv::Mat _carXImage;
	cv::Mat _carYImage;
	cv::Mat _truckXImage;
	cv::Mat _truckYImage;
	cv::Mat _exitPointImage;
	cv::Mat _roadImage;
	cv::Mat _backGroundImage;
	cv::Mat _Gold;
	cv::Mat _Sliver;
	cv::Mat _Bronze;
	cv::Mat _Fail;
public:
	ImageModel();
	void loadImage();
	void reSizeImage();
	int getTileSize();
	int getMapLength();
	int getMapSize();
	cv::Mat getRoad();
	cv::Mat getExitRoadImage();
	cv::Mat getPlayerCarImage();
	cv::Mat getCarXImage();
	cv::Mat getCarYImage();
	cv::Mat getTruckXImage();
	cv::Mat getTruckYImage();
	cv::Mat getBackGroundImage();
	cv::Mat getGoldImage();
	cv::Mat getSliverImage();
	cv::Mat getBronzeImage();
	cv::Mat getFailImage();
	//void loadImage(사용자 선택 값); 사용자의 자동차 이미지를 선택 가능함.
};