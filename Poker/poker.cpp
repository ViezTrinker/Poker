#include "poker.h"

Poker::Poker(void) : _buttonStart(this, 200, 500, 5, "START", olc::BLACK, olc::WHITE),
					_buttonSettings(this, 550, 500, 5, "SETTINGS", olc::BLACK, olc::WHITE),
					_buttonBackToMenu(this, 0, 725, 3, "<- MENU", olc::BLACK, olc::WHITE)
{
	sAppName = "POKER";
}

bool Poker::OnUserUpdate(float fElapsedTime)
{
	Input();
	Draw();
	return true;
}

bool Poker::OnUserCreate(void)
{
	return true;
}

void Poker::Input(void)
{
	_mouseX = GetMouseX();
	_mouseY = GetMouseY();

	switch (_state)
	{
	case State::MainMenu:
		if (_buttonStart.IsClicked(_mouseX, _mouseY))
		{
			_state = State::GameRunning;
			break;
		}
		if (_buttonSettings.IsClicked(_mouseX, _mouseY))
		{
			_state = State::Settings;
			break;
		}
		break;
	case State::GameRunning:
		if (_buttonBackToMenu.IsClicked(_mouseX, _mouseY))
		{
			_state = State::MainMenu;
			break;
		}
		break;
	case State::Settings:
		if (_buttonBackToMenu.IsClicked(_mouseX, _mouseY))
		{
			_state = State::MainMenu;
			break;
		}
		break;
	default:
		break;
	}
}

void Poker::Logic(void)
{

}

void Poker::Draw(void)
{
	// Blank white screen as default
	Clear(olc::WHITE);

	// Display mouse position for debugging purposes
	DrawString(0, 0, std::to_string(_mouseX), olc::BLACK, 3);
	DrawString(0, 25, std::to_string(_mouseY), olc::BLACK, 3);

	switch (_state)
	{
	case State::MainMenu:
		DrawMainMenu();
		break;
	case State::GameRunning:
		DrawGame();
		break;
	case State::Settings:
		DrawSettings();
		break;
	default:
		break;
	}
}

void Poker::DrawGame(void)
{
	DrawCircle(ScreenWidth()/2, ScreenHeight()/2, 250, olc::BLACK);
	_buttonBackToMenu.Draw();
}

void Poker::DrawMainMenu(void)
{
	// Draw POKER string
	const std::string stringGame = "POKER";
	constexpr uint32_t stringScale = 15;
	const int32_t stringX = (ScreenWidth() - GetTextSize(stringGame).x * stringScale) / 2;
	DrawString(stringX, 125, "POKER", olc::BLACK, stringScale);

	_buttonStart.Draw();
	_buttonSettings.Draw();
}

void Poker::DrawSettings(void)
{
	_buttonBackToMenu.Draw();
}