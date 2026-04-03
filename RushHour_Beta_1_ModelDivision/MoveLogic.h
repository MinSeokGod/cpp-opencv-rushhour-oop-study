#pragma once
#include "PlayerVehicle.h"
#include "OtherVehicle.h"
#include "WorldEditor.h"

class MoveLogic
{
private:
	WorldEditor* _worldEditor;
public:
	MoveLogic(WorldEditor* worldEditor);
	bool checkMouseInsidePlayerCar(int mouseX, int mouseY, PlayerVehicle* playerCar);
	bool checkMouseInsideOtherCar(int mouseX, int mouseY, OtherVehicle* otherCar);
	void MovePlayer(int mouseX, int mouseY, PlayerVehicle* playerCar, int mapSize);
	void MoveOther(int mouseX, int mouseY, OtherVehicle* otherCar, int mapSize);
	bool checkVehicleCollision(int x, int y, PlayerVehicle* player);
	bool checkOtherVehicleCollision(int x, int y, int index);
	bool checkFinish(int x, int y);
};