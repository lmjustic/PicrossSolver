/* solver.cpp
 * Luke Justice (lmjustic@umich.edu)
 * Last Updated: 2017-04-29
 * 
 * This program is meant to solve Picture Cross puzzles 
 * (How to Play: https://youtu.be/d-I5Ng2oYyM) by using a backtracking
 * algorithm provided the rows and columns.
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <getopt.h>

using namespace std;


void printHelp(char* function);
bool solve(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols);
bool isValid(vector<vector<int>>& board, vector<vector<int>>& rows, 
	vector<vector<int>>& cols, pair<size_t, size_t>& pos);
void printBoard(vector<vector<int>>& board);


int main(int argc, char *argv[]) {
	std::ios_base::sync_with_stdio(false);

	string infilename = "";
	string outfilename = "";

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
            return(0);

        case 'i':
        	infilename = optarg;
        	break;

        case 'o':
        	outfilename = optarg;
        	break;

        default:
            cerr << "Error: invalid option " << choice << endl;
            return(1);
        } // switch
    } // while



	return 0;
} // main()


// Prints a usage help 
void printHelp(char* function) {
    cout << "Usage: " << function << " -i \"infile\" -o \"outfile\"\n";
    cout << "This program finds the solution to a \n";
    cout << "find the minimum spanning tree to for a trade route using \n";
    cout << "Prim's, and find the best path using the travelling salesman \n";
    cout << "solution" << endl;;
} // printHelp()
