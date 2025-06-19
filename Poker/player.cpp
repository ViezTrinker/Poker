#include "player.h"

void Player::Draw(void)
{
	_pge->FillCircle(_posX, _posY, 40, olc::BLACK);
}