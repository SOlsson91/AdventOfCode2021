#include "Utility.h"

uint32_t MedianFuel(std::vector<uint32_t> numbers)
{
	Timer t;
	std::sort(std::begin(numbers), std::end(numbers));

	int32_t median = numbers[numbers.size() / 2];

	int32_t totalFuel = 0;
	std::for_each(std::begin(numbers), std::end(numbers), [&totalFuel, &median](int32_t number) {
		totalFuel += std::abs(number - median);
	});

	return totalFuel;
}

int64_t GetCost(const std::vector<uint32_t>& numbers, int32_t value)
{
	int64_t cost = 0;
	for (const auto& num : numbers)
	{
		int64_t dist = std::abs(value - static_cast<int32_t>(num));
		cost += (dist * (dist + 1)) / 2;
	}
	return cost;
}

uint32_t CrabEngineringFuel(std::vector<uint32_t> numbers)
{
	Timer t;
	int64_t lowestCost = INT64_MAX;
	uint32_t maxNumber = 0;
	for (const auto& number : numbers)
	{
		if (number > maxNumber)
			maxNumber = number;
	}

	for (uint32_t i = 0; i < maxNumber; i++)
	{
		int64_t cost = GetCost(numbers, i);
		if (cost < lowestCost)
			lowestCost = cost;
	}

	return lowestCost;
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");
	auto numbers = Utility::SplitStringToInt<uint32_t>(input[0], ",");

	std::cout << "**Part 1** = " << MedianFuel(numbers) << "\n";
	std::cout << "**Part 2** = " << CrabEngineringFuel(numbers) << "\n";

}
