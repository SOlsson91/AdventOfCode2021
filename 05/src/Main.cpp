#include "Utility.h"

struct Point
{
	uint32_t x;
	uint32_t y;

	bool operator<(const Point &ob) const
	{
		return (x < ob.x || (x == ob.x && y < ob.y));
	}
};

struct Line
{
	Point start;
	Point end;
};

std::vector<Line> InputToLines(const std::vector<std::string>& input)
{
	std::vector<Line> lines;
	for (const auto& row : input)
	{
		std::vector<std::string> splitLine = Utility::SplitString(row);
		std::vector<uint32_t> startCoordinates = Utility::SplitStringToInt(splitLine[0], ",");
		std::vector<uint32_t> endCoordinates = Utility::SplitStringToInt(splitLine[2], ",");
		Line line;
		line.start = {startCoordinates[0], startCoordinates[1]};
		line.end = {endCoordinates[0], endCoordinates[1]};
		lines.emplace_back(line);
	}
	return lines;
}

uint32_t HydrothermalVentPoints(const std::vector<Line> lines, bool checkDiagonals = false)
{
	Timer t;
	std::map<Point, uint32_t> pointMap;
	for (const auto& line : lines)
	{
		if (line.start.x == line.end.x)
		{
			uint32_t min = line.start.y < line.end.y ? line.start.y : line.end.y;
			uint32_t max = line.start.y > line.end.y ? line.start.y : line.end.y;
			for (; min <= max; ++min)
			{
				Point p = {line.start.x, min};
				auto it = pointMap.find(p);
				if (it != pointMap.end())
				{
					pointMap.at(p)++;
					continue;
				}
				pointMap.insert({p, 1});
			}
		}
		else if (line.start.y == line.end.y)
		{
			uint32_t min = line.start.x < line.end.x ? line.start.x : line.end.x;
			uint32_t max = line.start.x > line.end.x ? line.start.x : line.end.x;
			for (; min <= max; ++min)
			{
				Point p = {min, line.start.y};

				auto it = pointMap.find(p);
				if (it != pointMap.end())
				{
					pointMap.at(p)++;
					continue;
				}
				pointMap.emplace(p, 1);
			}
		}
		else
		{
			if (!checkDiagonals)
				continue;

			Point min = line.start < line.end ? line.start : line.end;
			Point max = line.end < line.start ? line.start : line.end;

			uint32_t yIt = 0;
			for (uint32_t x = min.x; x <= max.x; x++)
			{
				int32_t direction = min.y < max.y ? 1 : -1;
				Point p = {x, min.y + (direction * yIt++)};

				auto it = pointMap.find(p);
				if (it != pointMap.end())
				{
					pointMap.at(p)++;
					continue;
				}
				pointMap.emplace(p, 1);
			}
		}
	}

	uint32_t lineOverlappsGreaterThenTwo = 0;
	for (const auto& key : pointMap)
	{
		if (key.second >= 2)
			lineOverlappsGreaterThenTwo++;
	}
	return lineOverlappsGreaterThenTwo;
}

int main()
{
	std::vector<std::string> input = Utility::ReadFromFileToString("../input.txt");
	std::vector<Line> lines = InputToLines(input);

	std::cout << "**Part 1** = " << HydrothermalVentPoints(lines) << "\n";
	std::cout << "**Part 2** = " << HydrothermalVentPoints(lines, true) << "\n";
}
