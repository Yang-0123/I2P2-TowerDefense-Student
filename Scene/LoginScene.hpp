#include <allegro5/allegro_audio.h>
#include <memory>
#include "Engine/IScene.hpp"
class LoginScene : public Engine::IScene {
public:
    explicit LoginScene() = default;
    void Initialize() override;
    void Terminate() override;
    void SubmitOnClick();
    void SignUpOnClick();
    Engine::Group* alarm;
};
