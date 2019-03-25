//Anthony Lam
//Rec04
//Introductory program to pointers
#include<iostream>
#include<vector>
#include<string>
using namespace std;

//task 16
struct Complex {
	double real;
	double img;
};

//task 17
class PlainOldClass {
public:
	PlainOldClass() : x(-72) {}
	int getX() const { return x; }
	void setX(int val) { x = val; }
private:
	int x;
};

//task 18
class PlainOldClassV2 {
public:
	PlainOldClassV2() : x(-72) {}
	int getX() const { return x; }
	void setX(int x) { this->x = x; } // HMMMM???
private:
	int x;
};

//task 28
class Colour {
public:
	Colour(const string& name, unsigned r, unsigned g, unsigned b)
		: name(name), r(r), g(g), b(b) {}
	void display() const {
		cout << name << " (RBG: " << r << "," << g << "," << b << ")";
	}
private:
	string name;      // what we call this colour       
	unsigned r, g, b; // red/green/blue values for displaying  
};

//task 29
class SpeakerSystem {
public:
	void vibrateSpeakerCones(unsigned signal) const {

		cout << "Playing: " << signal << "Hz sound..." << endl;
		cout << "Buzz, buzzy, buzzer, bzap!!!\n";
	}
};// since no two way, speaker system can be attached to multiple amps

class Amplifier {
public:
	void attachSpeakers(const SpeakerSystem& spkrs)
	{
		if (attachedSpeakers) {
			cout << "already have speakers attached!\n";
		}
		else {
			attachedSpeakers = &spkrs;
		}
	}

	void detachSpeakers() { // should there be an "error" message if not attached?
		if (!attachedSpeakers) {
			cerr << "No speakers attached!" << endl;
		}
		else {
			attachedSpeakers = nullptr;
		}
	}

	void playMusic() const {
		if (attachedSpeakers)
			attachedSpeakers->vibrateSpeakerCones(440);
		else
			cout << "No speakers attached\n";
	}
private:
	const SpeakerSystem* attachedSpeakers = nullptr;
};

//task 30
class Person {
public:
	Person(const string& name) : name(name) {}
	void movesInWith(Person& newRoomate) {
		roomie = &newRoomate;        // now I have a new roomie
		if (!newRoomate.roomie){ //if there is no set roomie already then...
			newRoomate.movesInWith(*this); //prevent looping with if statement
		}; //should delegate the "move in with" method to the new guy
		//newRoomate.roomie = this;    // and now they do too       
	}
	void exchangeNames() { //always need a infinite recursion check
		if (!nameExch) {
			cout << "Hi my name is: " << getName() << endl;
			nameExch = true;
			roomie->exchangeNames();
		}
		
	}
	void moveOut() {
		if (roomie) {
			roomie->roomie = nullptr;
			roomie = nullptr;
			cout << "Moved" << endl;
		}
	}
	const string& getName() const { return name; }
	// Don't need to use getName() below, just there for you to use in debugging.
	string getRoomiesName() const {
		if (roomie) {
			return roomie->getName();
		}
		else {
			return "noone";
		}
	}
private:
	Person* roomie = nullptr;
	string name;
	bool nameExch = false;
};


