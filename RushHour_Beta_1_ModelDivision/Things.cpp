#include "Things.h"

Things::Things() {
}
Things::Things(int x, int y, cv::Mat image) {
	_x = x;
	_y = y;
	_image = image;
}
Things::~Things(){}
int Things::getX() {
	return _x;
}
int Things::getY() {
	return _y;
}
void Things::setX(int x) {
	_x = x;
}
void Things::setY(int y) {
	_y = y;
}
cv::Mat Things::getImage() {
	return _image;
}
void Things::setImage(cv::Mat image) {
	_image = image;
}