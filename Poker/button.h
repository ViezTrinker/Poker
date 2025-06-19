#ifndef BUTTON_H
#define BUTTON_H

#include <string>

#include "olcPixelGameEngine.h"

class Button
{
public:
	Button(olc::PixelGameEngine* pge,
		int32_t x, int32_t y, uint32_t scale, std::string string, olc::Pixel colorBorder, olc::Pixel colorFill) :
		_pge(pge), _x(x), _y(y), _scale(scale), _string(string), _colorBorder(colorBorder), _colorFill(colorFill)
	{
		_width = _pge->GetTextSize(_string).x * _scale;
		_height = _pge->GetTextSize(_string).y * _scale;
	}

	void Draw(void);
	bool IsClicked(int32_t x, int32_t y);
private:
	int32_t _x = 0;
	int32_t _y = 0;
	uint32_t _scale = 1;
	std::string _string = {};
	olc::Pixel _colorBorder = olc::BLACK;
	olc::Pixel _colorFill = olc::WHITE;

	int32_t _width = 0;
	int32_t _height = 0;

	olc::PixelGameEngine* _pge = nullptr;
};

#endif