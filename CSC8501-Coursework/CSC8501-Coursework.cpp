#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include "Puzzle.h"
#include <limits.h>
#include <filesystem>

//@author: David Towers (160243066)

using namespace std;

//Constants used by program
const string CON_FILE = "15-File.txt";
const string RES_FILE = "Solution-File.txt";
char* OPT = new char[2]{ 'y', 'n' };

//takes in options as characters
char charIn(string msg, char* options, int size){
	char input;
	bool loop;
	do {
		loop = false;
		cout << msg;
		cin >> input;
		bool match = false;
		for (int i = 0; i < size; i++)
			if (tolower(input) == options[i])
				match = true;
		if (cin.fail() || !match) {
			cin.clear();
			loop = true;
			string validChars = "";
			for (int i = 0; i < size; i++)
				validChars = validChars + options[i] + " ";
			cout << "Invalid input, please enter either: " << validChars << endl;
		}
	} while (loop);	
	return tolower(input);
}

//takes in options as ints
int intInInc(string msg, int lowerBound, int upperBound) {
	int input;
	bool loop;
	do {
		cout << msg;
		loop = false;
		cin >> input;
		if (cin.fail() || input < lowerBound || input > upperBound) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			loop = true;
			cout << "Invalid input, please enter an integer between " << lowerBound << " and " << upperBound << " inclusively" << endl;
		}
	} while (loop);
	return input;
}

//allows the user to enter a 4 x 4 manually
vector<int> manual() {
	cout << "Please Enter in 15 Numbers (1-20) to make up your configuration" << endl;
	vector<int> config = vector<int>();
	for (int i = 0; i < 15; i++) {
		bool used = false;
		int x = intInInc("Please enter Number " + to_string(i + 1) + ": ", 1, 20);
		for (int i : config)
			if (i == x)
				used = true;
		if (!used)
			config.push_back(x);
		else {
			cout << "That number has already been used. Please enter a number that hasn't been used" << endl;
			i--;
		}
	}
	return config;
}

//save the results to a file
void saveResults(vector<Puzzle> vec, bool part) throw (invalid_argument){
	ofstream output;
	char* invalidChars = new char[9]{ '\\', '/', '<', '>', '"', '|', ':', '?', '*' };
	int inCh = RES_FILE.find(invalidChars, 0, 1);
	if (inCh != -1)
		throw (invalid_argument("Invalid Characters in filename: " + RES_FILE.substr(inCh, inCh + 1)));
	output.open(RES_FILE.c_str());
	if (output.fail()) {
		throw (invalid_argument("file could not be created: " + RES_FILE));
	}

	output << vec.size() << endl;
	for (Puzzle p: vec)
		output << (part ? p.parString() : p.resultString(true)) << endl;
	output.close();
}

//load configurations from file
vector<Puzzle> loadConfigurations(vector<Puzzle> vec) throw (invalid_argument) {
	ifstream input;
	char* invalidChars = new char[9]{ '\\', '/', '<', '>', '"', '|', ':', '?', '*' };
	int inCh = CON_FILE.find(invalidChars, 0, 1);
	if (inCh != -1)
		throw (invalid_argument("Invalid Characters in filename: " + CON_FILE.substr(inCh, inCh + 1)));
	input.open(CON_FILE.c_str());
	if (input.fail())
		throw (invalid_argument("no file exists " + CON_FILE));
	
	vector<int> temp;
	int buff;
	int num;
	int size;
	input >> num;
	
	while(input >> buff)
		temp.push_back(buff);
	size = temp.size()/num;

	for (int i = 0; i < num; i++) {
		vector<int> newVec(temp.begin() + (i * size), temp.begin() + ((i + 1) * size));
		vec.push_back(Puzzle(newVec));
		
	}
	input.close();
	return vec;
}

