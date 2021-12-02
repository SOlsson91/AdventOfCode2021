#include "Utility.h"

uint32_t Position(std::vector<std::string>& directions)
{
	Timer t;
	int32_t horizontalPosition = 0, depth = 0;

	for (const auto& dir : directions)
	{
		std::vector<std::string> split = Utility::SplitString(dir);
		if (split[0].compare("forward"))
			horizontalPosition += stoi(split[1]);

		if (split[0].compare("down"))
			depth += stoi(split[1]);
		else if (split[0].compare("up"))
			depth -= stoi(split[1]);
	}
	return horizontalPosition * depth;
}

uint32_t FinalPosition(std::vector<std::string>& directions)
{
	Timer t;
	uint32_t horizontalPosition = 0, depth = 0, aim = 0;

	for (const auto& dir : directions)
	{
		std::vector<std::string> split = Utility::SplitString(dir);
		if (split[0].compare("forward"))
		{
			horizontalPosition += stoi(split[1]);
			depth += aim * stoi(split[1]);
		}

		if (split[0].compare("down"))
			aim += stoi(split[1]);
		else if ( split[0].compare("up"))
			aim -= stoi(split[1]);
	}
	return horizontalPosition * depth;
}

int main()
{
	std::vector<std::string> direction = Utility::ReadFromFileToString("../input.txt");
	std::cout << "Part 1 = " << Position(direction) << "\n";
	std::cout << "Part 2 = " << FinalPosition(direction) << "\n";
}
