//Anthony Lam
//Hw05
//Nobles and Warriors but on the heap

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

class Noble;
class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << warrior.name << ": " << warrior.Wstr << endl;
		return os;
	}
public:
	Warrior(const string& name, double str) : name(name), Wstr(str), leader(nullptr) {};
	const string& getWName() const {
		return name;
	}
	void setLeader(Noble* head) {
		leader = head;
	}
	Noble* getLeader() const {
		return leader;
	}
	double getWStr() const {
		return Wstr;
	}
	void setWStr(double val) {
		Wstr = val;
	}
private:
	string name;
	Noble* leader;
	double Wstr;
};
class Noble {
	friend ostream& operator<<(ostream& os, const Noble& noble) {
		os << noble.name << " has an army of " << noble.army.size() << endl;
		for (Warrior* soldier : noble.army) {
			os << *soldier;
		}
		return os;
	}
public:
	Noble(const string& name) : name(name), Nstr(0) {};
	bool hire(Warrior* hiree) {
		if ((hiree->getLeader() != nullptr)) { //if already has an employer or noble is dead
			return false;
		}
		else {
			army.emplace_back(hiree);
			Nstr += hiree->getWStr();
			hiree->setLeader(this);
			return true;
		}
	}
	bool fire(Warrior* firee) {
		if (firee->getLeader() != this) { //cannot fire unless is employer
			return false;
		}
		else {
			for (size_t i = 0; i < army.size(); i++) {
				if (army[i]->getWName() == firee->getWName()) {
					army[i]->setLeader(nullptr);
					//remove from army
					if (i != army.size() - 1) {//swap the position of the fired man until he reaches the back
						swap(army[i], army[i + 1]);//keep the hired order of the warriors, by swapping slowly
					}
				}
			}
			cout << firee->getWName() << " You're fired! -- " << name << endl;
			army.pop_back(); //fired
			Nstr -= firee->getWStr();
			return true;
		}
	}
	void battle(Noble* fighter) {
		string winner, dead, status;
		double ratio; //loss of str ratio
		cout << name << " battles " << fighter->getNName() << endl;

		if (((fighter->army.size() != 0) && (fighter->getNStr() == 0)) && (Nstr != 0)) {
			//enemy is dead, noble is not
			winner = name;
			status = "He's dead already, " + winner;
		}
		else if ((Nstr == fighter->getNStr()) && (Nstr != 0)) { //both die
			for (Warrior* loser : fighter->army) {
				loser->setWStr(0);
			}
			for (Warrior* loser : army) {
				loser->setWStr(0);
			}
			Nstr = 0;
			fighter->setNStr(0);
			status = "Mutual annihilation! " + name + " and " + fighter->getNName() + " die at each other's hand!";
		}
		else if ((Nstr == fighter->getNStr()) && (Nstr == 0) && (army.size() != 0) && (fighter->army.size() != 0)) {
			//already both dead
			status = "Oh No!, They're both dead! Yuck!";
		}
		else if (Nstr > fighter->getNStr()) {
			ratio = fighter->getNStr() / Nstr;
			winner = name;
			dead = fighter->getNName();
			fighter->setNStr(0);
			for (Warrior* loser : fighter->army) { //loser str set to 0
				loser->setWStr(0);
			}
			for (Warrior* victor : army) { //winner gets str reduced
				victor->setWStr(victor->getWStr() - (Nstr* ratio));
				status = winner + " defeats " + dead;
			}
		}
		else if (Nstr < fighter->getNStr()) { //one winner, one loser
			ratio = Nstr/ fighter->getNStr();
			winner = fighter->getNName();
			dead = name;
			for (Warrior* loser : army) {
				loser->setWStr(0);
			}
			for (Warrior* victor : fighter->army) {
				victor->setWStr(victor->getWStr() - (fighter->getNStr() * ratio));
			}
			status = winner + " defeats " + dead;
		}
		else if (((army.size() != 0) && (fighter->getNStr() == 0)) && (fighter->getNStr() != 0)) {//noble that is dead tries to battle
			winner = fighter->getNName();
			status = "He's dead already, " + winner;
		}
		cout << status << endl;
	}

