#include "Utility.h"

uint32_t GetCorruptionValue(const std::vector<std::string>& input)
{
	Timer t;
	uint32_t corruptValue = 0;
	for (const auto& row : input)
	{
		std::stack<uint8_t> brackets;
		for (const auto& c : row)
		{
			if ((c == '(') || (c == '[') || (c == '{') || (c == '<'))
			{
				brackets.emplace(c);
				continue;
			}
			uint8_t topChar = brackets.top();
			if ((topChar == '(' && c == ')') || (topChar == '[' && c == ']') ||
				(topChar == '{' && c == '}') || (topChar == '<' && c == '>'))
			{
				brackets.pop();
				continue;
			}
			if (c == ')')
				corruptValue += 3;
			else if (c == ']')
				corruptValue += 57;
			else if (c == '}')
				corruptValue += 1197;
			else if (c == '>')
				corruptValue += 25137;
			break;
		}
	}
	return corruptValue;
}

void GetUncompleted(const std::vector<std::string>& input, std::vector<std::stack<uint8_t>>& outStacks)
{
	for (const auto& row : input)
	{
		std::stack<uint8_t> brackets;
		bool corrupt = false;
		for (const auto& c : row)
		{
			if ((c == '(') || (c == '[') || (c == '{') || (c == '<'))
			{
				brackets.emplace(c);
				continue;
			}
			uint8_t topChar = brackets.top();
			if ((topChar == '(' && c == ')') || (topChar == '[' && c == ']') ||
				(topChar == '{' && c == '}') || (topChar == '<' && c == '>'))
			{
				brackets.pop();
				continue;
			}

			corrupt = true;
			break;
		}
		if (!brackets.empty() && !corrupt)
			outStacks.push_back(brackets);
	}
}

uint64_t MiddleFixedScore(const std::vector<std::string>& input)
{
	Timer t;
	std::vector<std::stack<uint8_t>> uncompleted{};
	GetUncompleted(input, uncompleted);
	std::vector<uint64_t> scores;

	for (auto& stack : uncompleted)
	{
		uint64_t score = 0;
		while (!stack.empty())
		{
			if (stack.top() == '(')
				score = (score * 5) + 1;
			else if (stack.top() == '[')
				score = (score * 5) + 2;
			else if (stack.top() == '{')
				score = (score * 5) + 3;
			else if (stack.top() == '<')
				score = (score * 5) + 4;
			stack.pop();
		}
		scores.push_back(score);
	}

	std::sort(std::begin(scores), std::end(scores));
	return scores[scores.size() / 2];
}

int main()
{
	auto input = Utility::ReadFromFileToString("../input.txt");

	std::cout << "**Part 1** = " << GetCorruptionValue(input) << "\n";
	std::cout << "**Part 2** = " << MiddleFixedScore(input) << "\n";
}
