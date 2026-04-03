#pragma once
#include "Things.h"
#include "opencv2/opencv.hpp"

class OtherVehicle : public Things
{
public:
	OtherVehicle(int x, int y, cv::Mat imagz);
};