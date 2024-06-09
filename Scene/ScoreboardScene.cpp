#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "ScoreboardScene.hpp"

void ScoreboardScene::Initialize() {
    index = 1;
    LoadScoreboardData();
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(new Engine::Label("Scoreboard", "pirulen.ttf", 60, halfW, 100, 0, 255, 0, 255, 0.5, 0.5));
    //AddNewObject(new Engine::Label("Name         Lives", "pirulen.ttf", 40, halfW, 165, 0, 255, 0, 255, 0.5, 0.5));
    Engine::ImageButton *btn;

    // Previous Page Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 650, halfH * 3 / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::PrevPageOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Prev Page", "pirulen.ttf", 48, halfW - 450, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

    // Back Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW-150, halfH * 3 / 2, 300, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::BackOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));

    // Next Page Button
    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW + 250, halfH * 3 / 2, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreboardScene::NextPageOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Next page", "pirulen.ttf", 48, halfW + 450, halfH * 3 / 2 + 50, 0, 0, 0, 255, 0.5, 0.5));
    DisplayScoreboardData(index);
}

void ScoreboardScene::LoadScoreboardData() {
    std::ifstream file("../Resource/scoreboard.txt");
    if (!file.is_open()) {
        std::cout << "Error: Unable to open scoreboard file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        ScoreInfo score;
        // 解析每一行的数据
        if (iss >> score.name >> score.lives) {
            getline(iss, score.date);
            scoreboardData.push_back(score);
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }
    AddNewObject(list = new Group());
    file.close();
}

void ScoreboardScene :: DisplayScoreboardData(int page) {
        list->Clear();
        int halfW = Engine::GameEngine::GetInstance().GetScreenSize().x / 2;
        int halfH = Engine::GameEngine::GetInstance().GetScreenSize().y / 2;
        int recordPerPage = 6;
        int startIndex = (page - 1) * recordPerPage;
        int endIndex = std::min(startIndex + recordPerPage, (int)scoreboardData.size());
        std::cout << startIndex << " " << endIndex << "\n";
        std::sort(scoreboardData.begin(), scoreboardData.end(), [](const ScoreInfo& a, const ScoreInfo& b) {
            return a.lives > b.lives;
        });
        for (int i = startIndex; i < endIndex; ++i) {
            //list.Clear();
            list->AddNewObject(new Engine::Label(scoreboardData[i].name +"   "+ std::to_string(scoreboardData[i].lives) + "   " +scoreboardData[i].date , 
                                "pirulen.ttf", 35, halfW, halfH - 200 + (i - startIndex) * 50, 0, 190, 0, 255, 0.5, 0.5));
        }
        Draw();
}

void ScoreboardScene::BackOnClick() {
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}

void ScoreboardScene::PrevPageOnClick() {
    if(index > 1){
        std::cout << "Prev " << index << "\n";
        index -= 1;
        DisplayScoreboardData(index);
    }
}

void ScoreboardScene::NextPageOnClick() {
    int div = scoreboardData.size() / 6;
    if(scoreboardData.size() % 6 != 0) div += 1;
    if(index < div){
        std::cout << "Next " << index << "\n";
        index++;
        DisplayScoreboardData(index);
    }
}

void ScoreboardScene::Terminate() {
    Clear();
    scoreboardData.clear();
    list->Clear();
}