	const string& getNName() const {
		return name;
	}
	const double getNStr() const {
		return Nstr;
	}
	void setNStr(double val) {
		Nstr = val;
	}
private:
	string name;
	vector<Warrior*> army;
	double Nstr;
};

string createNoble(const string& name, vector<Noble*>& nobles) {
	for (Noble* nobleman : nobles){//existance check
		if (nobleman->getNName() == name) {
			return "Noble already created.";
		}
	}
	Noble* nobleman;
	nobleman = new Noble(name);
	nobles.emplace_back(nobleman);
	return "";
}
string createWarrior(const string& name, int str, vector<Warrior*>& warriors) {
	for (Warrior* warrior : warriors) {//existance check
		if (warrior->getWName() == name) {
			return "Warrior already defined.";
		}
	}
	Warrior* warrior;
	warrior = new Warrior(name, str);
	warriors.emplace_back(warrior);
	return "";
}
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
	for (Noble* noble: nobles) {
		delete noble;
		noble = nullptr;
	}
	for (Warrior* warrior : warriors) {
		delete warrior;
		warrior = nullptr;
	}
	warriors.clear();
	nobles.clear();
};

int main() {
	fstream ifs("nobleWarriors.txt");
	if (!ifs) {
		cerr << "Incorrect file.";
		exit(1);
	}
	string command, name1, name2, noble, warrior;
	vector<Noble*> nobles;
	vector<Warrior*> warriors;
	while (ifs >> command) {
		if (command == "Battle") {
			ifs >> name1 >> name2;
			bool flag1, flag2 = true;
			for (Noble* dueler : nobles) {
				if (name1 == dueler->getNName()) {
					flag1 = false;
					for (Noble* duelee : nobles) {
						if ((duelee->getNName() == name2) && !(flag1)) {
							flag2 = false;
							dueler->battle(duelee);
						}
					}
				}
			}
			if (flag1) { cout << "Could not find the noble." << endl; } //checkers
			if (flag2) { cout << "Could not find the warrior." << endl; }
		}
		else if (command == "Status") {
			bool flag = true;
			cout << "Status" << endl << "==============" << endl << "Nobles:" << endl;
			for (Noble* noble : nobles) {
				cout << *noble;
				
			}
			if (nobles.size() == 0) { cout << "None" << endl; }
			cout << "Unemployed: " << endl;
			for (Warrior* warrior : warriors) {
				if (warrior->getLeader() == nullptr) {
					flag = false;
					cout << *warrior;
				}
			}
			if (flag) { cout << "None" << endl; }
		}
		else if (command == "Noble") {
			ifs >> noble;
			createNoble(noble, nobles);
		}
		else if (command == "Warrior") {
			int str;
			ifs >> warrior >> str;
			createWarrior(warrior, str, warriors);
		}
		else if (command == "Hire") {
			ifs >> noble >> warrior;
			bool flag1, flag2 = true;
			for (Noble* hirer : nobles) {
				if (noble == hirer->getNName()) {
					flag1 = false;
					for (Warrior* hiree : warriors) {
						if ((hiree->getWName() == warrior) && !(flag1)) {
							hirer->hire(hiree);
							flag2 = false;
						}
					}
				}
			}
			if (flag1) { cout << "Could not find the noble." << endl; } //checkers
			if (flag2) { cout << "Could not find the warrior." << endl; }
		}
		else if (command == "Fire") {
			bool flag1, flag2 = true;
			ifs >> noble >> warrior;
			for (Noble* firer : nobles) {
				if (noble == firer->getNName()) {
					flag1 = false;
					for (Warrior* firee : warriors) {
						if ((firee->getWName() == warrior) && !(flag1)) {
							flag2 = false;
							firer->fire(firee);
						}
					}
				}
			}
			if (flag1) { cout << "Noble can't be found." << endl; } //checkers
			if (flag2) { cout << "Warrior can't be found." << endl; }
		}
		else if (command == "Clear") {
			clear(nobles, warriors);
		}
	}
	ifs.close();
}