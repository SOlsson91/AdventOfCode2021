#pragma once
#include <vector>
#include <stack>
#include <cmath>
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
	static std::vector<uint32_t> ReadFromFileToInt(const std::string& file);
	static std::vector<unsigned char> ReadFromFileToByte(const std::string& file);
	static std::vector<std::string> ReadFromFileToString(const std::string& file);
	static std::vector<std::string> SplitString(const std::string& line);
	static std::vector<std::string> SplitStringDelimiter(const std::string& line, const std::string& delimiter);
	static bool MatchRegexInString(const std::regex& regex, const std::string& line, std::smatch& match);
	static uint32_t StringToBinary(const std::string& input);

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

	template<typename T>
	static std::vector<T> SplitStringToInt(const std::string& line, const std::string& delimiter)
	{
		std::vector<T> numbers;
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
};
