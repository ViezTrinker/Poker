#include "deck.h"

#include <codecvt>
#include <cstdlib>
#include <ctime>
#include <locale>
#include <string>

constexpr std::array<CardType, TotalNumberCards> Card
{{
	{ Cards::TwoClubs,		Suit::Clubs,	Rank::Two },
	{ Cards::TwoDiamonds,	Suit::Diamonds, Rank::Two },
	{ Cards::TwoHearts,		Suit::Hearts,	Rank::Two },
	{ Cards::TwoSpades,		Suit::Spades,	Rank::Two },

	{ Cards::ThreeClubs,	Suit::Clubs,	Rank::Three },
	{ Cards::ThreeDiamonds,	Suit::Diamonds, Rank::Three },
	{ Cards::ThreeHearts,	Suit::Hearts,	Rank::Three },
	{ Cards::ThreeSpades,	Suit::Spades,	Rank::Three },

	{ Cards::FourClubs,		Suit::Clubs,	Rank::Four },
	{ Cards::FourDiamonds,	Suit::Diamonds, Rank::Four },
	{ Cards::FourHearts,	Suit::Hearts,	Rank::Four },
	{ Cards::FourSpades,	Suit::Spades,	Rank::Four },

	{ Cards::FiveClubs,		Suit::Clubs,	Rank::Five },
	{ Cards::FiveDiamonds,	Suit::Diamonds, Rank::Five },
	{ Cards::FiveHearts,	Suit::Hearts,	Rank::Five },
	{ Cards::FiveSpades,	Suit::Spades,	Rank::Five },

	{ Cards::SixClubs,		Suit::Clubs,	Rank::Six },
	{ Cards::SixDiamonds,	Suit::Diamonds, Rank::Six },
	{ Cards::SixHearts,		Suit::Hearts,	Rank::Six },
	{ Cards::SixSpades,		Suit::Spades,	Rank::Six },

	{ Cards::SevenClubs,	Suit::Clubs,	Rank::Seven },
	{ Cards::SevenDiamonds,	Suit::Diamonds, Rank::Seven },
	{ Cards::SevenHearts,	Suit::Hearts,	Rank::Seven },
	{ Cards::SevenSpades,	Suit::Spades,	Rank::Seven },

	{ Cards::EightClubs,	Suit::Clubs,	Rank::Eight },
	{ Cards::EightDiamonds,	Suit::Diamonds, Rank::Eight },
	{ Cards::EightHearts,	Suit::Hearts,	Rank::Eight },
	{ Cards::EightSpades,	Suit::Spades,	Rank::Eight },

	{ Cards::NineClubs,		Suit::Clubs,	Rank::Nine },
	{ Cards::NineDiamonds,	Suit::Diamonds, Rank::Nine },
	{ Cards::NineHearts,	Suit::Hearts,	Rank::Nine },
	{ Cards::NineSpades,	Suit::Spades,	Rank::Nine },

	{ Cards::TenClubs,		Suit::Clubs,	Rank::Ten },
	{ Cards::TenDiamonds,	Suit::Diamonds, Rank::Ten },
	{ Cards::TenHearts,		Suit::Hearts,	Rank::Ten },
	{ Cards::TenSpades,		Suit::Spades,	Rank::Ten },

	{ Cards::JackClubs,		Suit::Clubs,	Rank::Jack },
	{ Cards::JackDiamonds,	Suit::Diamonds, Rank::Jack },
	{ Cards::JackHearts,	Suit::Hearts,	Rank::Jack },
	{ Cards::JackSpades,	Suit::Spades,	Rank::Jack },

	{ Cards::QueenClubs,	Suit::Clubs,	Rank::Queen },
	{ Cards::QueenDiamonds,	Suit::Diamonds, Rank::Queen },
	{ Cards::QueenHearts,	Suit::Hearts,	Rank::Queen },
	{ Cards::QueenSpades,	Suit::Spades,	Rank::Queen },

	{ Cards::KingClubs,		Suit::Clubs,	Rank::King },
	{ Cards::KingDiamonds,	Suit::Diamonds, Rank::King },
	{ Cards::KingHearts,	Suit::Hearts,	Rank::King },
	{ Cards::KingSpades,	Suit::Spades,	Rank::King },

	{ Cards::AceClubs,		Suit::Clubs,	Rank::Ace },
	{ Cards::AceDiamonds,	Suit::Diamonds, Rank::Ace },
	{ Cards::AceHearts,		Suit::Hearts,	Rank::Ace },
	{ Cards::AceSpades,		Suit::Spades,	Rank::Ace },
}};

