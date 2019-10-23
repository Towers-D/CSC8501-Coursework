#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <fstream>
#include "Puzzle.h"
#include <limits.h>

using namespace std;

const string CON_FILE = "15-File";
const string RES_FILE = "Solution-File";

char charIn(string msg, char* options, int size){
	char input;
	bool loop;
	do {
		loop = false;
		cout << msg;
		cin >> input;
		bool match = false;
		for (int i = 0; i < size; i++)
			if (input == options[i])
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
	return input;
}

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

void saveResults(vector<Puzzle> vec) {
	ofstream output(RES_FILE.c_str());
	output << vec.size() << endl;
	for (Puzzle p: vec)
		output << p.resultString();
	output.close();
}

vector<Puzzle> loadConfigurations(vector<Puzzle> vec) {
	ifstream input(CON_FILE.c_str());
	vector<int> temp;
	int buff;
	int num;
	input >> num;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < 24; j++) {
			input >> buff;
			temp.push_back(buff);
		}
		vec.push_back(Puzzle(temp));
		temp.clear();
	}
	return vec;
}

vector<Puzzle> checkEntry(vector<Puzzle> vec) {
	int num = 1;
	int dim = 1;
	char* opt = new char[3]{ 'm', 'r', 'l' };
	string msg = "Would you like to manually (m) enter a puzzle or randomly (r) generate Puzzles or load (l) from file?: ";
	char choice = charIn(msg, opt, 3);
	switch (choice) {
		case ('m'):
			vec.push_back(Puzzle(manual()));
			break;
		case ('r'):
			num = intInInc("How many puzzles would you like to generate?: ", 1, 20);
			dim = intInInc("How large would you like the Puzzle (x by x) x = ", 3, 10);
			for (int i = 0; i < num; i++) {
				vec.push_back(Puzzle(dim));
				vec.at(i).genPuzzle();
			}
			break;
		case ('l'):
			vec = loadConfigurations(vec);
			break;
	}
	return vec;
}

void boardToScreen(vector<Puzzle> vec) {
	cout << vec.size() << endl;
	for (Puzzle p : vec)
		cout << p << "\n" << endl;
}

void saveConFunction(vector<Puzzle> vec) {
	boardToScreen(vec);
	cout << "Saving Configuration" << endl;
	ofstream output(CON_FILE.c_str());
	output << vec.size() << endl;
	for (Puzzle p : vec)
		output << p << "\n" << endl;
	output.close();
}

void resToScreen(vector<Puzzle> vec) {
	cout << vec.size() << endl;
	for (Puzzle p : vec) {
		cout << p.resultString() << endl;
	}
}

void saveResFunction(vector<Puzzle> vec) {
	char* opt = new char[2]{ 'y', 'n' };
	char contin = charIn("Would you like find the full continous rows, columns and inverses? (Y or N): ", opt, 2);
	if (contin == 'y') {
		char wild = charIn("Would you like the empty space to act as a wilcard (Y or N): ", opt, 2);
		if (wild == 'y') {
			for (int i = 0; i < vec.size(); i++)
				vec.at(i).setWildCard(true);
		}
		resToScreen(vec);
		cout << "Saving Results" << endl;
		saveResults(vec);
	}
}

int main() {
	bool repeat = true;
	while (repeat) {
		vector<Puzzle> vec;
		srand(time(0));
		vec = checkEntry(vec);
		saveConFunction(vec);
		saveResFunction(vec);

		char* opt = new char[2]{ 'y', 'n' };
		char choice = charIn("Would you like to restart the program? (Y or N): ", opt, 2);
		if (choice == 'n')
			repeat = false;
	}
}