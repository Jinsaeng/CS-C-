//Anthony Lam
//Hw02
//Program to simulate medivial combat (structs, vectors, functions, i/o)

#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using namespace std;

struct Warrior {
	string name;
	int strength;
};
void battle(Warrior& one, Warrior& two, vector<Warrior>& group); //two warriors battle
void status(const vector<Warrior>& group); //outputs the result



int main() {
	fstream ifs("warriors.txt");
	if (!ifs) { //file check
		cerr << "Input file error";
		exit(1);
	}
	vector<Warrior> group;
	string command, name;
	int str;
	while (ifs >> command) { //loop through the text file
		if (command == "Warrior"){ //3 specified command lines
			ifs >> name >> str;
			Warrior newWarrior;
			newWarrior.name = name;
			newWarrior.strength = str;
			group.push_back(newWarrior);
		}
		else if (command == "Battle") {
			string warrior1, warrior2;
			ifs >> warrior1 >> warrior2;
			Warrior dueler, duelee;
			dueler.name = warrior1;
			duelee.name = warrior2;
			battle(dueler, duelee, group);
		}
		else if (command == "Status") {
			status(group);
		}
	}
	ifs.close();
};

void battle(Warrior& one, Warrior& two, vector<Warrior>& list) {
	bool flag1, flag2 = false; //check if both are present prior to duel and duplicate
	for (Warrior& enlisted : list) { //set a temp copy to the duelists (one and two)
		if (enlisted.name == one.name) {
			one.strength = enlisted.strength;
			flag1 = true;
		}
		else if ((enlisted.name == two.name) && (enlisted.name != one.name)) { //checks for self fighting
			two.strength = enlisted.strength;
			flag2 = true;
		}
	}
	cout << one.name << " battles " << two.name << endl;
 	if (flag1 && flag2) {
		if ((one.strength == 0) && (two.strength > 0)) {//one is already dead, but two is not
			cout << "He's dead, " << two.name << endl;
		}
		else if ((two.strength == 0) && (one.strength > 0)) {//two is dead, one is not
			cout << "He's dead, " << one.name << endl;
		}
		else if ((one.strength == 0) && (two.strength == 0)) { //both are dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if ((one.strength > two.strength)) { //one wins , two dies
			one.strength -= two.strength; //winner loses str according to the loser
			two.strength = 0; 
			cout << one.name << " defeats " << two.name << endl;
		}
		else if ((one.strength < two.strength)) {//two wins, one dies
			two.strength -= one.strength;
			one.strength = 0;
			cout << two.name << " defeats " << one.name << endl;
		}
		else if ((one.strength) == (two.strength)) {//tie (both die)
			one.strength = 0;
			two.strength = 0;
			cout << "Mutual Annihilation: " << one.name << " and " << two.name << " die at each other's hands." << endl;
		}
		for (Warrior& enlisted : list) { //set the warriors' str levels
			if (enlisted.name == one.name) {
				enlisted.strength = one.strength;
			}
			else if (enlisted.name == two.name) {
				enlisted.strength = two.strength;
			}
		}
	}
	else {
		cout << "Warriors have not enlisted." << endl;
	}
};
void status(const vector<Warrior>& group) { //status report
	cout << "There are " << group.size() << " warriors." << endl;
	for (const Warrior& fighter : group) {
		cout << "Warrior: " << fighter.name << ", Strength: " << fighter.strength << endl;
	}
};