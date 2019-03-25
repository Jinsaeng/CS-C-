//Anthony Lam
//Rec02
//Program to sort a group of chemicals by their number of carbons and hydrogens
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

struct Chemicals {
	int hydrogen;
	int carbon;
	vector<string> name;
}; 

//prototypes
void fileReader(ifstream& file); //file check
void fillVector(vector<Chemicals>& ChemList, ifstream& ifs); //reads file and fills vector
void sortVector(vector<Chemicals>& ChemList); //function to read a file
void displayVector(const vector<Chemicals>& ChemList); //print
bool sameComponentCheck(vector<Chemicals>& ChemList, Chemicals curr);
void fillInformation(vector<Chemicals>& ChemList, string name, int carb, int hydro);


int main() {
	ifstream ifs;
	vector<Chemicals> ChemList;
	fileReader(ifs);
	fillVector(ChemList, ifs);
	sortVector(ChemList);
	displayVector(ChemList);
}

void fileReader(ifstream& file) {
	string filename;
	cout << "Please enter the file name: ";
	cin >> filename;
	file.open(filename);
	while (!file) {
		file.clear();
		cout << "Error in file name, please retry: ";
		cin >> filename;
		file.open(filename);
	}
}

void fillVector(vector<Chemicals>& ChemList, ifstream& ifs) {//fills the vector
	char carbon;
	char hydro;
	int carbonC;
	int hydroC;
	string cName;
	Chemicals curr;
	while (ifs >> cName >> carbon >> carbonC >> hydro >> hydroC) {
		fillInformation(ChemList, cName, carbonC, hydroC);
	}

}

void fillInformation(vector<Chemicals>& ChemList, string name, int carb, int hydro) { //puts the information into a struct and into the vector
	Chemicals curr;
	curr.name.push_back(name);
	curr.carbon = carb;
	curr.hydrogen = hydro;
	if (sameComponentCheck(ChemList, curr)) { //only push if new item
		ChemList.push_back(curr);
	}
	curr.name.clear(); //refresh the vector of names for var
}

bool sameComponentCheck(vector<Chemicals>& ChemList, Chemicals curr) { //checks if chems have same CH
	bool push_back = true;
	if (ChemList.size() > 0) {
		for (Chemicals& chems : ChemList) { //check if same values
			if ((curr.carbon == chems.carbon) && (curr.hydrogen == chems.hydrogen)) {
				for (string& name : curr.name) {
					chems.name.push_back(name);
				}
				push_back = false;
			}
		}
	}
	return push_back;
}

void sortVector(vector<Chemicals>& ChemList) {//sort
	Chemicals temp;
	for (size_t i = 0; i < ChemList.size() - 1; i++) {
		if ((ChemList[i].carbon > ChemList[i + 1].carbon) || ((ChemList[i].carbon == ChemList[i + 1].carbon)
			&& (ChemList[i].hydrogen > ChemList[i + 1].hydrogen))) { //bubble sort
			temp = ChemList[i];
			ChemList[i] = ChemList[i + 1];
			ChemList[i + 1] = temp;
		}
	}
}
void displayVector(const vector<Chemicals>& ChemList) {//display
	for (const Chemicals& item : ChemList) {
		cout << "C" << item.carbon << "H" << item.hydrogen << " ";
		for (const string& name : item.name) { //loop over vector of names
			cout << name << " ";
		}
		cout << endl;
	}

}