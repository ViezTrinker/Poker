#ifndef DECK_H
#define DECK_H

#include <array>
#include <cstdint>
#include <vector>

#include "olcPixelGameEngine.h"

inline constexpr size_t TotalNumberCards = 52;
enum class Cards
{
	TwoClubs = 0,		TwoDiamonds,		TwoHearts,		TwoSpades,
	ThreeClubs,			ThreeDiamonds,		ThreeHearts,	ThreeSpades,
	FourClubs,			FourDiamonds,		FourHearts,		FourSpades,
	FiveClubs,			FiveDiamonds,		FiveHearts,		FiveSpades,
	SixClubs,			SixDiamonds,		SixHearts,		SixSpades,
	SevenClubs,			SevenDiamonds,		SevenHearts,	SevenSpades,
	EightClubs,			EightDiamonds,		EightHearts,	EightSpades,
	NineClubs,			NineDiamonds,		NineHearts,		NineSpades,
	TenClubs,			TenDiamonds,		TenHearts,		TenSpades,
	JackClubs,			JackDiamonds,		JackHearts,		JackSpades,
	QueenClubs,			QueenDiamonds,		QueenHearts,	QueenSpades,
	KingClubs,			KingDiamonds,		KingHearts,		KingSpades,
	AceClubs,			AceDiamonds,		AceHearts,		AceSpades,
	Last = TotalNumberCards
};

enum class Suit
{
	Clubs = 0,
	Diamonds,
	Hearts,
	Spades
};

enum class Rank { Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace };

struct CardType
{
	Cards card;
	Suit suit;
	Rank rank;
};

class Deck
{
public:
	Deck(uint8_t playerCount);
	static void DrawRiver(olc::PixelGameEngine* pge);
	static void DrawTurn(olc::PixelGameEngine* pge);
	static void DrawFlop(olc::PixelGameEngine* pge);
private:
	static void LoadSprites(void);
	
	static inline std::array<Cards, 5> _communityCards = {};

	using CardPair = std::array<Cards, 2>;
	static inline std::vector<CardPair> _holeCards;

	static inline std::array<std::unique_ptr<olc::Sprite>, TotalNumberCards> _cardSprite;
	static inline bool _spritesLoaded = false;
};

#endif