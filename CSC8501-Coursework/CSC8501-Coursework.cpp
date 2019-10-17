#include <iostream>
#include <vector>

using namespace std;

int factorial(int n) {
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}

int findConRows(int ind, int* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (arr[ind] == arr[i] - 1) {
			for (int j = 0; j < size; j++) {
				if (arr[i] == arr[j] - 1)
					return (factorial(size - 2)) + (factorial(size - 3) / 2);
			}
			return (factorial(size - 2) / 2);
		}
	}
	return 0;
}

int bruteforce(int* board) {
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
																if (board[a] == board[b] - 1 && board[b] == board[c] - 1) {
																	rows++;
																} else if (board[d] == board[e] - 1 && board[e] == board[f] - 1) {
																	rows++;
																} else if (board[g] == board[h] - 1) {
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
	int* board = new int[array_size] { 1, 18, 6, 7, 8, 9, 16, 13};
	int rowNum = 0;

	for (int i = 0; i < array_size; i++) {
		rowNum += findConRows(i, board, array_size);
	}

	;
	cout << rowNum << endl;
	cout << bruteforce(board) << endl;
}

