# cpp-opencv-RushHour

## About
* 기간 : 2학년 2학기 기말고사 기간 (대략 1~2주)
* 인원 : 개인 프로젝트
* 목적 : 객체지향 프로그래밍 수업 기말 대체 과제 및 첫 c++ 프로젝트
* 사용 환경 : visual studio 및 opencv 라이브러리

## Requirements
- OpenCV 설치 필요
- include/lib 경로 설정 필요

## 프로젝트 소개
RushHour는 차량이 한 방향(가로 또는 세로)으로만 이동할 수 있는 퍼즐 게임으로,
플레이어의 차량을 출구까지 이동시키는 것을 목표로 합니다.
본 프로젝트는 cpp를 처음 사용하여 진행한 프로젝트로,
객체 지향 프로그래밍과 MVC구조 및 기본적인 게임 로직 구현을 경험하는 데 중점을 두었습니다.

## 주요 기능
* 차량 이동 로직 구현 (퍼즐 게임에 맞게 가로/세로 방향 제한)
* 차량 간 충돌 판정
* 탈출구 도달 시 게임 종료 처리
* 타이머 기능

## 게임 로직 (간단히)
* 모든 차량은 초기 방향(가로/세로)에 따라 한 축으로만 이동 가능
* 이동 시:
  * 맵 범위를 벗어나는지 검사
  * 다른 차량과의 충돌 여부 검사
* 플레이어 차량이 출구 좌표에 도달하면 게임 종료
* 이동할 때마다 이동 횟수 증가 및 타이머 동작

## 설계 구조 : MVC
* Model
  * 차량 객체 (위치, 방향, 길이 등)
  * 맵 상태 (차량 배치 정보)
 * View
  * 게임 화면 출력
  * 사용자 인터페이스
* Controller
  * 사용자 입력 처리
  * 차량 이동 및 게임 상태 업데이트
  * 게임 시작/종료 제어

## 개발 과정
- 사전에 다이어그램 구성을 먼저 함
<img width="2264" height="916" alt="image" src="https://github.com/user-attachments/assets/9a669c3c-eea0-4ca2-a359-3915f5ac7675" />

- 기존 메인메뉴 화면을 만들었지만 각종 버그로 인하여 삭제
<img width="600" height="600" alt="image" src="https://github.com/user-attachments/assets/60cf15e4-7082-4d0e-91ba-f7fe61aa2bc3" />

- 게임 실행 시 화면 (빨간 차를 깃발까지 이동시켜야함)
<img width="600" height="600" alt="image" src="https://github.com/user-attachments/assets/6e68dabb-016d-4e2c-bf01-eadcb4e548e2" />

- 게임 실행 시 화면 (빨간 차를 깃발까지 이동시켜야함)
<img width="600" height="600" alt="image" src="https://github.com/user-attachments/assets/9a3b7fc8-9bd1-40ce-9cc2-58e5170f1ad8" />

## 느낀점이자 발전한 점
- 첫 CPP 프로젝트이자 두번째 러시아워 프로젝트, 언어 자체에 대한 이해와 함께
  객체 지향 설계와 mvc 구조를 더욱 능숙하게 신경 쓸 수 있었습니다.

- Git을 사용하지 않아 버전 관리를 체계적으로 하지 못했습니다. 
  하지만, 이전 java-rushhour 개발을 토대로 사전 클래스 설계 작업의 중요성을 깨달았기에
  의존성을 줄이고 코드의 간결함과 가독성, 유지보수성 등에 더욱 많은 발전이 있었습니다.

- 또한, 이전 java-rushhour에서 아쉬웠던 점인 map 생성 방식에 대해서 이전에는 직접 장애물의 위치를 하나한 생성하였지만
  해당 프로젝트에서는 .txt 파일에 맵을 저장하여 txt 파일을 불러와서 맵 생성과 장애물 배치를 하는 기능을 추가하였습니다.
