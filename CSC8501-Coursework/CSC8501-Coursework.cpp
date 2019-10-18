#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include "Puzzle.h"

using namespace std;

//Functions used by class, but not apart of object
int factoriall(int n) {
	if (n == 1)
		return 1;
	return n * factoriall(n - 1);
}


int Test(vector<int>* board) {
	int trips = 0;
	int dubs = 0;
	for (int i = 0; i < board->size() - 1; i++) {
		if (board->at(i) == board->at(i + 1) - 1) {
			dubs++;
			if (i != board->size() - 2 && board->at(i) == board->at(i + 2) - 2)
				trips++;
		}
	}

	return (dubs * factoriall(8 - 2)) / 2 + (trips * factoriall(8 - 3));
}

int main() {
	int array_size = 8;
	Puzzle three = Puzzle(4);
	three.genPuzzle();
	//vector<int>* board = new vector<int>{ 1, 18, 6, 7, 8, 9, 16, 13 };
	//vector<int>* board = new vector<int>{ 1, 2, 3, 4, 5, 6, 7, 8, };
	vector<int>* board = new vector<int>{ 4, 19, 12, 6, 18, 3, 17, 10, 2, 9, 16, 5, 15, 11, 7 };
	cout << "Object: " << three.calcComRows()  << endl;
	cout << "Old Method: " << Test(board) << endl;

}

