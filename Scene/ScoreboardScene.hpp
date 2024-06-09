#ifndef ScoreboardScene_HPP
#define ScoreboardScene_HPP

#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
struct ScoreInfo {
        std::string name;
        int lives;
        std::string date;
        static bool CompareScore(const ScoreInfo& a, const ScoreInfo& b) {
            return a.lives > b.lives;
        }
    };
bool CompareScore(const ScoreInfo& a, const ScoreInfo& b);
class ScoreboardScene final : public Engine::IScene {
private:
    std::shared_ptr<ALLEGRO_SAMPLE_INSTANCE> bgmInstance;
    std::vector<ScoreInfo> scoreboardData;
    Engine::Group* list;
    int index;
public:
    void Initialize() override;

    void BackOnClick();

    void PrevPageOnClick();

    void NextPageOnClick();
    
    void LoadScoreboardData();

    void DisplayScoreboardData(int );

    void Terminate() override;
};

#endif //endif ScoreboardScene.hpp