#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

int factorial(int n) {
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}

int calcFullRows(int* arr, int rowMax, int boardsize) {
	int numRows = sqrt(boardsize + 1);
	int val = 0;
	cout << boardsize << endl;
	for (int i = 2; i <= rowMax; i++)
		val += (arr[i] * factorial(boardsize - i) / 2) * ((i == numRows - 1) ? 1 : numRows - 1);
	return val;
}

int* findConRows(vector<int>* vec, int groupNum) {

	int* rArr = new int[groupNum + 1];
	sort(vec->begin(), vec->end());

	for (int i = 2; i <= groupNum; i++) {
		int count = 0;
		for (int j = 0; j < vec->size() - i; j++) {
			int check = 0;
			for (int x = 0; x < i; x++) {
				if (vec->at(j) == vec->at(j + x) - x)
					check++;
			}
			if (check == i)
				count++;
		}
		rArr[i] = count;
	}
	return rArr;
}

int Test(vector<int>* board) {
	int trips = 0;
	int dubs = 0;
	for (int i = 0; i < board->size() - 1; i++) {
		if (board->at(i) == board->at(i + 1) - 1) {
			dubs++;
			if (board->at(i) == board->at(i + 2) - 2)
				trips++;
		}
	}

	return (dubs * factorial(8 - 2)) / 2 + (trips * factorial(8 - 3));
}

int main() {
	int array_size = 8;
	vector<int>* board = new vector<int>{ 1, 18, 6, 7, 8, 9, 16, 13 };
	int* results = findConRows(board, 3);
	for (int i = 0; i < 4; i++)
		cout << results[i] << " ";
	//cout << rowNum << endl;
	cout << Test(board) << endl;
}

