#include <allegro5/base.h>
#include <random>
#include <string>

#include "Engine/Point.hpp"
#include "RedTankEnemy.hpp"

RedTankEnemy::RedTankEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 20, 20, 100, 100){};
