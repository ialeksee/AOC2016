
#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine/olcPixelGameEngine.h"
// Override base class with your custom functionality
class AOC : public olc::PixelGameEngine
{
public:
	AOC()
	{
		// Name your application
		sAppName = "Advent of Code 2016";
	}

public:
	bool OnUserCreate() override
	{
		// Called once at the start, so create things here
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};

int main()
{
	AOC demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}


