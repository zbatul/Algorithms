/*
 * Name: Batul Zamin
 * Class: CS301 Data Structures
 * Program: A C++ program to solve a Boggle Board and find all the words in it using a given dictionary.
 */

#include "Dictionary.h"

// global variables
bool verbose = false;
int numWords = 0;
int stepnum = 0;
ofstream outFile;      // file containing output

// Declare function prototypes
void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard);
void SearchForWord(int row, int col, int step[4][4], string path, string board[4][4], Dictionary& dict, 
	Dictionary& wordsFound, bool visited[4][4]);
void PrintBoard(string word, string board[4][4], int step[4][4]);
void PrintWord(string word);

// main driver dunction
int main() {
	// declare local variables
	ifstream inFile;       // file containing operations
	string inFileName;     // input file external name
	string outFileName;    // output file external name
	string outputLabel;
	string command;		   // operation to be executed
	string board[4][4];

	// Prompt for file names, read file names, and prepare files
	cout << "Enter name of input command file; press return." << endl;
	cin >> inFileName;
	inFile.open(inFileName.c_str());

	cout << "Enter name of output file; press return." << endl;
	cin >> outFileName;
	outFile.open(outFileName.c_str());

	cout << "Enter name of test run; press return." << endl;
	cin >> outputLabel;
	outFile << outputLabel << endl << endl;

	if (!inFile) {
		cout << "file not found" << endl;
		exit(2);
	}

	Dictionary dict("dictionary.txt");
	cout << dict.wordCount() << " words loaded." << endl;
	outFile << dict.wordCount() << " words loaded." << endl;

	/*// Below is some code to help you test your dictionary...
	string word;
	while (cout << "Enter string: " && cin >> word) {
		if (dict.isWord(word)) {
			cout << word << " is a valid word" << endl;
		}
		else {
			cout << word << " is NOT a valid word" << endl;
		}
		if (dict.isPrefix(word)) {
			cout << word << " is a valid prefix" << endl;
		}
		else {
			cout << word << " is NOT a valid prefix" << endl;
		}
		cout << endl;
	}
	*/

	while (inFile >> command && command != "QUIT") {
		numWords = 0;
		// Enter Board from inputFile
		cout << endl << "Enter Board" << endl << "------------" << endl;
		outFile << endl << "Enter Board" << endl << "------------" << endl;
		for (int r = 0; r < 4; r++) {
			cout << "Row " << r << ": ";
			outFile << "Row " << r << ": ";
			for (int c = 0; c < 4; c++) {
				inFile >> board[r][c];
				cout << board[r][c] << " ";
				outFile << board[r][c] << " ";
			}
			cout << endl;
			outFile << endl;
		}
		char showBoard;
		cout << "Show Board (y/n)?: ";
		outFile << "Show Board (y/n)?: ";
		inFile >> showBoard;
		cout << showBoard << endl;
		outFile << showBoard << endl;

		// Solve the Boggle by finding all the words.
		Dictionary wordsFound;
		if (showBoard == 'y') {
			SolveBoard(board, dict, wordsFound, true);
		}
		else {
			SolveBoard(board, dict, wordsFound, false);
		}
	}
	cout << "Testing completed." << endl;
	outFile << "Testing completed." << endl;
	inFile.close();
	outFile.close();
	return 0;
}

void SolveBoard(string board[4][4], Dictionary& dict, Dictionary& wordsFound, bool printBoard) {
// pre: takes input board, the dictionary and a dictionary to store found words. 
//      Also takes parameter whether to print the board or not
// post: Boggle is solved and all the words are found using Helper Function SearchForWord
	string path = "";
	bool visited[4][4] = { {false} };
	Dictionary wordsFoundDict;
	verbose = printBoard;
	// process the Board
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (dict.isPrefix(path)) {
				path += board[r][c];
				int step[4][4] = { {0} };
				stepnum = 0;
				SearchForWord(r, c, step, path, board, dict, wordsFound, visited);
				path = "";
			}
		}
	}
}

bool canVisit(int r, int c, bool visited[4][4]) {
// post: returns true if we can visit (r,c) coordinate in the board safely
	return (r >= 0 && r < 4 && c >= 0 && c < 4 && !visited[r][c]);
}

void SearchForWord(int row, int col, int step[4][4], string path, string board[4][4], Dictionary& dict, 
	Dictionary& wordsFound, bool visited[4][4]) {
// post: finds words on the board recursively
	step[row][col] = ++stepnum;
	// If word is present then print the word and the board (if verbose is true)
	if (dict.isWord(path) && path.length() >= 3 && !wordsFound.isWord(path)) {
		wordsFound.addWord(path);
		numWords++;
		if (verbose)
			PrintBoard(path, board, step);
		else
			PrintWord(path);
	}
	if (canVisit(row, col, visited)) {
		visited[row][col] = true;
		for (int a = 0; a < ALPHABET_SIZE && dict.isPrefix(path); a++) {
			// load current character in string ch
			char x = 'a' + a;
			string ch = "";
			ch = x;
			// Recursively Traverse the 8 adjacent cells of board[row][col]  
			if (canVisit(row + 1, col + 1, visited) && board[row + 1][col + 1] == ch)
				SearchForWord(row + 1, col + 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row, col + 1, visited) && board[row][col + 1] == ch)
				SearchForWord(row, col + 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row - 1, col + 1, visited) && board[row - 1][col + 1] == ch)
				SearchForWord(row - 1, col + 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row + 1, col, visited) && board[row + 1][col] == ch)
				SearchForWord(row + 1, col, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row + 1, col - 1, visited) && board[row + 1][col - 1] == ch)
				SearchForWord(row + 1, col - 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row, col - 1, visited) && board[row][col - 1] == ch)
				SearchForWord(row, col - 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row - 1, col - 1, visited) && board[row - 1][col - 1] == ch)
				SearchForWord(row - 1, col - 1, step, path + ch, board, dict, wordsFound, visited);
			if (canVisit(row - 1, col, visited) && board[row - 1][col] == ch)
				SearchForWord(row - 1, col, step, path + ch, board, dict, wordsFound, visited);
		}
	}
	visited[row][col] = false;
	stepnum--;
	step[row][col] = 0;
}

void PrintBoard(string word, string board[4][4], int step[4][4]) {
// pre: takes word, the board and step-board as parameters
// post: prints the word and the board alongwith the step-board
	cout << "Word: " << word << endl;
	cout << "Number of Words: " << numWords << endl;
	outFile << "Word: " << word << endl;
	outFile << "Number of Words: " << numWords << endl;
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (step[r][c] != 0) {
				cout << "\'" << board[r][c] << "\'\t";
				outFile << "\'" << board[r][c] << "\'\t";
			}
			else {
				cout << " " << board[r][c] << " \t";
				outFile << " " << board[r][c] << " \t";
			}
		}
		cout << "\t";
		outFile << "\t";
		for (int c = 0; c < 4; c++) {
			cout << step[r][c] << "\t";
			outFile << step[r][c] << "\t";
		}
		cout << endl;
		outFile << endl;
	}
}

void PrintWord(string word) {
// pre: takes word to print as parameter
// post: prints the word and word number to console and output file
	cout << numWords << "\t" << word << endl;
	outFile << numWords << "\t" << word << endl;
}
