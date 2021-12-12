#include "Utility.h"

void IncreaseAdjacent(std::vector<uint32_t>& squids, uint32_t i, int32_t width)
{
	int32_t x = i % width;
	int32_t y = i / width;
	int32_t height = squids.size() / width;
	if (x - 1 >= 0)
	{
		squids[i - 1]++;
		if (squids[i - 1] == 10)
			IncreaseAdjacent(squids, i - 1, width);
	}
	if (x + 1 < width)
	{
		squids[i + 1]++;
		if (squids[i + 1] == 10)
			IncreaseAdjacent(squids, i + 1, width);
	}
	if (y - 1 >= 0)
	{
		squids[i - width]++;
		if (squids[i - width] == 10)
			IncreaseAdjacent(squids, i - width, width);
	}
	if (y + 1 < height)
	{
		squids[i + width]++;
		if (squids[i + width] == 10)
			IncreaseAdjacent(squids, i + width, width);
	}
	//NOTE: Diagonal
	if (x - 1 >= 0 && y - 1 >= 0)
	{
		squids[i - width - 1]++;
		if (squids[i - width - 1] == 10)
			IncreaseAdjacent(squids, i - width - 1, width);
	}
	if (x - 1 >= 0 && y + 1 < height)
	{
		squids[i + width - 1]++;
		if (squids[i + width - 1] == 10)
			IncreaseAdjacent(squids, i + width - 1, width);
	}

	if (x + 1 < width && y - 1 >= 0)
	{
		squids[i - width + 1]++;
		if (squids[i - width + 1] == 10)
			IncreaseAdjacent(squids, i - width + 1, width);
	}
	if (x + 1 < width && y + 1 < height)
	{
		squids[i + width + 1]++;
		if (squids[i + width + 1] == 10)
			IncreaseAdjacent(squids, i + width + 1, width);
	}
}

uint32_t FlashesAfterSteps(std::vector<uint32_t> squids, const uint32_t width, uint32_t steps = 0)
{
	Timer t;
	if (steps == 0)
	{
		uint32_t step = 1;
		while (true)
		{
			for (uint32_t i = 0; i < squids.size(); i++)
			{
				squids[i]++;
				if (squids[i] == 10)
				{
					IncreaseAdjacent(squids, i, width);
				}
			}
			uint32_t flashes = 0;
			for (uint32_t i = 0; i < squids.size(); i++)
			{
				if (squids[i] > 9)
				{
					flashes++;
					squids[i] = 0;
				}
			}
			if (flashes == squids.size())
				return step;
			step++;
		}
		return 0;
	}

	uint32_t flashes = 0;
	for (uint32_t step = 0; step < steps; step++)
	{
		for (uint32_t i = 0; i < squids.size(); i++)
		{
			squids[i]++;
			if (squids[i] == 10)
			{
				IncreaseAdjacent(squids, i, width);
			}
		}
		for (uint32_t i = 0; i < squids.size(); i++)
		{
			if (squids[i] > 9)
			{
				flashes++;
				squids[i] = 0;
			}
		}
	}
	return flashes;
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");
	std::vector<uint32_t> numbers;
	const uint32_t width = input[0].size();
	for (const auto& line : input)
	{
		for (const char c : line)
		{
			numbers.emplace_back(std::atoi(&c));
		}
	}

	std::cout << "**Part 1** = " << FlashesAfterSteps(numbers, width, 100) << "\n";
	std::cout << "**Part 2** = " << FlashesAfterSteps(numbers, width) << "\n";
}
