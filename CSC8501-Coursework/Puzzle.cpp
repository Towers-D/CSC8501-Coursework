#include "Puzzle.h"

//@author: David Towers (160243066)

//Functions used by class, but not apart of object
InfInt factorial(InfInt n) {
	if (n == 1)
		return 1;
	return n * factorial(n - 1);
}


//Public Functions
Puzzle::Puzzle(int size) {
	rowColSize = size;
	//-1 for Blank space
	boardSpaces = (rowColSize * rowColSize) - 1;
	//-1 as we never calculate contuous rows of size 1
	results = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = 0;
	parArr = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		parArr[i] = 0;
	givPar = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		givPar[i] = 0;
	for (int i = 0; i < boardSpaces; i++)
		board.push_back(0);
	wildCard = 0;
}

Puzzle::Puzzle(vector<int> config) {
	rowColSize = sqrt(config.size() + 1);
	boardSpaces = config.size();
	results = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = 0;
	parArr = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		parArr[i] = 0;
	givPar = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		givPar[i] = 0;
	for (int i : config)
		board.push_back(i);
	wildCard = 0;
}

Puzzle::Puzzle(const Puzzle &rhs) {
	rowColSize = rhs.rowColSize;
	boardSpaces = rhs.boardSpaces;
	results = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		results[i] = rhs.results[i];
	parArr = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		parArr[i] = rhs.parArr[i];
	givPar = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		givPar[i] = rhs.givPar[i];
	for (int i : rhs.board)
		board.push_back(i);
	wildCard = rhs.wildCard;
}

Puzzle& Puzzle::operator=(const Puzzle& rhs) {
	if (this == &rhs) return (*this);
	delete[] results;
	rowColSize = rhs.rowColSize;
	boardSpaces = rhs.boardSpaces;
	for (int i = 0; i < boardSpaces; i++)
		board.push_back(0);
	results = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; ++i)
		results[i] = rhs.results[i];
	parArr = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; ++i)
		parArr[i] = rhs.parArr[i];
	givPar = new InfInt[rowColSize - 1];
	for (int i = 0; i < rowColSize - 1; i++)
		givPar[i] = rhs.givPar[i];
	wildCard = rhs.wildCard;
	return *this;
}

ostream& operator<<(ostream& ostr, const Puzzle& p) {
	ostr << p.boardString();
	return ostr;
}

Puzzle::~Puzzle() {
	delete[] results;
	delete[] parArr;
	delete[] givPar;
	parArr = nullptr;
	results = nullptr;
	givPar = nullptr;
}

void Puzzle::genPuzzle() {
	vector<int> range;
	for (int i = 1; i <= ((rowColSize * rowColSize) + rowColSize); i++)
		range.push_back(i);
	
	for (int i = 0; i < board.size(); i++) {
		int rnd = (rand() % range.size());
		board.at(i) = range.at(rnd);
		range.erase(range.begin() + rnd);
	}
}

InfInt Puzzle::calcConRows() {
	this->countGroups();
	InfInt val = 0;
	for (int i = rowColSize - (this->getWildCard() == 1 ? 1 : 0); i <= rowColSize; i++)
		val += (getResultFor(i) * (factorial(boardSpaces - i)/2) * ((i == rowColSize - 1) ? 1 : rowColSize - 1));
	finResult = val;
	return finResult;
}

void Puzzle::calcParRows() {
	this->countGroups();
	for (int i = 2; i <= rowColSize; i++) {
		InfInt temp = getResultFor(i) * (factorial(boardSpaces - i)) / 2;
		parArr[i - 2] = (temp * ( (rowColSize - (i - 1)) * (rowColSize - 1)));
		if (i != rowColSize)
			parArr[i - 2 ] += temp * ((rowColSize -  (i - 1)) - 1);
	}
}

vector<int> Puzzle::getBoard() const {
	return board;
}

InfInt Puzzle::getResult() {
	if (finResult == 0)
		finResult = calcConRows();
	return finResult;
}

string Puzzle::boardString() const {
	string boardStr = "";
	for (int i = 1; i <= board.size(); i++) {
		boardStr += to_string(board.at(i - 1));
		if (i % rowColSize == 0)
			boardStr += "\n";
		else
			boardStr += "\t";
	}
	return boardStr;
}

string Puzzle::resultString() {
	string resStr = boardString();
	InfInt res = getResult();
	resStr += ("\nrow = " + res.toString() + "\n");
	resStr += ("column = " + res.toString() + "\n");
	resStr += ("reverse row = " + res.toString() + "\n");
	resStr += ("reverse column = " + res.toString() + "\n");
	return resStr;
}

string Puzzle::parString() {
	string parStr = resultString();
	parStr += "(total for row & colunm, including inverse, in this configuration)\n";
	countUnOrded();
	for (int i = 0; i < rowColSize - 1; i++)
		parStr += to_string(i + 2) + " = " + givPar[i].toString() + "\n";
	parStr += "(total for row and column, including inverse, for all valid turns)\n";
	calcParRows();
	for (int i = 0; i < rowColSize - 1; i++)
		parStr += to_string(i + 2) + " = " + parArr[i].toString() + "\n";
	return parStr;
}

void Puzzle::setWildCard(bool b) {
	this->wildCard = b;
}

bool Puzzle::getWildCard() {
	return wildCard;
}

//Protected Functions
void Puzzle::countGroups() {
	this->clearResults();
	sortedBoard = board;
	sort(sortedBoard.begin(), sortedBoard.end());

	for (int i = 2; i <= rowColSize; i++) {
		for (int j = 0; j < boardSpaces; j++) {
			int check = 0;
			for (int x = 1; x < i; x++)
				if ((j + x) < (boardSpaces ) && sortedBoard.at(j) == sortedBoard.at(j + x) - x) 
					check++;
			if (check == i - 1)
				setResultAt(i, getResultFor(i) + 1);
		}
	}
}

void Puzzle::countUnOrded() {
	for (int i = 0; i < rowColSize; i ++) {
		vector<int> row(board.begin() + (i * rowColSize), board.begin() + ((i * rowColSize) + rowColSize - ((i * rowColSize) + rowColSize > board.size() ? 1 : 0)));
		countUnRowCol(row);
		vector<int> column;
		for (int j = i; j < board.size(); j += 4)
			column.push_back(board.at(j));
		countUnRowCol(column);
	}
}

void Puzzle::countUnRowCol(vector<int> vec) {
	for (int j = 1; j < rowColSize; j++) {
		for (int k = 0; k < vec.size(); k++) {
			int check = 0;
			int inCheck = 0;
			for (int x = 1; x <= j; x++)
				if ((k + x) < vec.size() && vec.at(k) == vec.at(k + x) - x)
					check++;
				else if ((k - x) >= 0 && vec.at(k) + x == vec.at(k - x))
					inCheck++;
			if (check == j || inCheck == j)
				givPar[j - 1]++;
		}
	}
}

void Puzzle::clearResults() {
	for (int i = 0; i < rowColSize - 1; i++) {
		results[i] = 0;
	}
}

InfInt Puzzle::getResultFor(int ind) {
	return results[ind - 2];
}

void Puzzle::setResultAt(int ind, InfInt val) {
	results[ind - 2] = val;
}
