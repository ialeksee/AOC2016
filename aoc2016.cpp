#define OLC_PGE_APPLICATION

#include "olcPixelGameEngine/olcPixelGameEngine.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

// Override base class with your custom functionality
class AOC : public olc::PixelGameEngine
{
	enum class Direction
	{
		Left,
		Right
	};
	enum class Orientation
	{
		North,
		East,
		West,
		South
	}facing;

	struct Instruction
	{
		Direction dir;
		unsigned int steps;
	}instr;
	std::vector<Instruction> instructions;
	const unsigned int BLOCK_SIZE{5};
	const unsigned int STREET_WIDTH{4};
	int x_pos{0};
	int y_pos{0};
	float frame_rate = 1.0 / 30.0;
	float accumulated_time{0.0};
	unsigned int step = 0;
	int steps_x{0};
	int steps_y{0};
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
		for(int x = 0; x < ScreenWidth(); x += (BLOCK_SIZE + STREET_WIDTH))
			for(int y = 0; y < ScreenHeight(); y += (BLOCK_SIZE + STREET_WIDTH))
				DrawRect(x, y, BLOCK_SIZE, BLOCK_SIZE,olc::DARK_CYAN);

		//calc start position.
		int nb_blocks_h = ScreenWidth()/(BLOCK_SIZE + STREET_WIDTH);
		int nb_blocks_v = ScreenHeight()/(BLOCK_SIZE + STREET_WIDTH);
		x_pos = (ScreenWidth() ) - STREET_WIDTH;
		y_pos = (ScreenHeight() / 2) - STREET_WIDTH;
		
		FillCircle(x_pos, y_pos, 1, olc::RED);
		std::ifstream input_file("day1.txt");
		char chr;
		while(input_file >> chr)
		{
			if(chr == 'L')
			{
				input_file >> chr;
				instructions.emplace_back(Instruction{Direction::Left, static_cast<unsigned int>(chr - 0x30)});
			}

			if(chr == 'R')
			{
				input_file >> chr;
				instructions.emplace_back(Instruction{Direction::Right, static_cast<unsigned int>(chr - 0x30)});
			}
			if((chr == ' ') || (chr == ','))
				continue;
		}
		facing = Orientation::North;
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// Called once per frame, draws random coloured pixels
//		for (int x = 0; x < ScreenWidth(); x++)
//			for (int y = 0; y < ScreenHeight(); y++)
//				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		accumulated_time += fElapsedTime;
		if(accumulated_time >= frame_rate)
		{
			accumulated_time -= frame_rate;
			fElapsedTime = frame_rate;
			if(step < instructions.size())
			{
				instr = instructions.at(step);
				if(instr.dir == Direction::Left)
				{
					switch(facing)
					{
						case Orientation::North:
							{
								DrawLine(x_pos, y_pos, x_pos- instr.steps * (BLOCK_SIZE + STREET_WIDTH), y_pos, olc::RED);
								x_pos -=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::West;
								steps_x--;
							}
							break;
						case Orientation::West:
							{
								DrawLine(x_pos, y_pos, x_pos, y_pos + instr.steps * (BLOCK_SIZE + STREET_WIDTH), olc::RED);
								y_pos +=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::South;
								steps_y++;
							}
							break;
						case Orientation::South:
							{
								DrawLine(x_pos, y_pos, x_pos + instr.steps * (BLOCK_SIZE + STREET_WIDTH), y_pos, olc::RED);
								x_pos +=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::East;
								steps_x++;
							}
							break;
						case Orientation::East:
							{
								DrawLine(x_pos, y_pos, x_pos, y_pos - instr.steps * (BLOCK_SIZE + STREET_WIDTH), olc::RED);
								y_pos -=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::North;
								steps_y++;
							}
							break;
					};
				}
				if(instr.dir == Direction::Right)
				{
					switch(facing)
					{
						case Orientation::North:
							{
								DrawLine(x_pos, y_pos, x_pos+ instr.steps * (BLOCK_SIZE + STREET_WIDTH), y_pos, olc::RED);
								x_pos +=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::East;
								steps_x++;
							}
							break;
						case Orientation::West:
							{
								DrawLine(x_pos, y_pos, x_pos, y_pos - instr.steps * (BLOCK_SIZE + STREET_WIDTH), olc::RED);
								y_pos -=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::North;
								steps_y--;
							}
							break;
						case Orientation::South:
							{
								DrawLine(x_pos, y_pos, x_pos - instr.steps * (BLOCK_SIZE + STREET_WIDTH), y_pos, olc::RED);
								x_pos -=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::West;
								steps_x++;
							}
							break;
						case Orientation::East:
							{
								DrawLine(x_pos, y_pos, x_pos, y_pos + instr.steps * (BLOCK_SIZE + STREET_WIDTH), olc::RED);
								y_pos +=  instr.steps * (BLOCK_SIZE + STREET_WIDTH);
								facing = Orientation::South;
								steps_y--;
							}
							break;
					};
				}


				step++;	
			}
			else
			{
				static bool printed = false;
				if(!printed)
				{
					int result = abs(steps_x) + abs(steps_y);
					std::cout << "Steps: " << result << std::endl;
					printed = true;
				}
			}
		}
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


