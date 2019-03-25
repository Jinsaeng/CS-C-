#include "Registrar.h"
#include "Student.h"
#include "Course.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
namespace BrooklynPoly {
	Registrar::Registrar() {};
	bool Registrar::addCourse(const string& cour) {
		if (courses.size() + 1 == Registrar::findCourse(cour)) {
			return false;
		}
		Course* newCour = new Course(cour);
		courses.push_back(newCour);
		return true;
	};
	bool Registrar::addStudent(const string& stud) {
		if (students.size() + 1 == findStudent(stud)) {
			return false;
		}
		Student* newStud = new Student(stud);
		students.push_back(newStud);
		return true;
	}
	size_t Registrar::findStudent(const string& stud)const {
		for (size_t i = 0; i < students.size(); i++) {
			if (students[i]->getName() == stud) {
				return i;
			}
		}
		return students.size();
	}
	size_t Registrar::findCourse(const string& cour) const {
		for (size_t i = 0; i < courses.size(); i++) {
			if (courses[i]->getName() == cour) {
				return i;
			}
		}
		return courses.size();
	}
	bool Registrar::enrollStudentInCourse(const string& studentName,
		const string& courseName) {
		size_t coursenum = findCourse(courseName);
		size_t studnum = findStudent(studentName);
		if ((courses.size() == coursenum) || (students.size() == studnum)) {
			return false;
		}

		courses[coursenum]->addStudent(students[studnum]);
		students[studnum]->addCourse(courses[coursenum]);
		return true;
	}
	bool Registrar::cancelCourse(const string& courseName) {
		size_t courseInd = findCourse(courseName);
		if (courses.size() == courseInd) {
			return false;
		}
		courses[courseInd]->removeStudentsFromCourse();
		delete courses[courseInd];
		swap(courses[courseInd], courses[courses.size() - 1]);
		courses.pop_back();
		return true;
	}
	void Registrar::purge() {
		for (Student* stud : students) {
			delete stud;
			stud = nullptr;
		}
		for (Course* cour : courses) {
			delete cour;
			cour = nullptr;
		}
		students.clear();
		courses.clear();
	}
	ostream& operator<<(ostream& os, const Registrar& rhs) {
		os << "Registrar's Report" << endl;
		os << "Courses: " << endl;
		for (Course* cour : rhs.courses) {
			os << *cour << endl;
		}
		os << "Students: " << endl;
		for (Student* per : rhs.students) {
			os << *per << endl;
		}
		os << endl;
		return os;
	}
	//extra
	bool Registrar::changeStudentName(const string& old, const string& newName) {
		size_t oldInd= Registrar::findStudent(old);
		if (oldInd == students.size()) {
			return false;
		}
		students[oldInd]->setName(newName);
		return true;
	}
	bool Registrar::dropStudentFromCourse(const string& stud, const string& cour) {
		size_t studInd = Registrar::findStudent(stud);
		size_t courInd = Registrar::findCourse(cour);
		if ((courses.size() == courInd) || (students.size() == studInd)) {
			return false;
		}
		students[studInd]->removedFromCourse(courses[courInd]);
		courses[courInd]->removeStudent(students[studInd]);
		return true;
	}
	bool Registrar::removeStudent(const string& stud) {
		size_t studInd = Registrar::findStudent(stud);
		if (students.size() == studInd) {
			return false;
		}
		//remove all attached courses
		students[studInd]->removeAllCourses();
		delete students[studInd];
		swap(students[studInd], students[students.size() - 1]);
		return true;
	}
}