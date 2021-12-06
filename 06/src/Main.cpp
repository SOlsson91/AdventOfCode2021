#include "Utility.h"

uint64_t GetNumberOfLantenFishAfter(const std::vector<uint32_t>& fishInput, const uint32_t days)
{
	Timer t;
	std::map<uint32_t, uint64_t> EmptyMap = {{0,0},{1,0},{2,0},{3,0},{4,0},{5,0},{6,0},{7,0},{8,0}};
	std::map<uint32_t, uint64_t> lanternFishs = EmptyMap;

	for (const auto& i : fishInput)
	{
		lanternFishs[i]++;
	}

	for (uint32_t day = 0; day < days; day++)
	{

		std::map<uint32_t, uint64_t> dayMap;
		for (uint32_t index = 0; index < 9; index++)
		{
			if (index == 0)
			{
				dayMap[8] += lanternFishs[index];
				dayMap[6] += lanternFishs[index];
			}
			else
				dayMap[index - 1] += lanternFishs[index];
		}
		lanternFishs = dayMap;
	}

	uint64_t sum = 0;
	for (const auto& i : lanternFishs)
	{
		sum += i.second;
	}
	return sum;
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");
	auto fishInput = Utility::SplitStringToInt(input[0], ",");

	std::cout << "**Part 1** = " << GetNumberOfLantenFishAfter(fishInput, 80) << "\n";
	std::cout << "**Part 2** = " << GetNumberOfLantenFishAfter(fishInput, 256) << "\n";
}
