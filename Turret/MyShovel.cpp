#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"
#include "MyShovel.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

const int MyShovel::Price = 0;
MyShovel::MyShovel(float x, float y) :
	Turret("play/dirty-1.png", "play/shovel.png", x, y, 5, Price, 1) {
}
void MyShovel::CreateBullet() {}
