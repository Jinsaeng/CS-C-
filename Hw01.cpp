//Anthony Lam
//Hw01
//Program to read an encrypted code and decrypt it (Caeser Cypher)

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;


//Function to read by char
char decrypter(const char& letter, int steps) {
	int curr = int(letter);
	if (!(curr < 97 || curr > 122)) {
		curr -= steps;
	}
	if ((curr < 97) && (curr > 97-steps-1)) {
		curr += 26;
	}
	return char(curr);
}
//Function to return the read char, decrypted (string version)
void decodedString(string& readMe, int steps) {
	for (char& item : readMe) {
		 item = decrypter(item, steps);
	}
}

int main() {
	fstream ifs("encrypted.txt");
	if (!ifs) {
		cerr << "File can not be found";
		exit(1);
	}

	vector<string> code;
	vector<string> decoded;
	string line;
	int steps;
	ifs >> steps;
	getline(ifs, line); //gets rid of the empty space left by the int getter

	while (getline(ifs, line)) { //puts the strings into a readable vector
		code.push_back(line);
	}
	for (size_t i = 1; i < code.size()+1; i++) { //decrypts and reverses order
		decodedString(code[code.size()-i], steps);
		decoded.push_back(code[code.size() - i]);
	}
	for (string& item : decoded) { //prints out decoded code
		cout << item << endl;
	}
	
}