#include "config.h"
#include "poker.h"

int main()
{
    Poker poker;
    if (poker.Construct(Config::ScreenWidth, Config::ScreenHeight, Config::PixelWidth, Config::PixelHeight))
    {
        poker.Start();
    }
}