#include "Utility.h"

std::vector<uint32_t> Utility::ReadFromFileToInt(const std::string& inputFile)
{
	std::vector<uint32_t> data;

	std::fstream file;
	file.open(inputFile, std::ios::in);
	if (!file)
	{
		std::cout << "Error opening file \n";
	}
	else
	{
		std::string row;
		while (getline(file, row))
		{
			data.push_back(std::stoi(row));
		}
		file.close();
	}
	return data;
}

std::vector<std::string> Utility::ReadFromFileToString(const std::string& inputFile)
{
	std::vector<std::string> data;

	std::fstream file;
	file.open(inputFile, std::ios::in);
	if (!file)
	{
		std::cout << "Error opening file \n";
	}
	else
	{
		std::string row;
		while (getline(file, row))
		{
			data.push_back(row);
		}
		file.close();
	}
	return data;
}

std::vector<std::string> Utility::SplitString(const std::string& line)
{
	std::istringstream iss(line);
	return {std::istream_iterator<std::string>(iss), std::istream_iterator<std::string>()};

}
