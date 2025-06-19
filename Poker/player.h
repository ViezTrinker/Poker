#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>

#include "olcPixelGameEngine.h"
#include "settings.h"

class Player
{
public:
	Player(olc::PixelGameEngine* pge, double posX, double posY) : _pge(pge), _posX(posX), _posY(posY) {}
	void Draw(void);
private:
	olc::PixelGameEngine* _pge = nullptr;
	uint32_t _money = StartMoney;
	double _posX = 0;
	double _posY = 0;
};

#endif