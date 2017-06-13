
/* solver.cpp
 *
 * Luke Justice (lmjustic@umich.edu)
 * Last Updated: 2017-05-05
 * 
 * This program is meant to solve Picture Cross puzzles 
 * (How to Play: https://youtu.be/d-I5Ng2oYyM) by using a backtracking
 * algorithm provided the rows and columns.
 *
 */

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <getopt.h>

#include "board.h"

using namespace std;


void printHelp(char* function);
void readBoard(ifstream& ifs, vector<vector<int>>& rows,
	vector<vector<int>>& cols);
/*bool solve(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols);*/
bool isValid(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols, pair<size_t, size_t>& pos);
void printBoard(vector<vector<int>>& board, ofstream& ofs);


// Driver for the Picross Solver
int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(false);

	string infilename = "";
	string outfilename = "";
	ifstream ifs;
	ofstream ofs;

	vector<vector<int>> rows;
	vector<vector<int>> cols;
	vector<vector<int>> board;

	// These are used with getopt_long()
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;
    option long_options[] = {
        { "help", no_argument, nullptr, 'h' },
        { "infile", required_argument, nullptr, 'i' },
        { "outfile", required_argument, nullptr, 'o' },
        { nullptr, 0, nullptr, '\0' }
    };

    while ((choice = getopt_long(argc, argv, "hi:o:", long_options,
        &option_index)) != -1) {

        switch (choice) {
        case 'h':
            printHelp(argv[0]);
            return 0;

        case 'i':
        	infilename = optarg;
        	break;

        case 'o':
        	outfilename = optarg;
        	break;

        default:
            cerr << "Error: invalid option " << choice << endl;
            return 1;
        }
    }

    // Makes sure the input file opens
    ifs.open(infilename);
    if (!ifs.is_open()) {
    	cerr << "Error: " << infilename << " could not be opened" << endl;
    	return 1;
    }

    // Read the input file
    try {
    	readBoard(ifs, rows, cols);
    } catch (exception& e) {
    	cerr << e.what() << endl;
        ifs.close();
    	return 1;
    }

    ifs.close();

    for (size_t i = 0; i < rows.size(); i++) {
        board.emplace_back();
        board[i].resize(cols.size(), -1);
    }

    // Makes sure the output file opens
    ofs.open(outfilename);
    if (!ofs.is_open()) {
    	cerr << "Error: " << outfilename << " could not be opened" << endl;
    	return 1;
    }

    printBoard(board, ofs);

    ofs.close();
	return 0;
} // main()


// Prints usage help 
void printHelp(char* function) {
    cout << "Usage: " << function << " -i \"infile\" -o \"outfile\"\n";
    cout << "This program finds the solution to a Picture Cross puzzle \n";
    cout << "using a backtracking algorithm and prints the file as a png \n";
    cout << "file." << endl;
} // printHelp()


void readBoard(ifstream& ifs, vector<vector<int>>& rows,
	vector<vector<int>>& cols) {

	stringstream ss;
	size_t numRows, numCols;
	int value;
	string line = "#";

	// Reading the boardsize ignoring columns
	while (line[0] == '#') {
		getline(ifs, line);
	}
	ss.str(line);
	if (!(ss >> numRows >> numCols)) {
		throw runtime_error("Error: board dimensions could not be read\n");
	}

	rows.reserve(numRows);
	cols.reserve(numCols);

	// Reading the row values ignoring comments
	for (size_t i = 0; i < numRows; i++) {
		rows.emplace_back();

        // Ignoring comments
		line = "#";
		while (line[0] == '#') {
			getline(ifs, line);
		}
        ss.clear();
		ss.str(line);
		
        // Appending all values on the line
		while (ss >> value) {
			rows[i].push_back(value);
		}

		// Ensures that there is an entry for the row
		if (rows[i].size() == 0) {
			throw runtime_error("Error: rows could not be read\n");
		}
	}

	// Reading the column values ignoring comments
	for (size_t i = 0; i < numCols; i++) {
		cols.emplace_back();

        // Ignoring comments
		line = "#";
		while (line[0] == '#') {
			getline(ifs, line);
		}
        ss.clear();
		ss.str(line);
		
        // Appending all values on the line
		while (ss >> value) {
			cols[i].push_back(value);
		}

		// Ensures that there is an entry for the column
		if (cols[i].size() == 0) {
			throw runtime_error("Error: columns could not be read\n");
		}
	}
} // readBoard()

/*
bool solve(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols) {

	return true;
} // solve()
*/

bool isValid(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols, pair<size_t, size_t>& pos) {

    size_t rowPos = 0;
    size_t colPos = 0;
    int count = 0;
    int sum = 0;
    int unfilled = 0;

    /*// Inserted position is a blank square
    if (board[pos.first][pos.second] == 0) {
        // Check the row until the inserted position
        for (size_t i = 0; i <= pos.second; i++) {
            // Count the segment length
            if (board[pos.first][i] == 1) {
                // Don't need to check if too many segments since a segment
                // cannot be created with a blank square
                count++;
                sum++;
            }
            // End of segment
            else {
                if (count != 0) {
                    if (count != rows[pos.first][rowPos]) {
                        // Incorrect length found
                        return false;
                    }
                    count = 0;
                    rowPos++;
                }
            }

        }

        return true;
    }*/

    // Check the row until the inserted position
    for (size_t i = 0; i <= pos.second; i++) {

        // Count the segment length
        if (board[pos.first][i] == 1) {
            if (rowPos == rows.size()) {
                // Too many segments
                return false;
            }
            count++;
        }

        // End of segment
        else {
            if (count != 0) {
                if (count != rows[pos.first][rowPos]) {
                    // Incorrect length found
                    return false;
                }
                count = 0;
                rowPos++;
            }
        }
    }

    if (count > rows[pos.first][rowPos]) {
        // Inserted filled tile made the segment too long
        return false;
    }

    // Calculating the minimum number of tiles in row to fill requirement
    unfilled = -1 - count;
    for (size_t i = rowPos; i < rows[pos.first].size(); i++) {
        unfilled += rows[pos.first][i] + 1;
    }

    if (unfilled > (cols.size() - pos.second - 1)) {
        // Number of unchecked tiles is less than minimum required to solve
        return false;
    }

    count = 0;
    sum = 0;
    unfilled = 0;

    // Check the column until the inserted position
    for (size_t i = 0; i <= pos.first; i++) {

    	// Count the segment length
    	if (board[i][pos.second] == 1) {

    	}

    	// End of segment

    }

	return true;
} // isValid()


void printBoard(vector<vector<int>>& board, ofstream& ofs) {
	// TODO: Write as an image format
	for (size_t i = 0; i < board.size(); i++) {
		for (size_t j = 0; j < board[i].size(); j++) {
			ofs << board[i][j] << " ";
		}
		ofs << endl;
	}
} // printBoard()
