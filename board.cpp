
#include "board.h"

using namespace std;

Board::Board(ifstream& ifs) {
	ifs >> this->numRows >> this->numCols;
	this->initBoard();
	this->read(ifstream& ifs);
}

Board::Board(string& string) {
	
}

void Board::initBoard() {
	this->rows.reserve(this->numRows);
	this->cols.reserve(this->numCols);
	this->state.reserve(this->numCols);

	for (size_t i = 0; i < this->numRows; i++) {
		this->rows.emplace_back();
		this->state.emplace_back();
	}

	for (size_t i = 0; i < this->numCols; i++) {
		this->cols.emplace_back();
	}
}

void Board::read(ifstream& ifs) {

}