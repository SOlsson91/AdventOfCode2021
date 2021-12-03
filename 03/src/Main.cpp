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

int main()
{
	std::vector<std::string> rows = Utility::ReadFromFileToString("../input.txt");
	std::cout << "**Part 1** = " << GetPowerConsumption(rows) << "\n";
}
