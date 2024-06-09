#ifndef MYPLANE_HPP
#define MYPLANE_HPP
#include "Enemy.hpp"

class MyPlane : public Enemy {
public:
	MyPlane(int x, int y);
    void UpdatePath(const std::vector<std::vector<int>>& mapDistance) override;
    void Update(float deltaTime) override;
};
#endif // MYPLANE_HPP
