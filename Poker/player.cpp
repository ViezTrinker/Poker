#include "player.h"

void Player::Draw(void)
{
	_pge->FillCircle(static_cast<int32_t>(_posX), static_cast<int32_t>(_posY), 40, olc::BLACK);
}