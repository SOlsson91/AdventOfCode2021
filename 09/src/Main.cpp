#include "Utility.h"

uint32_t GetNumberOfLowPoints(const std::vector<uint32_t>& heightMap, int32_t width)
{
	Timer t;
	uint32_t sumOfLowPoints = 0;
	for (uint32_t i = 0; i < heightMap.size(); i++)
	{
		int32_t x = i % width;
		int32_t y = i / width;
		int32_t height = heightMap.size() / width;

		if ((x - 1 >= 0 && heightMap[i - 1] <= heightMap[i]) || (x + 1 < width && heightMap[i + 1] <= heightMap[i]) ||
			(y - 1 >= 0 && heightMap[i - width] <= heightMap[i]) || (y + 1 < height && heightMap[i + width] <= heightMap[i]))
			continue;
		sumOfLowPoints += heightMap[i] + 1;
	}
	return sumOfLowPoints;
}

uint32_t BasinSize(std::vector<uint32_t>& heightMap, int32_t i, int32_t width)
{
	int32_t height = heightMap.size() / width;
	if (heightMap[i] < 9)
	{
		heightMap[i] = 10;
		int32_t x = i % width;
		int32_t y = i / width;

		uint32_t size = 1;
		if ((x + 1) < width)
			size += BasinSize(heightMap, i + 1, width);
		if ((x - 1) >= 0)
			size += BasinSize(heightMap, i - 1, width);
		if ((y + 1) < height)
			size += BasinSize(heightMap, i + width, width);
		if ((y - 1) >= 0)
			size += BasinSize(heightMap, i - width, width);
		return size;
	}
	return 0;
}

uint32_t GetLargestBasins(std::vector<uint32_t>& heightMap, int32_t width)
{
	Timer t;
	std::vector<uint32_t> largestBasins{};

	for (uint32_t i = 0; i < heightMap.size(); i++)
	{
		int32_t x = i % width;
		int32_t y = i / width;
		int32_t height = heightMap.size() / width;

		if ((x - 1 >= 0 && heightMap[i - 1] <= heightMap[i]) || (x + 1 < width && heightMap[i + 1] <= heightMap[i]) ||
			(y - 1 >= 0 && heightMap[i - width] <= heightMap[i]) || (y + 1 < height && heightMap[i + width] <= heightMap[i]))
			continue;

		largestBasins.push_back(BasinSize(heightMap, i, width));
	}

	std::sort(std::begin(largestBasins), std::end(largestBasins));
	std::reverse(std::begin(largestBasins), std::end(largestBasins));

	return largestBasins[0] * largestBasins[1] * largestBasins[2];
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");
	std::vector<uint32_t> heightMap {};
	uint32_t mapWidth = 0;
	for (const auto& row : input)
	{
		mapWidth = row.size();
		for (const auto num : row)
		{
			heightMap.emplace_back(std::atoi(&num));
		}
	}

	std::cout << "**Part 1** = " << GetNumberOfLowPoints(heightMap, mapWidth) << "\n";
	std::cout << "**Part 2** = " << GetLargestBasins(heightMap, mapWidth) << "\n";
}
