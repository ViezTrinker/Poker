#include "poker.h"

#include <cmath>

#include "config.h"

Poker::Poker(void) : _buttonStart(this, 200, 500, 5, "START", olc::BLACK, olc::WHITE),
					_buttonSettings(this, 550, 500, 5, "SETTINGS", olc::BLACK, olc::WHITE),
					_buttonBackToMenu(this, 0, 725, 3, "<- MENU", olc::BLACK, olc::WHITE),
					_buttonIncreasePlayers(this, 750, 200, 3, "+", olc::BLACK, olc::WHITE),
					_buttonDecreasePlayers(this, 700, 200, 3, "-", olc::BLACK, olc::WHITE)
{
	sAppName = "POKER";
}

bool Poker::OnUserUpdate(float fElapsedTime)
{
	Input();
	Logic();
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
			InitTable();
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
		if (_buttonIncreasePlayers.IsClicked(_mouseX, _mouseY) && _numberPlayers < MaxPlayers)
		{
			_numberPlayers++;
			break;
		}
		if (_buttonDecreasePlayers.IsClicked(_mouseX, _mouseY) && _numberPlayers > MinPlayers)
		{
			_numberPlayers--;
			break;
		}
		break;
	default:
		break;
	}
}

void Poker::Logic(void)
{
	switch (_state)
	{
	case State::GameRunning:
		PokerRoundStateMachine();
		break;
	default:
		break;
	}
}

void Poker::PokerRoundStateMachine(void)
{
	switch (_stateRound)
	{
	case RoundState::Init:
		InitRound();
		break;
	default:
		break;
	}
}

void Poker::InitRound(void)
{
	Deck deck(_numberPlayers);
}

void Poker::InitTable(void)
{
	_player.clear();
	constexpr double Pi = 3.14159265;
	double startAngle = 3 * Pi / 2;
	double angleDistance = 2 * Pi / _numberPlayers;
	for (uint8_t index = 0; index < _numberPlayers; index++)
	{
		double angle = startAngle + index * angleDistance;
		double xPos = Config::ScreenWidth / 2 + TableRadius * cos(angle);
		double yPos = Config::ScreenHeight / 2 + TableRadius * sin(angle);
		_player.push_back(Player(this, xPos, yPos));
	}
}

void Poker::Draw(void)
{
	// Blank white screen as default
	Clear(olc::GREY);

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
	DrawCircle(ScreenWidth() / 2, ScreenHeight() / 2, TableRadius, olc::BLACK);
	_buttonBackToMenu.Draw();

	for (uint8_t index = 0; index < _numberPlayers; index++)
	{
		_player[index].Draw();
	}
	Deck::DrawFlop(this);
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
	std::string playerCountString = "NUMBER OF PLAYERS: ";
	playerCountString.append(std::to_string(_numberPlayers));
	DrawString(180, 200, playerCountString, olc::BLACK, 3);
	
	_buttonBackToMenu.Draw();
	_buttonIncreasePlayers.Draw();
	_buttonDecreasePlayers.Draw();
}