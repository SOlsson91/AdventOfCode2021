#include "Utility.h"
#include "Timer.h"

uint32_t Sweep(std::vector<uint32_t>& depths, uint32_t window)
{
	Timer t;
	uint32_t increases = 0;
	for (uint32_t i = window; i < depths.size(); ++i)
	{
		if (depths[i - window] < depths[i])
			++increases;
	}
	return increases;
}

int main()
{
	std::vector<uint32_t> depths = Utility::ReadFromFileToInt("../input.txt");

	std::cout << "Part 1 = " << Sweep(depths, 1) << "\n";
	std::cout << "Part 2 = " << Sweep(depths, 3) << "\n";
}
