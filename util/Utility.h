#pragma once
#include <vector>
#include <numeric>
#include <array>
#include <iostream>
#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <regex>
#include "Timer.h"

class Utility
{
public:
	template <typename T>
	static std::vector<T> ReadFromFileToNum(const std::string& inputFile)
	{
		std::vector<T> data;

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
				data.push_back(std::stoll(row));
			}
			file.close();
		}
		return data;
	}

	static std::vector<uint32_t> ReadFromFileToInt(const std::string& file);
	static std::vector<unsigned char> ReadFromFileToByte(const std::string& file);
	static std::vector<std::string> ReadFromFileToString(const std::string& file);
	static std::vector<std::string> SplitString(const std::string& line);
	static bool MatchRegexInString(const std::regex& regex, const std::string& line, std::smatch& match);
	static uint32_t StringToBinary(const std::string& input);
	static std::vector<uint32_t> SplitStringToInt(const std::string& line, const std::string& delimiter);
};
