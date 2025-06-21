#ifndef POKER_H
#define POKER_H

#include <vector> 

#include "button.h"
#include "deck.h"
#include "olcPixelGameEngine.h"
#include "player.h"
#include "settings.h"

class Poker : public olc::PixelGameEngine
{
public:
	Poker(void);

private:
	bool OnUserUpdate(float fElapsedTime) override;
	bool OnUserCreate(void) override;

	void Input(void);

	void Logic(void);
	void PokerRoundStateMachine(void);
	void InitRound(void);

	void InitTable(void);

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

	enum class RoundState
	{
		Init
	};
	RoundState _stateRound = RoundState::Init;

	int32_t _mouseX = 0;
	int32_t _mouseY = 0;

	Button _buttonStart;
	Button _buttonBackToMenu;
	Button _buttonSettings;

	Button _buttonIncreasePlayers;
	Button _buttonDecreasePlayers;

	uint8_t _numberPlayers = DefaultStartPlayers;

	std::vector<Player> _player;
};

#endif // POKER_H