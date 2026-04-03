#pragma once
#include "MoveLogic.h"
#include "ImageModel.h"
#include "GameView.h"
#include "WorldEditor.h"
#include <opencv2/opencv.hpp>
#include <conio.h>
#include <iostream>

class Controller
{
private:
	GameView* _gameView;
	ImageModel* _imageModel;
	MoveLogic* _moveLogic;
	WorldEditor* _worldEditor;
	bool isPlayerDrag;
	bool isOtherDrag;
	int index;
	bool isGameFinished;
	int isGameStage;
	int isGameStageMax;
public:
	Controller();
	void initGame();
	void startGame();
	void ClearGame();
	void HandleMouse();
	static void onMouse(int event, int x, int y, int flags, void* userdata);
	void onMouseCallBack(int event, int x, int y, int flags);
};