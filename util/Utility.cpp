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
std::vector<unsigned char> ReadFromFileToByte(const std::string& inputFile)
{
	std::streampos fileSize;
	std::ifstream file(inputFile, std::ios::binary);

	file.seekg(0, std::ios::end);
	fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<unsigned char> data(fileSize);
	file.read(reinterpret_cast<char*>(&data[0]), fileSize);

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

std::vector<uint32_t> Utility::SplitStringToInt(const std::string& line, const std::string& delimiter)
{
	std::vector<uint32_t> numbers;
	std::string s = line;

	size_t pos = 0;
	std::string token;
	while ((pos = s.find(delimiter)) != std::string::npos)
	{
		token = s.substr(0, pos);
		numbers.emplace_back(std::stoi(token));
		s.erase(0, pos + delimiter.length());
	}
	//TODO: Proper check for last character.
	if (s.size() != 0)
	{
		numbers.emplace_back(std::stoi(s));
	}
	return numbers;
}


bool Utility::MatchRegexInString(const std::regex& regex, const std::string& line, std::smatch& match)
{
	std::regex_search(line, match, regex);
	if (!match.empty())
		return true;
	return false;
}

uint32_t Utility::StringToBinary(const std::string& input)
{
	uint32_t val = 0, temp = 1, len = input.length();
	for (int i = len - 1; i >= 0; i--)
	{
		if (input[i] == '1')
			val += temp;
		temp = temp * 2;
   }
   return val;
}
