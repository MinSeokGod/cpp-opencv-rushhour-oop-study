#include "GameView.h"
#include "opencv2/opencv.hpp"
#include "WorldEditor.h"
using namespace std;
using namespace cv;
using namespace chrono;

GameView::GameView(WorldEditor* worldEditor, int tileSize, int mapLength, int mapSize) {
	_worldEditor = worldEditor;
	map = Mat::zeros(mapSize, mapSize, CV_8UC3);
	map.setTo(Scalar(255, 255, 255));
	startTime = high_resolution_clock::now();
}

void GameView::DrawGame(cv::Mat roadImage, cv::Mat backGroundImage, bool isGameFinished, int TileSize) {
	auto currentTime = high_resolution_clock::now();
	auto elapsedTime = duration_cast<seconds>(currentTime - startTime).count();
	int remainingTime = max(0, 180 - static_cast<int>(elapsedTime));  // 남은 시간 계산

	if (isGameFinished) {
		string gradeImage;

		if (elapsedTime < 60) {
			gradeImage = "res\\Images\\Gold.png";
		}
		else if (elapsedTime < 120) {
			gradeImage = "res\\Images\\Sliver.png";
		}
		else if (elapsedTime < 180) {
			gradeImage = "res\\Images\\Bronze.png";
		}
		else {
			gradeImage = "res\\Images\\Fail.png";
		}
		DrawTile(backGroundImage);
		Mat gradeImageMat = imread(gradeImage, IMREAD_UNCHANGED);
		resize(gradeImageMat, gradeImageMat, Size(200, 200));
		DrawMeDal(gradeImageMat);
	}
	else {
		DrawTile(roadImage);
		DrawExit(TileSize);
		DrawPlayer(TileSize);
		DrawObj(TileSize);
		putText(map, "Time: " + to_string(remainingTime) + "s", Point(10, 30), FONT_HERSHEY_TRIPLEX, 1, Scalar(0, 0, 255), 2);
	}
	imshow("RushHour Game", map);
}

void GameView::DrawMeDal(Mat grade) {
	Rect roi(200, 100, grade.cols, grade.rows);  // 위치 조절 가능
	Mat imageROI = map(roi);

	for (int i = 0; i < grade.rows; ++i) {
		for (int j = 0; j < grade.cols; ++j) {
			const Vec4b& pixel = grade.at<Vec4b>(i, j);
			if (pixel[3] > 0) {
				Vec3b& backgroundPixel = imageROI.at<Vec3b>(i, j);
				for (int c = 0; c < 3; ++c) {
					backgroundPixel[c] = pixel[c] * (pixel[3] / 255.0) + backgroundPixel[c] * (1.0 - pixel[3] / 255.0);
				}
			}
		}
	}
}

void GameView::DrawTile(Mat roadImage) {
	for (int i = 0; i < map.rows; i += roadImage.rows) {
		for (int j = 0; j < map.cols; j += roadImage.cols) {
			Rect tile(j, i, roadImage.cols, roadImage.rows); //타일 사각형 생성 (가로 100 세로 100)
			Mat imageROI = map(tile);
			roadImage.copyTo(imageROI);
		}
	}
}

void GameView::DrawExit(int TileSize) {
	Mat	bufferImage = _worldEditor->getExit()->getImage();
	Rect car(_worldEditor->getExit()->getX() * TileSize, _worldEditor->getExit()->getY() * TileSize, bufferImage.cols, bufferImage.rows);
	Mat obj = map(car);

	for (int i = 0; i < bufferImage.rows; ++i) {
		for (int j = 0; j < bufferImage.cols; ++j) {
			const Vec4b& pixel = bufferImage.at<Vec4b>(i, j);
			if (pixel[3] > 0) {
				Vec3b& mapPixel = obj.at<Vec3b>(i, j);
				for (int c = 0; c < 3; ++c) {
					mapPixel[c] = pixel[c] * (pixel[3] / 255.0) + mapPixel[c] * (1.0 - pixel[3] / 255.0);
				}
			}
		}
	}
}

void GameView::DrawObj(int TileSize) {
	for (int i = 0; i < _worldEditor->getSize(); i++) {
		if (_worldEditor->_otherThings[i] != NULL) {
			Mat	bufferImage = _worldEditor->_otherThings[i]->getImage();
			Rect car(_worldEditor->_otherThings[i]->getX() * TileSize, _worldEditor->_otherThings[i]->getY() * TileSize, bufferImage.cols, bufferImage.rows);
			Mat obj = map(car);

			for (int i = 0; i < bufferImage.rows; ++i) {
				for (int j = 0; j < bufferImage.cols; ++j) {
					const Vec4b& pixel = bufferImage.at<Vec4b>(i, j);
					if (pixel[3] > 0) {
						Vec3b& mapPixel = obj.at<Vec3b>(i, j);
						for (int c = 0; c < 3; ++c) {
							mapPixel[c] = pixel[c] * (pixel[3] / 255.0) + mapPixel[c] * (1.0 - pixel[3] / 255.0);
						}
					}
				}
			}
		}
	}
}


void GameView::DrawPlayer(int TileSize) {
	Mat	bufferImage = _worldEditor->getPlayer()->getImage(); //플레이어의 이미지를 저장함
	Rect car(_worldEditor->getPlayer()->getX() * TileSize, _worldEditor->getPlayer()->getY() * TileSize, bufferImage.cols, bufferImage.rows); //그려야할 좌표와 크기를 구함
	Mat obj = map(car);

	for (int i = 0; i < bufferImage.rows; ++i) {
		for (int j = 0; j < bufferImage.cols; ++j) {
			const Vec4b& pixel = bufferImage.at<Vec4b>(i, j);
			if (pixel[3] > 0) {
				Vec3b& mapPixel = obj.at<Vec3b>(i, j);
				for (int c = 0; c < 3; ++c) {
					mapPixel[c] = pixel[c] * (pixel[3] / 255.0) + mapPixel[c] * (1.0 - pixel[3] / 255.0);
				}
			}
		}
	}
}
