//Anthony Lam
//Rec01
//Code to implement Conway's Game of Life

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//Open File

bool checkStatus(char& piece) { //alive or dead
	if (piece == '*') {
		return true;
	}
	return false;
}

bool checkNext(bool current, int nNeighbors) { //if next gen is alive or dead
	if (current && nNeighbors == 3){
		return true;
	}
	else if (current && nNeighbors == 2) {
		return true;
	}
	else if (!current && nNeighbors == 3) {
		return true;
	}
	return false;
}

int main() {
	fstream ifs("life.txt");
	if (!ifs) {
		cerr << "File not found";
		exit(1);
	}
	//cout << "Found";
	string line;
	//getline(cin, line);
	vector<string> first;
	//vector<string> next;
	vector<string> current;
	cout << "Initial Generation" << endl;
	while (getline(ifs,line)) {
		first.push_back(line);
		cout << line << endl;
	}

	ifs.close();
	current = first;
	int generations = 1;
	while (generations < 11) { //required generations is 10
		for (size_t i = 0; i < first.size(); i++) {
			for (size_t j = 0; j < first[i].size(); j++) {
				int neighbors = 0;
				if (i == 0 && j == 0) { //top left
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j+1] == '*') {
						neighbors += 1;
					}
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
				}
				else if (i == 0 && j == first[i].size()-1) { //top right
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j - 1] == '*') {
						neighbors += 1;
					}
				}
				else if (i == first.size()-1 && j == 0) { //bottom left
					if (first[i - 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i-1][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
				}
				else if (i == first.size()-1 && j == first[i].size()-1) { //bottom right
					if (first[i - 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j - 1] == '*') {
						neighbors += 1;
					}
				}
				else if ((i == 0) && (j != 0 && j != first[i].size()-1)) { //first row exclusive of corners
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j + 1] == '*') {
						neighbors += 1;
					}
				}
				else if ((i == 0 || i == first.size()-1) && (j != 0 && j != first[i].size())) {//last row
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j + 1] == '*') {
						neighbors += 1;
					}
				}
				else if ((j == 0) && (i != 0 && i != first.size()-1)) { //first column
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i-1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j + 1] == '*') {
						neighbors += 1;
					}
				}
				else if ((j == first[i].size()-1) && (i != 0 && i != first.size()-1)) { //last column
					if (first[i-1][j-1] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i][j-1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
				}
				else { //everything in the middle
					if (first[i - 1][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i - 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i-1][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j - 1] == '*') {
						neighbors += 1;
					}
					if (first[i][j + 1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j-1] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j] == '*') {
						neighbors += 1;
					}
					if (first[i + 1][j + 1] == '*') {
						neighbors += 1;
					}
				}
				if (checkNext(checkStatus(first[i][j]), neighbors)) {
					current[i][j] = '*';
				}
				else {
					current[i][j] = '-';
				}
			}
		}
		cout << generations << endl;
		for (string& item : current) {
			cout << item << endl;
		}
		generations += 1;
		first = current;		
	}
}

//one dies
//2-3 lives
//more than 3 dies
//if dead, needs 3