int main() {
	
	////task 2
	//int x;
	//x = 10;
	//cout << "x: " << x << endl; 

	////task 8
	//int* p;
	//p = &x;
	//cout << "p = " << p << endl;

	////task 9
	////p = 0x0012fed4; // using the value from my Watch window
	////error cannot convert int to int*

	////task 10
	//cout << "p points to where " << *p << " is stored\n";
	//cout << "*p contains " << *p << endl;
	//
	////task 11
	//*p = -2763;
	//cout << "p points to where " << *p << " is      stored\n";
	//cout << "*p now contains " << *p << endl;
	//cout << "x now contains " << x << endl;
	//
	////task 12
	//int y(13);
	//cout << "y contains " << y << endl;
	//p = &y;
	//cout << "p now points to where " << *p << " is stored\n";
	//cout << "*p now contains " << *p << endl;
	//*p = 980;
	//cout << "p points to where " << *p << " is stored\n";
	//cout << "*p now contains " << *p << endl;
	//cout << "y now contains " << y << endl;

	////task 13
	//int* q;
	//q = p;
	//cout << "q points to where " << *q << " is stored\n";
	//cout << "*q contains " << *q << endl;

	////task 14
	//double d(33.44);
	//double* pD(&d);
	//*pD = *p;
	//*pD = 73.2343;
	//*p = *pD;
	//*q = *p;
	//cout << *p << " " << *pD << endl; //can point to same place, but when printed, its diff
	//pD = p; //value of type int* cannot be assigned to type double*
	//p = pD;
	//cross casting with pointers is not allowed

	//task  15
	int joe = 24;
	const int sal = 19;
	int*  pI;
	pI = &joe;  //can assign int pointer to joe
	*pI = 234; //can assign new information in address 
	//pI = &sal;  //cannot assign const int pointer to reg int pointer
//	const int* sal(&joe); // can assign reg int pointer to const int pointer
	*pI = 7623;     
	

	const int* pcI;
	pcI = &joe;  //same type assignment
	//*pcI = 234;  //cannot change const
	pcI = &sal;  
	//*pcI = 7623; //cannot change const    

	//int* const cpI; //requires an initializer, since const is after the type* needs 
	//initializer since its initial address cannot be change
	int* const cpI(&joe);
	//int* const cpI(&sal); //address of const int* != int* const
	//cpI = &joe;  //cannot change the initial pointer's address
	*cpI = 234;  //value in address can change
	//cpI = &sal;  
	*cpI = 7623;    

	//const int* const cpcI;
	const int* const cpcI(&joe); //can change from reg int* to const int*
//	const int* const cpcI(&sal); // multiple initializations error
	//cpcI = &joe; //cannot change anything
	//*cpcI = 234;  
	//cpcI = &sal;  
	//*cpcI = 7623;  

	//task 16
	//Complex c = { 11.23,45.67 };
	//Complex* pC(&c);
	//cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl; //precedence of * and . (. is greater)
	////cout << pC->img << endl; //& and ->
	////&+-> show address of where the info the pointer is pointing to
	////-> shows the information of the pointer

	////task 17/18
	//PlainOldClassV2 poc;
	//PlainOldClassV2* ppoc(&poc);
	//cout << ppoc->getX() << endl;
	//ppoc->setX(2837);
	//cout << ppoc->getX() << endl;

	//task 19 (new and delete) heap stuff
	int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
	*pDyn = 17;
	cout << "The " << *pDyn
		<< " is stored at address " << pDyn
		<< " which is in the heap\n";
	cout << pDyn << endl;
	//delete pDyn;
	//cout << pDyn << endl; //since deleted, contents are undefined
	//cout << "The 17 might STILL be stored at address " << pDyn << " even though we deleted pDyn\n";
	//cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n"; //crash
	//

	//task 21 nullptrs
	//int val of 0 
	//setting to nullptr after deleting prevents crashes when 
	delete pDyn;
	pDyn = nullptr;
	double* pDouble = nullptr;
	cout << "The 17 might STILL be stored at address " << pDyn << " even though we deleted pDyn\n";
	
	//task 22
	//cout << "Can we dereference nullptr?  " << *pDyn << endl;
	//cout << "Can we dereference nullptr?  " << *pDouble << endl;
	//cannot dereference nullptr

	//task 23 
	//this cannot point to nullptr since this is an pointer of an instance

	//task 24 deleting nullptr
	double* pTest = new double(12);
	delete pTest;
	pTest = nullptr;
	delete pTest; // safe

	//task 25 deleting a deleted pointer
	short* pShrt = new short(5);
	cout << "Delete";
	delete pShrt;
	//delete pShrt; //cant delete twice

	//task 26 deleting memory locations?
	cout << "Mem";
	long jumper = 12238743;
	//delete jumper; //cannnot
	long* ptrTolong = &jumper;
	//delete ptrTolong; //cannot
//	Complex cmplx;
	//delete cmplx; //cannot 


	//task 27
	//cout << "vector" << endl;
	//vector<Complex*> complV; // can hold pointers to Complex objects
	//Complex* tmpPCmplx;      // space for a Complex pointer
	//for (size_t ndx = 0; ndx < 3; ++ndx) {
	//	tmpPCmplx = new Complex; // create a new Complex object on the heap
	//	tmpPCmplx->real = ndx;   // set real and img to be the
	//	tmpPCmplx->img = ndx;   // value of the current ndx
	//	complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
	//}
	//// display the objects using the pointers stored in the vector
	//for (size_t ndx = 0; ndx < 3; ++ndx) {
	//	cout << complV[ndx]->real << endl;
	//	cout << complV[ndx]->img << endl;
	//}
	//// release the heap space pointed at by the pointers in the vector      
	//for (size_t ndx = 0; ndx < 3; ++ndx) {
	//	delete complV[ndx];
	//}
	//// clear the vector      
	//complV.clear();
	//vector<Colour*> colours;
	//string inputName;
	//unsigned inputR, inputG, inputB;

	////task 28
	//// fill vector with Colours from the file       
	//// this could be from an actual file but here we are using the keyboard instead of a file
	//// (so we don't have to create an actual file)
	//// Do you remember the keystroke combination to indicate "end of file" at the keyboard?
	//// somehow the while's test has to fail - from keyboard input
	//while (cin >> inputName >> inputR >> inputG >> inputB) {
	//	colours.push_back(new Colour(inputName, inputR, inputG, inputB));
	//}

	//// display all the Colours in the vector:       
	//for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
	//	colours[ndx]->display();
	//	cout << endl;
	//}
	//for (size_t ndx = 0; ndx < colours.size(); ++ndx) {//freeing up the heap
	//	delete colours[ndx];
	//}
	//colours.clear();

	//task 29
	cout << endl;
	//SpeakerSystem Spksys;
	//Amplifier Amp;
	//Amp.playMusic();
	//Amp.detachSpeakers();
	//Amp.attachSpeakers(Spksys);
	//Amp.playMusic();
	//Amp.attachSpeakers(Spksys);
	//Amp.detachSpeakers();

	//task 30
	// write code to model two people in this world       
	Person joeBob("Joe Bob"), billyJane("Billy Jane");

	// now model these two becoming roommates       
	joeBob.movesInWith(billyJane);

	// did this work out?       
	cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
	cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

	joeBob.exchangeNames();
	joeBob.moveOut();
	cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
	cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
}
