#include "Utility.h"

void Sweep(std::vector<uint32_t>& depths, uint32_t window)
{
	uint32_t increases = 0;
	for (uint32_t i = window; i < depths.size(); ++i)
	{
		if (depths[i - window] < depths[i])
			++increases;
	}
	std::cout << "Increases: " << increases << "\n";
}

int main()
{
	std::vector<uint32_t> depths = Utility::ReadFromFileToInt("../input.txt");

	Sweep(depths, 1);
	Sweep(depths, 3);
}
