#include "Utility.h"
uint32_t FindUniqueNumbers(const std::vector<std::string>& input)
{
	Timer t;
	uint32_t knownNumbers = 0;
	for (const auto& line : input)
	{
		size_t pos;
		if ((pos = line.find("|")) != std::string::npos)
		{
			std::string sub = line.substr(pos + 2);
			auto words = Utility::SplitString(sub);
			for (const auto& word : words)
			{
				if (word.size() == 2 or word.size() == 4 or word.size() == 3 or word.size() == 7)
					knownNumbers++;
			}
		}
	}
	return knownNumbers;
}

uint32_t DeduceMissingNumbers(const std::vector<std::string>& input)
{
	Timer t;
	for (const auto& row : input)
	{
		std::cout << row << std::endl;
	}
	return 0;
}

int main()
{
	std::vector<std::string> input = Utility::ReadFromFileToString("../input.txt");

	std::cout << "**Part 1** = " << FindUniqueNumbers(input) << "\n";
	std::cout << "**Part 2** = " << DeduceMissingNumbers(input) << "\n";
}
