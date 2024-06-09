#ifndef MYSHOVEL_HPP
#define MYSHOVEL_HPP
#include "Turret.hpp"

class MyShovel: public Turret {
public:
	static const int Price;
    MyShovel(float x, float y);
    void CreateBullet() override;
};
#endif // MYTURRET_HPP
