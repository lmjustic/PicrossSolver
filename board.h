#ifndef BOARD_H
#define BOARD_H

#include <string>		// std::string
#include <utility>		// std::pair
#include <vector>		// std::vector

class Board {
public:
	Board(std::ifstream& ifs);
	Board(std::string& filename);
	void initBoard();
	void read(std::ifstream& ifs);
	bool solve();
	void print(std::ofstream& ofs);
	void print(std::string& filename);
	
private:
	bool isValid(std::pair<std::size_t, std::size_t>& pos);

	std::vector<std::vector<std::size_t>> rows;
	std::vector<std::vector<std::size_t>> cols;
	std::vector<std::vector<std::size_t>> state;
	std::size_t numRows;
	std::size_t numCols;
};

#endif