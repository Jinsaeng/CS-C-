//Anthony Lam
//Rec05
//Program to model school administration

#include<iostream>
#include<vector>
#include<string>
using namespace std;

//Lab section - time slot, knows time and student rec, does not know instructor
//Lab instructor - knows lab section
//Time slot - inside section
//Student Rec - on the heap (vector of 14 grades)
class LabWorker;
class Section {
	friend ostream& operator<<(ostream& os, const Section& section) {
		os << "Section: " << section.title << "," << section.timeOfSection << " Students: ";
		if (section.students.size() == 0) { os << "None" << endl; }
		else {
			for (StudentRecord* student : section.students) {
				os << endl << *student;

			}
		}
		return os;
	}
	class TimeSlot {
		friend ostream& operator<<(ostream& os, const TimeSlot& time) {
			os << " Time Slot: [Day: " << time.day << ", Start Time: "
				<< time.TStime << time.timeOfDay;
			return os;
		}
	public:
		TimeSlot(const string& day, int time) : day(day), TStime(time), timeOfDay("am") {
			if (time > 12) {
				TStime -= 12;
				timeOfDay = "pm";
			}
		};
	private:
		string day;
		int TStime;
		string timeOfDay;
	};
	class StudentRecord {
		friend ostream& operator<<(ostream& os, const StudentRecord& sr) {
			os << "Name: " << sr.name << ", Grades: ";
			for (int grade : sr.grades) {
				os << grade << " ";
			}
			return os;
		}
	public:
		StudentRecord(const string& name) : name(name) {
			for (size_t i = 0; i < 14; i++) {//where 14 is the # of weeks in the semester
				grades.push_back(-1);
			}
		};
		const string& getName() const {
			return name;
		}
		void setGrade(int val, int week) {
			grades[week - 1] = val;
		}
	private:
		string name;
		vector<int> grades;
	};
public:
	Section(const string& sectionNum, const string& day, int time) :title(sectionNum), timeOfSection(day, time) {};
	void addStudent(const string& name) {
		StudentRecord* p = new StudentRecord(name);
		students.emplace_back(p);
	};
	const string& getTitle() const {
		return title;
	}
	void changeGrade(const string& name, int grade, int week) {
		for (StudentRecord* student : students) {
			if (name == student->getName()) {
				student->setGrade(grade, week);
			}
		}
	}
	Section(const Section& rhs):timeOfSection(rhs.timeOfSection), title(rhs.title){
		for (StudentRecord* student : rhs.students) {
			StudentRecord* newStudent = new StudentRecord(*student);
			students.emplace_back(newStudent);
		}
	}
	~Section() {
		cout << "Section " << title << " is being deleted." << endl;
		for (StudentRecord* student : students) {
			cout << "deleting " << student->getName() << endl;
			delete student;
			student = nullptr;
		}
		students.clear();
	}
private:
	string title;
	TimeSlot timeOfSection;
	vector<StudentRecord*> students;
};

class LabWorker {
	friend ostream& operator<<(ostream& os, const LabWorker& instr) {
		if (instr.section) {
			os << instr.name << " has " << *(instr.section) << endl;
		}
		else {
			os << instr.name << " does not have a section" << endl;
		}
		return os;
	}
public:
	LabWorker(const string& name):name(name), section(nullptr) {};
	void addSection(Section& secTitle) {
		Section* p = &secTitle;//creates pointer with the add
		section = p; //sets pointer
	}
	void addGrade(const string& name, int valueOfGrade, int weekNum) {
		//look through section to find name
		section->changeGrade(name, valueOfGrade, weekNum);
		//extract grades from name
		//change grade
	}
private:
	string name;
	Section* section; // can only have one

};


// Test code
void doNothing(Section sec) {
	cout << sec << endl;;
}

int main() {
	//
		cout << "Test 1: Defining a section\n";
		Section secA2("A2", "Tuesday", 16);
		cout << secA2 << endl;

		cout << "\nTest 2: Adding students to a section\n";
		secA2.addStudent("John");
		secA2.addStudent("George");
		secA2.addStudent("Paul");
		secA2.addStudent("Ringo");
		cout << secA2 << endl;

		cout << "\nTest 3: Defining a lab worker.\n";
		LabWorker moe("Moe");
		cout << moe << endl;

		cout << "\nTest 4: Adding a section to a lab worker.\n";
		moe.addSection(secA2);
		cout << moe << endl;

		cout << "\nTest 5: Adding a second section and lab worker.\n";
		LabWorker jane("Jane");
		Section secB3("B3", "Thursday", 11);
		secB3.addStudent("Thorin");
		secB3.addStudent("Dwalin");
		secB3.addStudent("Balin");
		secB3.addStudent("Kili");
		secB3.addStudent("Fili");
		secB3.addStudent("Dori");
		secB3.addStudent("Nori");
		secB3.addStudent("Ori");
		secB3.addStudent("Oin");
		secB3.addStudent("Gloin");
		secB3.addStudent("Bifur");
		secB3.addStudent("Bofur");
		secB3.addStudent("Bombur");
		jane.addSection(secB3);
		cout << jane << endl;

		cout << "\nTest 6: Adding some grades for week one\n";
		moe.addGrade("John", 17, 1);
		moe.addGrade("Paul", 19, 1);
		moe.addGrade("George", 16, 1);
		moe.addGrade("Ringo", 7, 1);
		cout << moe << endl;

		cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
		moe.addGrade("John", 15, 3);
		moe.addGrade("Paul", 20, 3);
		moe.addGrade("Ringo", 0, 3);
		moe.addGrade("George", 16, 3);
		cout << moe << endl;

		cout << "\ntest 8: we're done (almost)! \nwhat should happen to all "
			<< "those students (or rather their records?)\n";

		cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
			<< "then make sure the following call works properly, i.e. no memory leaks\n";
		doNothing(secA2);
		cout << "Back from doNothing\n\n";

} // main