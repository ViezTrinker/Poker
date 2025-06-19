#include "button.h"

void Button::Draw(void)
{	
	_pge->FillRect(_x, _y, _width, _height, _colorFill);
	_pge->DrawRect(_x, _y, _width, _height, _colorBorder);
	_pge->DrawString(_x, _y, _string, _colorBorder, _scale);
}

bool Button::IsClicked(int32_t x, int32_t y)
{	
	if (!_pge->GetMouse(olc::Mouse::LEFT).bPressed)
	{
		return false;
	}

	return (x <= _x + _width && x >= _x && y <= _y + _height && y >= _y);
}