Deck::Deck(uint8_t playerCount)
{
	std::srand(static_cast<unsigned int>(std::time({})));
	constexpr uint16_t ShuffleCount = 10000;

	std::array<Cards, TotalNumberCards> cardsToShuffle {};
	for (uint8_t index = 0; index < TotalNumberCards; index++)
	{
		cardsToShuffle[index] = static_cast<Cards>(index);
	}
	for (uint16_t index = 0; index < 10000; index++)
	{
		int16_t pos1 = std::rand() % TotalNumberCards;
		int16_t pos2 = std::rand() % TotalNumberCards;

		Cards tempCard = cardsToShuffle[pos1];
		cardsToShuffle[pos1] = cardsToShuffle[pos2];
		cardsToShuffle[pos2] = tempCard;
	}
	for (size_t index = 0; index < _communityCards.size(); index++)
	{
		_communityCards[index] = cardsToShuffle[index];
	}
	size_t shuffleIndex = _communityCards.size();
	for (uint8_t index = 0; index < playerCount; index++)
	{
		CardPair tempPair = { cardsToShuffle[shuffleIndex], cardsToShuffle[shuffleIndex + 1] };
		_holeCards.push_back(tempPair);
		shuffleIndex += 2;
	}

	if (!_spritesLoaded)
	{
		LoadSprites();
		_spritesLoaded = true;
	}
}

