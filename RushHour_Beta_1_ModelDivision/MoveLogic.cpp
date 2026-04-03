#include "MoveLogic.h"
#include "OtherVehicle.h"
#include <opencv2/opencv.hpp>
using namespace cv;

MoveLogic::MoveLogic(WorldEditor* worldEditor) {
	_worldEditor = worldEditor;
}

bool MoveLogic::checkMouseInsidePlayerCar(int mouseX, int mouseY, PlayerVehicle* playerCar) {
	int playerCarX = playerCar->getX();// 플레이어의 자동차 좌표
	int playerCarY = playerCar->getY();
	int playerCarWidth = playerCar->getImage().cols;// 플레이어의 자동차 크기
	int playerCarHeight = playerCar->getImage().rows;
	// 마우스 클릭이 플레이어의 자동차 내부에 있는지 확인
	return mouseX >= playerCarX * 100 && mouseX <= (playerCarX * 100) + playerCarWidth &&
		mouseY >= playerCarY * 100 && mouseY <= (playerCarY * 100) + playerCarHeight;
}

bool MoveLogic::checkMouseInsideOtherCar(int mouseX, int mouseY, OtherVehicle* otherCar) {
	int otherCarX = otherCar->getX();
	int otherCarY = otherCar->getY();
	int otherCarWidth = otherCar->getImage().cols;
	int otherCarHeight = otherCar->getImage().rows;

	return mouseX >= otherCarX * 100 && mouseX <= (otherCarX * 100) + otherCarWidth &&
		mouseY >= otherCarY * 100 && mouseY <= (otherCarY * 100) + otherCarHeight;
}

void MoveLogic::MovePlayer(int mouseX, int mouseY, PlayerVehicle* playerCar, int mapLength) {
	int newPlayerX = mouseX / 100;
	int newPlayerY = mouseY / 100;
	//맵 안에서만 움직이게
	if (newPlayerX >= 0 && newPlayerX + (playerCar->getImage().cols / 100) <= mapLength && 
		newPlayerY >= 0 && newPlayerY + (playerCar->getImage().rows / 100) <= mapLength) {
		//너비가 더 길다? = 가로축 차라는 뜻
		if (playerCar->getImage().cols > playerCar->getImage().rows) {
			playerCar->setX(newPlayerX);
		}
		if (playerCar->getImage().cols < playerCar->getImage().rows) {
			playerCar->setY(newPlayerY);
		}
	}
}

void MoveLogic::MoveOther(int mouseX, int mouseY, OtherVehicle* otherCar, int mapLength) {
	int newOtherX = mouseX / 100;
	int newOtherY = mouseY / 100;

	if (newOtherX >= 0 && newOtherX + (otherCar->getImage().cols / 100) <= mapLength &&
		newOtherY >= 0 && newOtherY + (otherCar->getImage().rows / 100) <= mapLength) {
		if (otherCar->getImage().cols > otherCar->getImage().rows) {
			otherCar->setX(newOtherX);
		}
		if (otherCar->getImage().cols < otherCar->getImage().rows) {
			otherCar->setY(newOtherY);
		}
	}
}

bool MoveLogic::checkVehicleCollision(int x, int y, PlayerVehicle* player) {
	int newMouseX = x / 100;
	int newMouseY = y / 100;
	// 충돌 여부 확인
	for (int i = 0; i < _worldEditor->getSize(); i++) {
		if ((newMouseX < (_worldEditor->_otherThings[i]->getX() + _worldEditor->_otherThings[i]->getImage().cols / 100) &&
			(newMouseX + player->getImage().cols / 100) > _worldEditor->_otherThings[i]->getX() &&
			newMouseY < (_worldEditor->_otherThings[i]->getY() + _worldEditor->_otherThings[i]->getImage().rows / 100) &&
			(newMouseY + player->getImage().rows / 100) > _worldEditor->_otherThings[i]->getY())){
			return true;
		}
	}
	return false;
}

bool MoveLogic::checkOtherVehicleCollision(int x, int y, int index) {
	int newMouseX = x / 100;
	int newMouseY = y / 100;
	// 충돌 여부 확인 다른 차들 조사해서 통과하면
	for (int i = 0; i < _worldEditor->getSize(); i++) {
		if (i != index) {
			if ((newMouseX < (_worldEditor->_otherThings[i]->getX() + _worldEditor->_otherThings[i]->getImage().cols / 100) &&
				(newMouseX + _worldEditor->_otherThings[index]->getImage().cols / 100) > _worldEditor->_otherThings[i]->getX() &&
				newMouseY < (_worldEditor->_otherThings[i]->getY() + _worldEditor->_otherThings[i]->getImage().rows / 100) &&
				(newMouseY + _worldEditor->_otherThings[index]->getImage().rows / 100) > _worldEditor->_otherThings[i]->getY())) {
				return true;
			}
		}
	}//플레이어 차랑도 검사
	if ((newMouseX < (_worldEditor->getPlayer()->getX() + _worldEditor->getPlayer()->getImage().cols / 100) &&
		(newMouseX + _worldEditor->_otherThings[index]->getImage().cols / 100) > _worldEditor->getPlayer()->getX() &&
		newMouseY < (_worldEditor->getPlayer()->getY() + _worldEditor->getPlayer()->getImage().rows / 100) &&
		(newMouseY + _worldEditor->_otherThings[index]->getImage().rows / 100) > _worldEditor->getPlayer()->getY())) { 
		return true;
	}
	return false;
}

bool MoveLogic::checkFinish(int x, int y) {
	if ((_worldEditor->getPlayer()->getX() == _worldEditor->getExit()->getX()) && (_worldEditor->getPlayer()->getY() == _worldEditor->getExit()->getY()))
		return true;
	else
		return false;
}