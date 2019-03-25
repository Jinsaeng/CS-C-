//Anthony Lam
//hw04

//Program to simulate battles between warriors with nobles as the hosts.
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

class Noble;
class Warrior {
public:
	Warrior(const string& name, int str) : w_name(name), str(str) {};
	const string& getName() const {
		return w_name;
	}
	int getStr() const {
		return str;
	}
	void setStr(int newStr) {
		str = newStr;
	}
	Noble* getBoss() const {
		return boss;
	}
	void setBoss(Noble* newBoss) {
		boss = newBoss;
	}
private:
	string w_name;
	int str;
	Noble* boss = nullptr;

};
class Noble {
public:
	Noble(const string& name) : n_name(name) {};
	bool hire(Warrior& name) {
		//check if not dead, if army_str != 0 || (army_str == 0 && army.size() == 0)
		if ((name.getBoss() == nullptr) && ((army_str != 0) || ((army_str == 0) && (army.size() == 0)))) {
			name.setBoss(this);
			army_str += name.getStr();
			Warrior* p = &name;
			army.emplace_back(p);
			return true;
		}
		else {
			return false;
		}
	};
	bool fire(Warrior& name) {
		if ((name.getBoss() != this) && ((army_str != 0) || ((army_str == 0) && (army.size() == 0)))){
			return false;
		}
		else {
			for (size_t i = 0; i < army.size(); i++) {
				if (army[i]->getName() == name.getName()) {
					army[i]->setBoss(nullptr);//set boss to nullptr
					//remove from army
					if (i != army.size() - 1) {//swap the position of the fired man until he reaches the back
						swap(army[i], army[i + 1]);//keep the hired order of the warriors, by swapping slowly
					}
				}
			}cout << name.getName() << " You're fired! -- " << n_name << endl;
			army.pop_back(); //fired
			army_str -= name.getStr();
			return true;
		}
	};

	void battle(Noble& enemy) {
		string winner, dead, status;
		int ratio; //loss of str ratio
		cout << n_name << " battles " << enemy.n_name << endl;
		//if ((enemy.army.size() != 0) && (enemy.army_str == 0)) { //check if they are dead or have no warriors
			//enemy = dead;
		//}
		if (((enemy.army.size() != 0) && (enemy.army_str == 0)) && (army_str != 0)) {
			//enemy is dead, noble is not
			winner = n_name;
			status = "He's dead already, " + winner;
		}
		else if ((army_str == enemy.army_str) && (army_str!= 0)) { //both die
			for (Warrior* loser : enemy.army) {
				loser->setStr(0);
			}
			for (Warrior* loser : army) {
				loser->setStr(0);
			}
			army_str = 0;
			enemy.army_str = 0;
			status = "Mutual annihilation! " + n_name + " and " + enemy.n_name + " die at each other's hand!";
		}
		else if ((army_str == enemy.army_str) && (army_str == 0) && (army.size() !=0) && (enemy.army.size()!=0)) { 
			//already both dead
			status = "Oh No!, They're both dead! Yuck!";
		}
		else if (army_str > enemy.army_str) {
			ratio = enemy.army_str / army_str;
			winner = n_name;
			dead = enemy.n_name;
			enemy.army_str = 0;
			for (Warrior* loser : enemy.army) { //loser str set to 0
				loser->setStr(0);
			}
			for (Warrior* victor : army) { //winner gets str reduced
				victor->setStr(victor->getStr() - (army_str * ratio));
				status = winner + " defeats " + dead;
			}
		}
		else if (army_str < enemy.army_str) { //one winner, one loser
			ratio = army_str / enemy.army_str;
			winner = enemy.n_name;
			dead = n_name;
			for (Warrior* loser : army) {
				loser->setStr(0);
			}
			for (Warrior* victor : enemy.army) {
				victor->setStr(victor->getStr() - (army_str * ratio));
			}
			status = winner + " defeats " + dead;
		}
		else if (((army.size() != 0) && (army_str == 0)) && (enemy.army_str != 0)) {//noble that is dead tries to battle
			winner = enemy.n_name;
			status = "He's dead already, " + winner;
		}
		cout << status << endl;
	}

	void display() const {
		cout << n_name << " has an army of " << army.size() << endl;
		for (Warrior* soldier : army) {
			cout << soldier->getName() << ": " << soldier->getStr() << endl;
		}
	};
private:
	string n_name;
	int army_str;
	vector<Warrior*> army;
};

int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

}