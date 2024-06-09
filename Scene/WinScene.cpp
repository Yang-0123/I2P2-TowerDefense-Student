#include <functional>
#include <string>
#include <chrono>
#include <ctime>

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/Image.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "PlayScene.hpp"
#include "Engine/Point.hpp"
#include "WinScene.hpp"
#include "UI/Component/InputBox.hpp"
#include <fstream>
#include <iostream>
Engine::InputBox* inputBox;
void WinScene::Initialize() {
	ticks = 0;
	int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
	int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
	int halfW = w / 2;
	int halfH = h / 2;
	AddNewObject(new Engine::Image("win/benjamin-sad.png", halfW, halfH, 0, 0, 0.5, 0.5));
	AddNewObject(new Engine::Label("You Win!", "pirulen.ttf", 48, halfW, halfH / 4 -10, 255, 255, 255, 255, 0.5, 0.5));

	// 创建输入框对象并添加到场景中
    inputBox = new Engine::InputBox("pirulen.ttf", 24, halfW, halfH / 4 +50, 400, 40, 255, 255, 255, 255, 255, 255, 255, 255, false, "Enter name here...", 0.5, 0.5);
    AddNewControlObject(inputBox);

	Engine::ImageButton* btn;
	btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
	btn->SetOnClickCallback(std::bind(&WinScene::BackOnClick, this, 2));
	AddNewControlObject(btn);
	AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
	bgmId = AudioHelper::PlayAudio("win.wav");
}
void WinScene::Terminate() {
	IScene::Terminate();
	AudioHelper::StopBGM(bgmId);
}
void WinScene::Update(float deltaTime) {
	ticks += deltaTime;
	if (ticks > 4 && ticks < 100 &&
		dynamic_cast<PlayScene*>(Engine::GameEngine::GetInstance().GetScene("play"))->MapId == 2) {
		ticks = 100;
		bgmId = AudioHelper::PlayBGM("happy.ogg");
	}
}
void WinScene::BackOnClick(int stage) {
	int lives;
	std::ifstream file("../Resource/lives.txt"); 
    if (file.is_open()) {
		file >> lives;
        file.close();
        std::cout << "Text written to scoreboard.txt: " << inputBox->GetText() << std::endl;
    } else {
        // 如果无法打开文件，输出错误信息
        std::cerr << "Unable to open scoreboard.txt" << std::endl;
    }

	std::ofstream file2("../Resource/scoreboard.txt", std::ios::app); // 打开文件并追加写入
    if (file2.is_open()) {
        // 将 inputBox 的文本写入文件
		auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        file2 << inputBox->GetText() << " " << lives << " "<<std::ctime(&now)<<std::endl;
        // 关闭文件
        file2.close();
        std::cout << "Text written to scoreboard.txt: " << inputBox->GetText() << " " << lives << " "<<std::ctime(&now) << std::endl;
    } else {
        // 如果无法打开文件，输出错误信息
        std::cerr << "Unable to open scoreboard.txt" << std::endl;
    }
    // Change to select scene.
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}
