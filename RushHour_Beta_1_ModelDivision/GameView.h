#pragma once
#include <opencv2/opencv.hpp>
#include <chrono>
#include "Things.h"
#include "WorldEditor.h"
using namespace std::chrono;

class GameView
{
private:
	WorldEditor* _worldEditor;
	cv::Mat map;
	high_resolution_clock::time_point startTime;
public:
	GameView(WorldEditor* worldEditor, int tileSize, int mapLength, int mapSize);
	void DrawGame(cv::Mat roadImage, cv::Mat backGroundImage, bool isGameFinished, int TileSize);
	void DrawTile(cv::Mat roadImage);
	void DrawExit(int TileSize);
	void DrawObj(int TileSize);
	void DrawPlayer(int TileSize);
	void DrawMeDal(cv::Mat grade);
};