void Deck::LoadSprites(void)
{
	_cardSprite[0] = std::make_unique<olc::Sprite>("./resources/clubs_2.png");
	_cardSprite[4] = std::make_unique<olc::Sprite>("./resources/clubs_3.png");
	_cardSprite[8] = std::make_unique<olc::Sprite>("./resources/clubs_4.png");
	_cardSprite[12] = std::make_unique<olc::Sprite>("./resources/clubs_5.png");
	_cardSprite[16] = std::make_unique<olc::Sprite>("./resources/clubs_6.png");
	_cardSprite[20] = std::make_unique<olc::Sprite>("./resources/clubs_7.png");
	_cardSprite[24] = std::make_unique<olc::Sprite>("./resources/clubs_8.png");
	_cardSprite[28] = std::make_unique<olc::Sprite>("./resources/clubs_9.png");
	_cardSprite[32] = std::make_unique<olc::Sprite>("./resources/clubs_10.png");
	_cardSprite[36] = std::make_unique<olc::Sprite>("./resources/clubs_J.png");
	_cardSprite[40] = std::make_unique<olc::Sprite>("./resources/clubs_Q.png");
	_cardSprite[44] = std::make_unique<olc::Sprite>("./resources/clubs_K.png");
	_cardSprite[48] = std::make_unique<olc::Sprite>("./resources/clubs_A.png");

	_cardSprite[1] = std::make_unique<olc::Sprite>("./resources/diamonds_2.png");
	_cardSprite[5] = std::make_unique<olc::Sprite>("./resources/diamonds_3.png");
	_cardSprite[9] = std::make_unique<olc::Sprite>("./resources/diamonds_4.png");
	_cardSprite[13] = std::make_unique<olc::Sprite>("./resources/diamonds_5.png");
	_cardSprite[17] = std::make_unique<olc::Sprite>("./resources/diamonds_6.png");
	_cardSprite[21] = std::make_unique<olc::Sprite>("./resources/diamonds_7.png");
	_cardSprite[25] = std::make_unique<olc::Sprite>("./resources/diamonds_8.png");
	_cardSprite[29] = std::make_unique<olc::Sprite>("./resources/diamonds_9.png");
	_cardSprite[33] = std::make_unique<olc::Sprite>("./resources/diamonds_10.png");
	_cardSprite[37] = std::make_unique<olc::Sprite>("./resources/diamonds_J.png");
	_cardSprite[41] = std::make_unique<olc::Sprite>("./resources/diamonds_Q.png");
	_cardSprite[45] = std::make_unique<olc::Sprite>("./resources/diamonds_K.png");
	_cardSprite[49] = std::make_unique<olc::Sprite>("./resources/diamonds_A.png");

	_cardSprite[2] = std::make_unique<olc::Sprite>("./resources/hearts_2.png");
	_cardSprite[6] = std::make_unique<olc::Sprite>("./resources/hearts_3.png");
	_cardSprite[10] = std::make_unique<olc::Sprite>("./resources/hearts_4.png");
	_cardSprite[14] = std::make_unique<olc::Sprite>("./resources/hearts_5.png");
	_cardSprite[18] = std::make_unique<olc::Sprite>("./resources/hearts_6.png");
	_cardSprite[22] = std::make_unique<olc::Sprite>("./resources/hearts_7.png");
	_cardSprite[26] = std::make_unique<olc::Sprite>("./resources/hearts_8.png");
	_cardSprite[30] = std::make_unique<olc::Sprite>("./resources/hearts_9.png");
	_cardSprite[34] = std::make_unique<olc::Sprite>("./resources/hearts_10.png");
	_cardSprite[38] = std::make_unique<olc::Sprite>("./resources/hearts_J.png");
	_cardSprite[42] = std::make_unique<olc::Sprite>("./resources/hearts_Q.png");
	_cardSprite[46] = std::make_unique<olc::Sprite>("./resources/hearts_K.png");
	_cardSprite[50] = std::make_unique<olc::Sprite>("./resources/hearts_A.png");

	_cardSprite[3] = std::make_unique<olc::Sprite>("./resources/spades_2.png");
	_cardSprite[7] = std::make_unique<olc::Sprite>("./resources/spades_3.png");
	_cardSprite[11] = std::make_unique<olc::Sprite>("./resources/spades_4.png");
	_cardSprite[15] = std::make_unique<olc::Sprite>("./resources/spades_5.png");
	_cardSprite[19] = std::make_unique<olc::Sprite>("./resources/spades_6.png");
	_cardSprite[23] = std::make_unique<olc::Sprite>("./resources/spades_7.png");
	_cardSprite[27] = std::make_unique<olc::Sprite>("./resources/spades_8.png");
	_cardSprite[31] = std::make_unique<olc::Sprite>("./resources/spades_9.png");
	_cardSprite[35] = std::make_unique<olc::Sprite>("./resources/spades_10.png");
	_cardSprite[39] = std::make_unique<olc::Sprite>("./resources/spades_J.png");
	_cardSprite[43] = std::make_unique<olc::Sprite>("./resources/spades_Q.png");
	_cardSprite[47] = std::make_unique<olc::Sprite>("./resources/spades_K.png");
	_cardSprite[51] = std::make_unique<olc::Sprite>("./resources/spades_A.png");
}

void Deck::DrawRiver(olc::PixelGameEngine* pge)
{
	pge->DrawSprite(300, 360, _cardSprite[static_cast<size_t>(_communityCards[0])].get());
	pge->DrawSprite(380, 360, _cardSprite[static_cast<size_t>(_communityCards[1])].get());
	pge->DrawSprite(460, 360, _cardSprite[static_cast<size_t>(_communityCards[2])].get());
	pge->DrawSprite(540, 360, _cardSprite[static_cast<size_t>(_communityCards[3])].get());
	pge->DrawSprite(620, 360, _cardSprite[static_cast<size_t>(_communityCards[4])].get());
}

void Deck::DrawTurn(olc::PixelGameEngine* pge)
{
	pge->DrawSprite(300, 360, _cardSprite[static_cast<size_t>(_communityCards[0])].get());
	pge->DrawSprite(380, 360, _cardSprite[static_cast<size_t>(_communityCards[1])].get());
	pge->DrawSprite(460, 360, _cardSprite[static_cast<size_t>(_communityCards[2])].get());
	pge->DrawSprite(540, 360, _cardSprite[static_cast<size_t>(_communityCards[3])].get());
}

void Deck::DrawFlop(olc::PixelGameEngine* pge)
{
	pge->DrawSprite(300, 360, _cardSprite[static_cast<size_t>(_communityCards[0])].get());
	pge->DrawSprite(380, 360, _cardSprite[static_cast<size_t>(_communityCards[1])].get());
	pge->DrawSprite(460, 360, _cardSprite[static_cast<size_t>(_communityCards[2])].get());
}