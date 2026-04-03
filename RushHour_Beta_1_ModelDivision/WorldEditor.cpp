#include "WorldEditor.h"
using namespace std;

WorldEditor::WorldEditor(ImageModel* imageModel) {
	_imageModel = imageModel;
}

void WorldEditor::LoadMap(const string& mapFileName) {
	ifstream file(mapFileName);
	if (!file.is_open()) {
		cerr << "에러: 맵 파일을 열 수 없습니다." << endl;
		return;
	}

	vector<vector<int>> mapData;
	int row = 0;
	int col = 0;

	while (!file.eof()) {
		string line;
		getline(file, line);

		col = max(col, static_cast<int>(line.length()));

		vector<int> rowData;
		for (char& c : line) {
			rowData.push_back(c - '0');
		}

		if (!rowData.empty()) {
			mapData.push_back(rowData);
			++row;
		}
	}
	file.close();
	size = 0; //다음 스테이지를 불러오기 위해서...
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			if (mapData[i][j] == 1) {
				// 플레이어
				_player = new PlayerVehicle(j, i, _imageModel->getPlayerCarImage());
			}
			else if (mapData[i][j] == 2) {
				// 탈출구
				_exitPoint = new ExitPoint(j, i, _imageModel->getExitRoadImage());
			}
			else if (mapData[i][j] == 3) {
				_otherThings[size++] = new OtherVehicle(j, i, _imageModel->getCarXImage());
			}
			else if (mapData[i][j] == 4) {
				_otherThings[size++] = new OtherVehicle(j, i, _imageModel->getCarYImage());
			}
			else if (mapData[i][j] == 5) {
				_otherThings[size++] = new OtherVehicle(j, i, _imageModel->getTruckXImage());
			}
			else if (mapData[i][j] == 6) {
				_otherThings[size++] = new OtherVehicle(j, i, _imageModel->getTruckYImage());
			}
		}
	}
}

PlayerVehicle* WorldEditor::getPlayer() {
	return _player;
}
ExitPoint* WorldEditor::getExit() {
	return _exitPoint;
}

int WorldEditor::getSize() {
	return size;
}