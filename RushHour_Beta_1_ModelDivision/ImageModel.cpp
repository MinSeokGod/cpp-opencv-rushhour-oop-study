#include "ImageModel.h"
#include <opencv2/opencv.hpp>
using namespace cv;

ImageModel::ImageModel() {
	loadImage(); //이미지 불러오는걸 메소드로 구현한 이유 :  
	//컨트롤러에서 이미지 모델이 생성 될 때 자동으로 이미지를 호출함 추후에 이미지를 선택 할 수 있게 변경 가능
}

void ImageModel::loadImage() {
	_roadImage = imread("res\\Images\\_RoadImage.png");
	_backGroundImage = imread("res\\Images\\BackGounrd.png");
	_playerCarImage = imread("res\\Images\\_PlayerCarImage.png", IMREAD_UNCHANGED);
	_exitPointImage = imread("res\\Images\\_ExitPointImage.png", IMREAD_UNCHANGED);
	_carXImage = imread("res\\Images\\_CarXImage.png", IMREAD_UNCHANGED);
	_carYImage = imread("res\\Images\\_CarYImage.png", IMREAD_UNCHANGED);
	_truckXImage = imread("res\\Images\\_TruckXImage.png", IMREAD_UNCHANGED);
	_truckYImage = imread("res\\Images\\_TruckYImage.png", IMREAD_UNCHANGED);
	_Gold = imread("res\\Images\\Gold.png", IMREAD_UNCHANGED);
	_Sliver = imread("res\\Images\\Sliver.png", IMREAD_UNCHANGED);
	_Bronze = imread("res\\Images\\Bronze.png", IMREAD_UNCHANGED);
	_Fail = imread("res\\Images\\Fail.png", IMREAD_UNCHANGED);
	reSizeImage();
}

void ImageModel::reSizeImage() {
	resize(_roadImage, _roadImage, Size(TILESIZE, TILESIZE));
	resize(_exitPointImage, _exitPointImage, Size(TILESIZE, TILESIZE));
	resize(_playerCarImage, _playerCarImage, Size(TILESIZE, TILESIZE * 2));;
	resize(_carXImage, _carXImage, Size(TILESIZE * 2, TILESIZE));
	resize(_carYImage, _carYImage, Size(TILESIZE, TILESIZE * 2));
	resize(_truckXImage, _truckXImage, Size(TILESIZE * 3, TILESIZE));
	resize(_truckYImage, _truckYImage, Size(TILESIZE, TILESIZE * 3));
	resize(_backGroundImage, _backGroundImage, Size(MAPSIZE, MAPSIZE));
	resize(_Gold, _Gold, Size(TILESIZE, TILESIZE));
	resize(_Sliver, _Sliver, Size(TILESIZE, TILESIZE));
	resize(_Bronze, _Bronze, Size(TILESIZE, TILESIZE));
	resize(_Fail, _Fail, Size(TILESIZE, TILESIZE));
}

int ImageModel::getTileSize() {
	return TILESIZE;
}
int ImageModel::getMapLength() {
	return MAPLENGTH;
}
int ImageModel::getMapSize() {
	return MAPSIZE;
}
Mat ImageModel::getRoad() {
	return _roadImage;
}
Mat ImageModel::getPlayerCarImage() {
	return _playerCarImage;
}
Mat ImageModel::getExitRoadImage() {
	return _exitPointImage;
}
Mat ImageModel::getCarXImage() {
	return _carXImage;
}
Mat ImageModel::getCarYImage() {
	return _carYImage;
}
Mat ImageModel::getTruckXImage() {
	return _truckXImage;
}
Mat ImageModel::getTruckYImage() {
	return _truckYImage;
}
Mat ImageModel::getBackGroundImage() {
	return _backGroundImage;
}
Mat ImageModel::getGoldImage() {
	return _Gold;
}
Mat ImageModel::getSliverImage() {
	return _Sliver;
}
Mat ImageModel::getBronzeImage() {
	return _Bronze;
}
Mat ImageModel::getFailImage() {
	return _Fail;
}