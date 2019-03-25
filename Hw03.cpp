//Anthony Lam
//Hw03
//File to simulate battles between warriors, this time with swords.

#include<vector>
#include<string>
#include<fstream>
#include<iostream>
using namespace std;


//text file "warrior" name weapon str
//warrior,battle, status
//weapon is nested inside warrior
//battle simulations are the same
class Warrior;
void status(const vector<Warrior>& group);
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& person) {
		os << "Warrior: " << person.name << person.weapon; //delegates to weapon
		return os;
	}
	class Weapon {
		friend ostream& operator<<(ostream& os, const Weapon& weapon) {
			os << "Weapon: " << weapon.w_name << ", " << weapon.w_str;
			return os;
		}
	public:
		Weapon(const string& name, int str) : w_name(name), w_str(str) {};
		int getstr() const {
			return w_str;
		}	
		void setstr(const int& val) {
			w_str = val;
		}
	private:
		string w_name;
		int w_str;
	};
public:
	Warrior(const string& name, const string& w_name, int w_str) 
		: name(name), weapon(w_name, w_str) {};

	void battle(Warrior& opponent) { //this guy battles the other
		int str1 = weapon.getstr();
		int str2 = opponent.weapon.getstr();
		cout << name << " battles " << opponent.name << endl;
		if ((str1==0) && (str2>0)) {//one is already dead, but two is not
			cout << "He's dead, " << opponent.name << endl;
		}
		else if ((str2 == 0) && (str1 > 0)) {//two is dead, one is not
			cout << "He's dead, " << name << endl;
		}
		else if ((str1 == 0) && (str2 == 0)) { //both are dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if ((str1 > str2)) { //one wins , two dies
			weapon.setstr(str1 - str2);//winner loses str according to the loser
			opponent.weapon.setstr(0);
			cout << name << " defeats " << opponent.name << endl;
		}
		else if ((str1 < str2)) {//two wins, one dies
			opponent.weapon.setstr((str2 - str1));
			weapon.setstr(0);
			cout << opponent.name << " defeats " << name << endl;
		}
		else if ((str1) == (str2)) {//tie (both die)
			weapon.setstr(0);
			opponent.weapon.setstr(0);
			cout << "Mutual Annihilation: " << name << " and " 
				<< opponent.name << " die at each other's hands." << endl;
		}

	};
	const string& getName()const{
		return name;
	}
private:
	string name;
	Weapon weapon;

};

int main() {
	fstream ifs("warriors.txt");
	if (!ifs) { //file check
		cerr << "Input file error";
		exit(1);
	}
	vector<Warrior> group;
	string command, name, w_name;
	int str;
	while (ifs >> command) { //loop through the text file
		if (command == "Warrior") { 
			ifs >> name >> w_name >> str;
			Warrior newWarrior(name, w_name, str);
			group.push_back(newWarrior);
		}
		else if (command == "Battle") {
			string warrior1, warrior2;
			ifs >> warrior1 >> warrior2;
			for (size_t i = 0; i < group.size(); i++) {
				bool flag1 = false;//flag for existence check
				if (group[i].getName() == warrior1) {
					flag1 = true; //flag to show first guy was found
				}
				if (flag1) {// only after finding the first guy would it search for the second
					for (size_t j = 0; j < group.size(); j++) { //after finding the first one loop through to find second
						if ((group[j].getName() == warrior2) &&
							(group[j].getName() != warrior1)) { //checks for self fighting
							group[i].battle(group[j]); //order matters in duels
						}

					}
				}
			}
		}
		else if (command == "Status") {
			status(group);
		}
	}
	ifs.close();
}

void status(const vector<Warrior>& group) {
	cout << "There are: " << group.size() << " warriors." << endl;
	for (const Warrior& person : group) {
		cout << person << endl; //delegates printing to the classes
	}
}; //prints out status
