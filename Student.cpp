#include "Student.h"
#include "Course.h"
//#include <iostream>
//#include <vector>
//#include <string>
using namespace std;
namespace BrooklynPoly {

	ostream& operator<<(ostream& os, const Student& rhs) {
		os << rhs.Student::getName() << ": ";
		if (rhs.courses.size() == 0) {
			os << "No courses.";
		}
		else {
			for (Course* cour : rhs.courses) {
				os << cour->getName() << " ";
			}
		}
		return os;
	}
	Student::Student(const string& name) : name(name) {};
	const string& Student::getName() const {
		return name;
	}
	bool Student::addCourse(Course* cour) {
		for (Course* c : courses) {
			if (c == cour) {
				return false;
			}
		}
		courses.push_back(cour);
		return true;
	}
	void Student::removedFromCourse(Course* cour) {
		for (size_t i = 0; i < courses.size(); i++) {
			if ((courses[i]) == cour) {
				swap(courses[i], courses[courses.size() - 1]);
				courses.pop_back();
			}
		}
	}
	//extra
	void Student::setName(const std::string& newName) {
		name = newName;
	}
	void Student::removeAllCourses() {
		for (Course* cour : courses) {
			cour->removeStudent(this);
		}
		courses.clear();
	}
}