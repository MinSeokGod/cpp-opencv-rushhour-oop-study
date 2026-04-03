#pragma once
#include "Things.h"
#include "ExitPoint.h"
#include "PlayerVehicle.h"
#include "OtherVehicle.h"
#include "ImageModel.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

class WorldEditor
{
private:
	PlayerVehicle* _player;
	ExitPoint* _exitPoint;
	ImageModel* _imageModel;
	int size;
public:
	WorldEditor(ImageModel* imageModel);
	OtherVehicle* _otherThings[10];
	void LoadMap(const std::string& mapFileName);
	PlayerVehicle* getPlayer();
	ExitPoint* getExit();
	int getSize();
};