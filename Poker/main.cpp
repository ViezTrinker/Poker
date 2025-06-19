#include "config.h"
#include "poker.h"

int main()
{
    Poker poker;
    if (poker.Construct(ScreenWidth, ScreenHeight, PixelWidth, PixelHeight))
    {
        poker.Start();
    }
}