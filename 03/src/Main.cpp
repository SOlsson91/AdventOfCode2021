#include "Utility.h"

struct RowData
{
	uint16_t zeroes = 0;
	uint16_t ones = 0;
};

uint32_t GetPowerConsumption(const std::vector<std::string>& input)
{
	Timer t;
	std::vector<RowData> data;
	data.reserve(input[0].size());
	std::string gammaRate = "";
	std::string epsilonRate = "";

	for (uint8_t i = 0; i < input[0].size(); i++)
	{
		data[i].zeroes = 0;
		data[i].ones = 0;

		for (const std::string& row : input)
		{
			if (row[i] == '0')
				data[i].zeroes += 1;
			else
				data[i].ones += 1;
		}

		gammaRate += (data[i].ones > data[i].zeroes) ? "1" : "0";
		epsilonRate += (data[i].ones > data[i].zeroes) ? "0" : "1";
	}

	return Utility::StringToBinary(gammaRate) * Utility::StringToBinary(epsilonRate);
}

void RemoveRows(const std::vector<std::string>& toRemove, std::vector<std::string>& generatorRating)
{
	for (auto it = std::begin(generatorRating); it != std::end(generatorRating);)
	{
		bool removed = false;
		for (const auto& removeItem : toRemove)
		{
			if (*it == removeItem)
			{
				generatorRating.erase(it);
				removed = true;
				break;
			}
		}
		if (!removed)
			++it;
	}
}

uint64_t GetLifeSupportRating(const std::vector<std::string>& input)
{
	Timer t;
	std::vector<std::string> oxygenGeneratorRating = input;
	std::vector<std::string> co2ScrubberRating = input;

	for (uint8_t i = 0; i != input[0].size(); i++)
	{
		std::vector<std::string> ones = {};
		std::vector<std::string> zeroes = {};

		if (oxygenGeneratorRating.size() > 1)
		{
			for (const std::string& row : oxygenGeneratorRating)
			{
				if (row[i] == '0')
				{
					zeroes.emplace_back(row);
					continue;
				}
				ones.emplace_back(row);
			}
			if (ones.size() >= zeroes.size())
			{
				RemoveRows(zeroes, oxygenGeneratorRating);
			}
			else
			{
				RemoveRows(ones, oxygenGeneratorRating);
			}

		}

		ones.clear();
		zeroes.clear();
		if (co2ScrubberRating.size() > 1)
		{
			for (const std::string& row : co2ScrubberRating)
			{
				if (row[i] == '0')
				{
					zeroes.emplace_back(row);
					continue;
				}
				ones.emplace_back(row);
			}
			if (zeroes.size() <= ones.size())
			{
				RemoveRows(ones, co2ScrubberRating);
			}
			else
			{
				RemoveRows(zeroes, co2ScrubberRating);
			}
		}
	}

	return Utility::StringToBinary(oxygenGeneratorRating[0]) * Utility::StringToBinary(co2ScrubberRating[0]);
}

int main()
{
	std::vector<std::string> rows = Utility::ReadFromFileToString("../input.txt");
	std::cout << "**Part 1** = " << GetPowerConsumption(rows) << "\n";
	std::cout << "**Part 2** = " << GetLifeSupportRating(rows) << "\n";
}
