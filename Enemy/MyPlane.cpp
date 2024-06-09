#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <cmath>
#include <random>
#include <string>
#include <vector>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Bullet.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Enemy.hpp"
#include "UI/Animation/ExplosionEffect.hpp"
#include "Engine/GameEngine.hpp"
#include "Engine/Group.hpp"
#include "Engine/IScene.hpp"
#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"
#include "Turret/Turret.hpp"

#include "MyPlane.hpp"

MyPlane::MyPlane(int x, int y) : Enemy("play/MyPlane.png", x, y, 16, 30, 5, 10) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}
void MyPlane :: UpdatePath(const std::vector<std::vector<int>>& mapDistance){}

void MyPlane :: Update(float deltaTime) {
    // 直接朝終點前進，不需要更新路徑
    Engine::Point target = PlayScene::EndGridPoint * PlayScene::BlockSize + Engine::Point(PlayScene::BlockSize / 2, PlayScene::BlockSize / 2);
    Engine::Point vec = target - Position;
    float distanceToEnd = vec.Magnitude();
    float moveDistance = speed * deltaTime;
    if (moveDistance >= distanceToEnd) {
        Hit(hp);
        getPlayScene()->Hit();
        reachEndTime = 0;
        return;
    } else {
        Engine::Point normalized = vec.Normalize();
        Position = Position + normalized * moveDistance;
        Velocity = normalized * speed;
    }
    Rotation = atan2(Velocity.y, Velocity.x);
    Sprite::Update(deltaTime);
}
