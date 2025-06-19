#ifndef POKER_H
#define POKER_H

#include "button.h"
#include "olcPixelGameEngine.h"

class Poker : public olc::PixelGameEngine
{
public:
	Poker(void);

private:
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserCreate(void) override;

	void Input(void);

	void Logic(void);

	void Draw(void);
	void DrawMainMenu(void);
	void DrawGame(void);
	void DrawSettings(void);

	enum class State
	{
		MainMenu,
		Settings,
		GameRunning,
		GamePausing,
		GameFinished
	};
	State _state = State::MainMenu;

	int32_t _mouseX = 0;
	int32_t _mouseY = 0;

	Button _buttonStart;
	Button _buttonBackToMenu;
	Button _buttonSettings;

	Button _buttonIncreasePlayers;
	Button _buttonDecreasePlayers;

	static constexpr uint8_t _MinPlayers = 2;
	static constexpr uint8_t _MaxPlayers = 10;
	uint8_t _numberPlayers = 5;
};

#endif // POKER_H