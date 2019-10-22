#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include "Puzzle.h"

using namespace std;

const string CON_FILE = "15-File";
const string RES_FILE = "Solution-File";

//Functions used by class, but not apart of object
int factoriall(int n) {
	if (n == 1)
		return 1;
	return n * factoriall(n - 1);
}

//vector<int>* board = new vector<int>{ 1, 18, 6, 7, 8, 9, 16, 13 };
//vector<int>* board = new vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, };
//vector<int>* board = new vector<int>{ 4, 19, 12, 6, 18, 3, 17, 10, 2, 9, 16, 5, 15, 11, 7 };

vector<int> manual() {
	cout << "Please Enter in 15 Numbers (1-20) to make up your configuration" << endl;
	vector<int> config = vector<int>();
	int x;
	bool used;
	for (int i = 0; i < 15; i++) { // Limit Numbers to 1-20
		used = false;
		cout << "Please enter Number " << i + 1 << ": ";
		cin >> x;
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

void saveConfigurations(vector<Puzzle> vec) {
	ofstream output(CON_FILE.c_str());
	output << vec.size() << endl;
	for (Puzzle p : vec)
		output << p << "\n" << endl;
	output.close();
}

void saveResults(vector <Puzzle> vec) {
	ofstream output(RES_FILE.c_str());
	output << vec.size() << endl;
	for (Puzzle p : vec)
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
		for (int j = 0; j < 15; j++) {
			input >> buff;
			temp.push_back(buff);
		}
		vec.push_back(Puzzle(temp));
		temp.clear();
	}
	return vec;
}

int main() {
	bool repeat = true;
	while (repeat) {
		vector<Puzzle> vec;
		srand(time(0));
		char choice;
		int num = 1;
		cout << "Would you like to manually (m) enter a puzzle or randomly (r) generate Puzzles or load (l) from file?: ";
		cin >> choice;
		switch (choice) {
			case ('m'):
				vec.push_back(Puzzle(manual()));
				break;
			case ('r'):
				cout << "How many puzzles would you like to generate?: ";
				cin >> num;
				for (int i = 0; i < num; i++) {
					vec.push_back(Puzzle(4));
					vec.at(i).genPuzzle();
				}

				break;
			case ('l'):
				vec = loadConfigurations(vec);
				break;
		}

		cout << "Saving Configuration" << endl;
		saveConfigurations(vec);

		cout << vec.size() << endl;
		for (Puzzle p : vec) {
			cout << p.resultString() << endl;
		}

		cout << "Saving Results" << endl;
		saveResults(vec);

		cout << "Would you like to restart the program? (Y or N): ";
		cin >> choice;

		if (choice == 'n')
			repeat = false;
	}
}