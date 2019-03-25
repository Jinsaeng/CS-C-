//Anthony Lam
//rec03
//Introduction and tutorial to classes by simulating bank accounts

#include<string>
#include<vector>
#include<iostream>
#include<fstream>
using namespace std;

class Client;
//task 1
struct Account {
	string name;
	int number;
};
//task 3
//struct Transaction {
//	string type;
//	int amount;
//};
//task 2
class BankAccount {
	friend ostream& operator<<(ostream& os, const BankAccount& acc) {
		os << "Name: " << acc.name << " Acc number: " << acc.number << " Balance: " << acc.balance << endl;
		if (acc.statement.size() == 0) {
			return os;
		}
		else {
			os << "Transaction History: " << endl;
			for (const Transaction& move : acc.statement) {
				os << "Type: " << move.getType() << " Amount: " << move.getAmt()<< endl;
			}
			return os;
		}
	}
private:
	//task 4
	class Transaction {
	public:
		Transaction(const string& dw, int money) : type(dw), amount(money) {};
		const string& getType() const {
			return type;
		}
		const int getAmt() const {
			return amount;
		}
	private:
		int amount;
		string type;
	};
	string name;
	int number, balance;
	vector<Transaction> statement;
	//Client owner;
public:
	BankAccount(const string& name, int num) : name(name), number(num), balance(0){
	};
	const string& getName() const {
		return name;
	}
	const int getNumber() const {
		return number;
	}
	void withdraw(int money) {
		if ((balance - money) < 0) {
			cout << "Not enough money to withdraw" << endl;
			statement.emplace_back(Transaction("Withdrawal Failure", money ));
		}
		else {
			statement.emplace_back(Transaction( "Withdraw", money ));
			balance -= money;

		}
	};
	void deposit(int money) {
		statement.emplace_back(Transaction( "Deposit", money ));
		balance += money;
	};

};

//task 5
//class Client {
//public:
//	Client(const string& name, int acc) : name(name) { };
//private:
//	string name;
//	BankAccount vault;
//};


void fileOpen(ifstream& file) {
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
void fileReader(ifstream& file, vector<Account>& ledger) {
	cout << "ReadV1" << endl;
	string name, accountFiller; //check if valid entry as an account
	int num;
	while (file >> accountFiller >> name >> num) {
		if (accountFiller == "Account") {
			Account curr;
			curr.name = name;
			curr.number = num;
			ledger.push_back(curr);
		}
	}
}

void fileReader2(ifstream& file, vector<Account>& ledger) {
	cout << "ReadV2" << endl;
	string name, accountFiller;
	int num;
	while (file >> accountFiller >> name >> num) {
		if (accountFiller == "Account") {
			Account curr{ name, num };
			ledger.push_back(curr);
		}
	}
}
void fileReader3(ifstream& file, vector<BankAccount>& ledger2) {
	cout << "ReadV3" << endl;
	string name, text;
	int num, bankAcc, amount;
	bool accFlag;
	while (file >> text) {
		accFlag = false;
		if (text == "Deposit") {
			file >> bankAcc >> amount;
			for (BankAccount& person : ledger2) {
				if (person.getNumber() == bankAcc) {
					person.deposit(amount);
					accFlag = true;
				}
			}
			if (!accFlag) {
				cout << "Account does not exist" << endl;
			}
		}
		else if (text == "Withdraw") {
			file >> bankAcc >> amount;
			for (BankAccount& person : ledger2) {
				if (person.getNumber() == bankAcc) {
					person.withdraw(amount);
					accFlag = true;
				}
			}
			if (!accFlag) {
				cout << "Account does not exist" << endl;
			}
		}
		else if (text == "Account") {
			file >> name >> num;
			//BankAccount curr(name, num);	
			//ledger2.push_back(BankAccount(name, num));
			ledger2.emplace_back(BankAccount(name, num));
		}
		else {
			cout << "Invalid Operation" << endl;
		}
	}
}

void displayLedger(const vector<Account>& ledger) {
	for (const Account& person : ledger) {
		cout << "Name: " << person.name << " Acc Number: " << person.number << endl;
	}
}


int main() {
	ifstream ifs;
	fileOpen(ifs);
	vector<Account> ledger;
	//task 1
	fileReader(ifs, ledger);
	displayLedger(ledger);
	ifs.close();
	ledger.clear();
	fileOpen(ifs);
	fileReader2(ifs, ledger);
	displayLedger(ledger);

	//task 2
	ifs.close();
	fileOpen(ifs);
	vector<BankAccount> ledger2;
	fileReader3(ifs, ledger2);
	for (BankAccount& item : ledger2) {
		//cout << "Name: " << item.getName() << " Acc Num: " << item.getNumber() << endl;
		cout << item;
	}
	ifs.close();
}

//text file
//Account Rodger 15
//Account Tony 18
//Account Jim 12
//Account Robert 19
//Deposit 15 10
//Deposit 13 4
//Withdraw 15 50
//Deposit 12 50
//Deposit 19 10
//Withdraw 12 6