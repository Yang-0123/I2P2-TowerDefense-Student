#include <allegro5/allegro_audio.h>
#include <functional>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include "LoginScene.hpp"

#include "Engine/AudioHelper.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"
#include "UI/Component/InputBox.hpp"
Engine::InputBox* usernameInputBox;
Engine::InputBox* passwordInputBox;
void LoginScene::Initialize() {
    int w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    int h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    int halfW = w / 2;
    int halfH = h / 2;
    AddNewObject(alarm = new Group());
    Engine::ImageButton* btn;
    AddNewObject(new Engine::Label("Tower Defense", "pirulen.ttf", 120, halfW, halfH / 3 + 50, 10, 255, 255, 255, 0.5, 0.5));
    //AddNewObject(new Engine::Label("Login", "pirulen.ttf", 60, halfW, halfH / 3 + 50, 255, 255, 255, 0.5, 0.5));
    //AddNewObject(new Engine::Label("Enter username here...", "pirulen.ttf", 23, halfW-20, halfH / 2 + 190, 255, 255, 255, 70, 0.5, 0.5));
    usernameInputBox = new Engine::InputBox("pirulen.ttf", 32, halfW, halfH / 2 + 190, 
    500, 70, 255, 255, 255, 255, 0, 0, 0, 255, false,"Enter username here...", 0.5, 0.5);
    AddNewControlObject(usernameInputBox);

    //AddNewObject(new Engine::Label("Enter password here...", "pirulen.ttf", 23, halfW-20, halfH / 2 + 300, 255, 255, 255, 70, 0.5, 0.5));
    passwordInputBox = new Engine::InputBox("pirulen.ttf", 32, halfW, halfH / 2 + 300,
    500, 70, 255, 255, 255, 255, 0, 0, 0, 255, true,"Enter password here...", 0.5, 0.5);
    AddNewControlObject(passwordInputBox);

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW - 225, halfH + 200, 175, 80);
    btn->SetOnClickCallback(std::bind(&LoginScene::SubmitOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("SignIn", "pirulen.ttf", 32, halfW-140, halfH + 240, 0, 0, 0, 255, 0.5, 0.5));

    btn = new Engine::ImageButton("stage-select/dirt.png", "stage-select/floor.png", halfW+75, halfH + 200, 175, 80);
    btn->SetOnClickCallback(std::bind(&LoginScene::SignUpOnClick, this));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("SignUp", "pirulen.ttf", 32, halfW+160, halfH + 240, 0, 0, 0, 255, 0.5, 0.5));

}

void LoginScene::Terminate() {
    IScene::Terminate();
}

void LoginScene::SubmitOnClick() {
    std::string username = usernameInputBox->GetText();
    std::string password = passwordInputBox->GetText();

    // 檢查 auth.txt 是否存在，如果不存在則創建它。
    std::ifstream authFile("../Resource/auth.txt");
    if (!authFile.is_open()) {
        std::ofstream createAuthFile("../Resource/auth.txt");
        createAuthFile.close();
    }
    
    authFile.close();

    // 重新打開 auth.txt 進行驗證。
    authFile.open("../Resource/auth.txt");
    std::string line;
    bool authenticated = false;

    while (std::getline(authFile, line)) {
        std::istringstream iss(line);
        std::string storedUsername, storedPassword;
        if (!(iss >> storedUsername >> storedPassword)) { continue; }
        if (storedUsername == username && storedPassword == password) {
            authenticated = true;
            break;
        }
    }
    
    if (authenticated) {
        Engine::GameEngine::GetInstance().ChangeScene("start");
    } else {
        alarm->Clear();
        alarm->AddNewObject(new Engine::Label("Login Failed", "pirulen.ttf", 32, Engine::GameEngine::GetInstance().GetScreenSize().x / 2, Engine::GameEngine::GetInstance().GetScreenSize().y - 245, 255, 0, 0, 255, 0.5, 0.5));
    }
}
bool IsPasswordValid(const std::string& password) {
    bool hasLetter = false;
    bool hasDigit = false;

    for (char ch : password) {
        if (isalpha(ch)) {
            hasLetter = true;
        }
        if (isdigit(ch)) {
            hasDigit = true;
        }
    }

    return hasLetter && hasDigit;
}

void LoginScene::SignUpOnClick(){
    std::string username = usernameInputBox->GetText();
    std::string password = passwordInputBox->GetText();

    if (!IsPasswordValid(password)) {
        alarm->Clear();
        AddNewObject(new Engine::Label("Password must contain letters and numbers", "pirulen.ttf", 32, Engine::GameEngine::GetInstance().GetScreenSize().x / 2, Engine::GameEngine::GetInstance().GetScreenSize().y - 245, 255, 0, 0, 255, 0.5, 0.5));
        return;
    }
    // 檢查 auth.txt 是否存在，如果不存在則創建它。
    std::ifstream authFile("../Resource/auth.txt");
    if (!authFile.is_open()) {
        std::ofstream createAuthFile("../Resource/auth.txt");
        createAuthFile.close();
    }
    authFile.close();

    // 檢查帳號是否已存在。
    authFile.open("../Resource/auth.txt");
    std::string line;
    bool userExists = false;

    while (std::getline(authFile, line)) {
        std::istringstream iss(line);
        std::string storedUsername, storedPassword;
        if (!(iss >> storedUsername >> storedPassword)) { continue; }
        if (storedUsername == username) {
            userExists = true;
            break;
        }
    }
    authFile.close();

    if (!userExists) {
        std::ofstream authFileOut("../Resource/auth.txt", std::ios_base::app);
        authFileOut << username << " " << password << std::endl;
        authFileOut.close();
        alarm->Clear();
        AddNewObject(new Engine::Label("SignUp Successful", "pirulen.ttf", 32, Engine::GameEngine::GetInstance().GetScreenSize().x / 2, Engine::GameEngine::GetInstance().GetScreenSize().y - 245, 255, 0, 0, 255, 0.5, 0.5));
    } else {
        alarm->Clear();
        AddNewObject(new Engine::Label("Username Already Exists", "pirulen.ttf", 32, Engine::GameEngine::GetInstance().GetScreenSize().x / 2, Engine::GameEngine::GetInstance().GetScreenSize().y - 245, 255, 0, 0, 255, 0.5, 0.5));
    }
} 