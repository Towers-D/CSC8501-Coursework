#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int factorial(int n) {
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}

int findConRows(vector<int>* vec, int groupNum) {
	int trips = 0;
	int dubs = 0;
	int* rArr = new int[groupNum + 1];
	rArr[0] = 0;
	rArr[1] = 0;
	sort(vec->begin(), vec->end());

	for (int i = 2; i < groupNum; i++) {

	}

	for (int i = 0; i < 8 - 1; i++) {
		if (vec->at(i) == vec->at(i + 1) - 1) {
			dubs++;
			if (vec->at(i) == vec->at(i + 2) - 2)
				trips++;
		}
	}

	return (dubs * factorial(8 - 2))/2 + (trips * factorial(8 - 3));
}

int bruteforce(vector<int>* board) {
	int rows = 0;
	for (int a = 0; a < 8; a++) {
		for (int b = 0; b < 8; b++) {
			if (b != a) {
				for (int c = 0; c < 8; c++) {
					if (c != a && c != b) {
						for (int d = 0; d < 8; d++) {
							if (d != a && d != b && d != c) {
								for (int e = 0; e < 8; e++) {
									if (e != a && e != b && e != c && e != d) {
										for (int f = 0; f < 8; f++) {
											if (f != a && f != b && f != c && f != d && f != e) {
												for (int g = 0; g < 8; g++) {
													if (g != a && g != b && g != c && g != d && g != e && g != f) {
														for (int h = 0; h < 8; h++) {
															if (h != a && h != b && h != c && h != d && h != e && h != f && h != g) {
																if (board->at(a) == board->at(b) - 1 && board->at(b) == board->at(c) - 1) {
																	rows++;
																} 
																else if (board->at(d) == board->at(e) - 1 && board->at(e) == board->at(f) - 1) {
																	rows++;
																} 
																else if (board->at(g) == board->at(h) - 1) {
																	rows++;
																}
															}
														}
													}
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return rows / 2;
}

int main() {
	int array_size = 8;
	vector<int>* board = new vector<int> { 1, 18, 6, 7, 8, 9, 16, 13};
	int rowNum = findConRows(board, 3);


	cout << rowNum << endl;
	cout << bruteforce(board) << endl;
}