//allows the user to decide how they want to make the puzzle
vector<Puzzle> checkEntry(vector<Puzzle> vec) throw (invalid_argument) {
	int num = 1;
	int dim = 1;
	char* opts = new char[3]{ 'm', 'r', 'l' };
	string msg = "Would you like to manually (m) enter a puzzle or randomly (r) generate Puzzles or load (l) from file?: ";
	char choice = charIn(msg, opts, 3);
	switch (choice) {
		case ('m'):
			vec.push_back(Puzzle(manual()));
			break;
		case ('r'):
			num = intInInc("How many puzzles would you like to generate?: ", 1, 20);
			dim = intInInc("How large would you like the Puzzle (x by x) x = ", 3, 1000);
			for (int i = 0; i < num; i++) {
				vec.push_back(Puzzle(dim));
				vec.at(i).genPuzzle();
			}
			break;
		case ('l'):
			try {
				vec = loadConfigurations(vec);
			} catch (...) {
				throw;
			}
			break;
	}
	return vec;
}

//prints board to screen
void boardToScreen(vector<Puzzle> vec) {
	cout << vec.size() << endl;
	for (Puzzle p : vec)
		cout << p << "\n" << endl;
}

//saves the configuration to file
void saveConFunction(vector<Puzzle> vec) throw(invalid_argument) {
	boardToScreen(vec);
	cout << "Saving Configuration" << endl;
	ofstream output;
	char* invalidChars = new char[9]{ '\\', '/', '<', '>', '"', '|', ':', '?', '*' };
	int inCh = CON_FILE.find(invalidChars, 0, 1);
	if (inCh != -1)
		throw (invalid_argument("Invalid Characters in filename: " + CON_FILE.substr(inCh, inCh + 1)));
	output.open(CON_FILE.c_str());
	if (output.fail())
		throw (invalid_argument("file could not be created " + CON_FILE));
	output << vec.size() << endl;
	for (Puzzle p : vec)
		output << p << "\n" << endl;
	output.close();
}

//prints results to screen
void resToScreen(vector<Puzzle> vec, bool part) {
	cout << vec.size() << endl;
	for (Puzzle p : vec) {
		cout << (part ? p.parString(): p.resultString(true)) << "\n" << endl;
	}
}

//allows the user to show and save results
void saveResFunction(vector<Puzzle> vec) {
	char contin = charIn("Would you like find the full continous rows, columns and inverses? (Y or N): ", OPT, 2);
	if (contin == 'y') {
		char wild = charIn("Would you like the empty space to act as a wilcard? (Y or N): ", OPT, 2);
		if (wild == 'y') {
			for (int i = 0; i < vec.size(); i++)
				vec.at(i).setWildCard(true);
		}
		char part = charIn("Would you like to calculate partial rows as well? (Y or N): ", OPT, 2);
		resToScreen(vec, part == 'y');
		cout << "Saving Results" << endl;
		try {
			saveResults(vec, part == 'y');
		} 
		catch (...) {
			throw;
		}
	}
}

//tests how fast the threaded and unthreaded funtions are
void speedTest(vector<Puzzle> vec) {
	char race = charIn("Would you like to see if the threaded function is faster?: ", OPT, 2);
	if (race == 'y') {
		clock_t beginThread = clock();
		vec.at(0).getResult(true);
		clock_t endThread = clock();
		clock_t beginUnThread = clock();
		vec.at(0).getResult(false);
		clock_t endUnThread = clock();
		cout << "Threaded Function took " << double(endThread - beginThread) / CLOCKS_PER_SEC << endl;
		cout << "Unthreaded Function took " << double(endUnThread - beginUnThread) / CLOCKS_PER_SEC << endl;
	}
}

int main() {
	bool repeat = true;
	while (repeat) {
		vector<Puzzle> vec;
		srand(time(0));
		try {
			vec = checkEntry(vec);
			saveConFunction(vec);
			saveResFunction(vec);
		}
		catch (invalid_argument& iae) {
			cout << "Error Inputting/outputitng files: " << iae.what() << endl;
			exit(1);
		}
		char* opt = new char[2]{ 'y', 'n' };
		speedTest(vec);
		char choice = charIn("Would you like to restart the program? (Y or N): ", opt, 2);
		if (choice == 'n')
			repeat = false;
	}
}