#pragma once
#include "opencv2/opencv.hpp"

class Things
{
private:
	int _x;
	int _y;
	cv::Mat _image;
public:
	Things();
	Things(int x, int y, cv::Mat image);
	~Things();
	int getX();
	int getY();
	void setX(int x);
	void setY(int x);
	cv::Mat getImage();
	void setImage(cv::Mat image);
};