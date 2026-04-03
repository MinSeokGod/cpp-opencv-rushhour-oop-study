#include "Controller.h"

using namespace cv;
using namespace std;

Controller::Controller() {
	_imageModel = new ImageModel();
	_worldEditor = new WorldEditor(_imageModel);
	_moveLogic = new MoveLogic(_worldEditor);
	_gameView = new GameView(_worldEditor, _imageModel->getTileSize(), _imageModel->getMapLength(), _imageModel->getMapSize());
	isPlayerDrag = false;
	isOtherDrag = false;
	index = -1;
	isGameFinished = false;
	isGameStage = 0;
	isGameStageMax = 3; //맵의 개수에 맞게 수정해줄 것!!
}

void Controller::initGame() { //초기 게임만 세팅해줌 난이도 선택 기능 추가 구현 가능
	//1. 맵 초기화
	_worldEditor->LoadMap("res\\Map\\map" + to_string(isGameStage) + ".txt");
}

void Controller::startGame() {
	//1. View에 Model의 이미지 전달 및 화면 그리기 시작
	_gameView->DrawGame(_imageModel->getRoad(), _imageModel->getBackGroundImage(), isGameFinished, _imageModel->getTileSize());
	HandleMouse();

	while (1) {
		if (!_moveLogic->checkFinish(_worldEditor->getPlayer()->getX(), _worldEditor->getPlayer()->getY())) {
			int key = waitKey(200); //200에 한번씩 검사하며 입력을 기다림 (loop 역할)
			if (key == 27) //"ESC" 입력시 종료
				exit(0);
		}
		else { //스테이지가 클리어된 경우에
			if (!isGameFinished) {
				isGameStage++; //스테이지 값 상승
				if (isGameStage == isGameStageMax) {
					ClearGame();
				}
				else {
					initGame(); //게임 초기화
					startGame();
				}
				isGameFinished = true;  // waitKey의 동작이 너무 빨라서 isGameStage++가 너무 빠르게 실행되는 문제가 발생 그러므로 일종의 트리거를 줌.
			}
		}

	}
}

void Controller::ClearGame() {
	isGameFinished = true; //클리어 되었음을 gameView에게 알려야함.
	_gameView->DrawGame(_imageModel->getRoad(), _imageModel->getBackGroundImage(), isGameFinished, _imageModel->getTileSize());
	while (1) {
		int key = waitKey(200);
		if (key == 27) {
			exit(0);
		}
	}
}

void Controller::onMouse(int event, int x, int y, int flags, void* userdata) { //onMouse는 openCv 라이브러리의 특성으로 static으로 선언되어야 한다.
	Controller* controller = static_cast<Controller*>(userdata); //이때 onMouse는 static이므로 Controller에 위치해 있지만 Controller를 모른다. (정적 멤버 함수는 특정 인스턴스에 종속 되지 않음)
	if (controller) {// 그렇기에 userdata로 들어온 Controller를 통해서 Controller가 누군지 알려주고 그 안에 있는  onMouseCallBack을 호출하여 Controller가 알고 있는 _worldEditor 등등에 접근 할 수 있도록 한다.
		controller->onMouseCallBack(event, x, y, flags);
	}
}

void Controller::onMouseCallBack(int event, int x, int y, int flags) {
	switch (event) {
	case EVENT_LBUTTONDOWN:
		if (_moveLogic->checkMouseInsidePlayerCar(x, y, _worldEditor->getPlayer())) {
			isPlayerDrag = true;
		}
		else {
			for (int i = 0; i < _worldEditor->getSize(); i++) {
				if (_moveLogic->checkMouseInsideOtherCar(x, y, _worldEditor->_otherThings[i])) {
					isOtherDrag = true;
					index = i;
					break;
				}
			}
		}
		break;
	case EVENT_LBUTTONUP:
		isPlayerDrag = false;
		isOtherDrag = false;
		break;
	case EVENT_MOUSEMOVE:
		if (isPlayerDrag) {
			if (!(_moveLogic->checkVehicleCollision(x, y, _worldEditor->getPlayer()))) {
				_moveLogic->MovePlayer(x, y, _worldEditor->getPlayer(), _imageModel->getMapLength());

			}
		}
		else if (isOtherDrag) {
			if (index != -1) {
				if (!(_moveLogic->checkOtherVehicleCollision(x, y, index))) {
					_moveLogic->MoveOther(x, y, _worldEditor->_otherThings[index], _imageModel->getMapLength());
				}
			}
		}
		_gameView->DrawGame(_imageModel->getRoad(), _imageModel->getBackGroundImage(), isGameFinished, _imageModel->getTileSize());
		break;
	}
}

void Controller::HandleMouse() {
	setMouseCallback("RushHour Game", onMouse, this);
}