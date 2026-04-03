#pragma once
#include "Things.h"
#include "opencv2/opencv.hpp"


class PlayerVehicle : public Things
{
public:
	PlayerVehicle(int x, int y, cv::Mat image);
};