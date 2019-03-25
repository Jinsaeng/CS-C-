#include "Course.h"
#include "Student.h"
//#include <iostream>
//#include <string>
//#include <vector>
using namespace std;
namespace BrooklynPoly {
	ostream& operator<<(ostream& os, const Course& rhs) {
		os << rhs.Course::getName() << ": ";
		if (rhs.students.size() == 0) {
			os << "No students.";
		}
		else {
			for (Student* per : rhs.students) {
				os << per->getName();
			}
		}
		return os;
	};
	Course::Course(const string& courseName) : name(courseName) {};
	const string& Course::getName() const {
		return name;
	}
	bool Course::addStudent(Student* stud) {
		for (Student* s : students) {
			if (s == stud) {
				return false;
			}
		}
		students.push_back(stud);
		return true;
	}
	void Course::removeStudentsFromCourse() {
		for (Student* stud : students) {
			stud->removedFromCourse(this);
		}

	}
	//extra
	bool Course::removeStudent(Student* stud) {
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i] == stud) {
				swap(students[i], students[students.size() - 1]);
				students.pop_back();
				return true;
			}
		}
		return false;
	}
}