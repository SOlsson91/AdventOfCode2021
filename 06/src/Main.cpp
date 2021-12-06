#include "Utility.h"

uint64_t GetNumberOfLantenFishAfter(const std::vector<uint32_t>& fishInput, const uint32_t days)
{
	Timer t;
	std::array<uint64_t, 9> lanternFishs{};

	for (const auto& i : fishInput)
	{
		lanternFishs[i]++;
	}

	for (uint32_t day = 0; day < days; day++)
	{
		std::array<uint64_t, 9> dayMap{};
		for (uint32_t index = 0; index < 9; index++)
		{
			if (index == 0)
			{
				dayMap[8] += lanternFishs[index];
				dayMap[6] += lanternFishs[index];
				continue;
			}
			dayMap[index - 1] += lanternFishs[index];
		}
		lanternFishs = dayMap;
	}

	return std::accumulate(std::begin(lanternFishs), std::end(lanternFishs), 0LL);
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");
	auto fishInput = Utility::SplitStringToInt(input[0], ",");

	std::cout << "**Part 1** = " << GetNumberOfLantenFishAfter(fishInput, 80) << "\n";
	std::cout << "**Part 2** = " << GetNumberOfLantenFishAfter(fishInput, 256) << "\n";
}
