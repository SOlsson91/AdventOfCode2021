#include "Utility.h"

struct BingoNumber
{
	uint32_t number = 0;
	bool marked = false;
};

struct BingoBoard
{
	std::vector<BingoNumber> board;
	bool bingo = false;
};

std::vector<BingoBoard> GetBoardsData(const std::vector<std::string>& rows)
{
	std::vector<BingoBoard> boards;
	BingoBoard board;

	for (uint32_t i = 2; i < rows.size(); ++i)
	{
		if (rows[i].size() == 0)
		{
			board.bingo = false;
			boards.push_back(board);
			board.board.clear();
			continue;
		}
		std::vector<std::string> row = Utility::SplitString(rows[i]);
		for (const auto& number : row)
		{
			BingoNumber bingoNumber;
			bingoNumber.number = std::stoi(number);
			bingoNumber.marked = false;
			board.board.emplace_back(bingoNumber);
		}
	}
	boards.emplace_back(board);

	return boards;
}

bool IsBingo(const BingoBoard& board, uint32_t lastBingoPos, uint32_t& bingoSum)
{
	const uint32_t BOARDWIDTH = 5;
	uint32_t column = lastBingoPos / BOARDWIDTH;
	uint32_t row = lastBingoPos % BOARDWIDTH;


	bool rowBingo = true;
	for (uint32_t r = 0; r < 5; r++)
	{
		uint32_t index = r + BOARDWIDTH * column;
		if (board.board[index].marked == false)
		{
			rowBingo = false;
			break;
		}
	}
	if (rowBingo)
	{
		for (const auto& b : board.board)
		{
			bingoSum += (b.marked) ? 0 : b.number;
		}
		return true;
	}

	bool columnBingo = true;
	for (uint32_t c = 0; c < 5; c++)
	{
		uint32_t index = row + BOARDWIDTH * c;
		if (board.board[index].marked == false)
		{
			columnBingo = false;
			break;
		}
	}
	if (columnBingo)
	{
		for (const auto& b : board.board)
		{
			bingoSum += (b.marked) ? 0 : b.number;
		}
		return true;
	}

	return false;
}

uint32_t FirstBingo(std::vector<BingoBoard> boards, const std::vector<uint32_t>& bingoNumbers)
{
	Timer t;
	for (uint32_t i = 0; i < bingoNumbers.size(); i++)
	{
		for (auto& bingoBoard : boards)
		{
			for (uint32_t pos = 0; pos != bingoBoard.board.size(); pos++)
			{
				if (bingoBoard.board[pos].number == bingoNumbers[i])
				{
					bingoBoard.board[pos].marked = true;

					uint32_t bingoSum = 0;
					if (IsBingo(bingoBoard, pos, bingoSum))
					{
						return bingoSum * bingoNumbers[i];
					}
					break;
				}
			}
		}
	}
	return 0;
}

uint32_t LastBingo(std::vector<BingoBoard> boards, const std::vector<uint32_t>& bingoNumbers)
{
	Timer t;
	uint32_t boardsWithBingo = 0;
	for (uint32_t i = 0; i < bingoNumbers.size(); i++)
	{
		for (auto& bingoBoard : boards)
		{
			if (bingoBoard.bingo)
				continue;
			for (uint32_t pos = 0; pos != bingoBoard.board.size(); pos++)
			{
				if (bingoBoard.board[pos].number == bingoNumbers[i])
				{
					bingoBoard.board[pos].marked = true;

					uint32_t bingoSum = 0;
					if (IsBingo(bingoBoard, pos, bingoSum))
					{
						bingoBoard.bingo = true;

						boardsWithBingo++;
						if (boardsWithBingo == boards.size())
							return bingoSum * bingoNumbers[i];
					}
					break;
				}
			}
		}
	}
	return 0;
}

int main()
{
	std::vector<std::string> rows = Utility::ReadFromFileToString("../input.txt");
	std::vector<uint32_t> bingoNumbers = Utility::SplitStringToInt(rows[0], ",");
	std::vector<BingoBoard> boards = GetBoardsData(rows);

	std::cout << "**Part 1** = " << FirstBingo(boards, bingoNumbers) << "\n";
	std::cout << "**Part 2** = " << LastBingo(boards, bingoNumbers) << "\n";
}
