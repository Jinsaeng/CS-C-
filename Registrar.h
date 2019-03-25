#pragma once
#ifndef REGISTRAR_H
#define REGISTRAR_H
#include<iostream>
#include<string>
#include<vector>
namespace BrooklynPoly {
	class Student;
	class Course;
	class Registrar {
		friend std::ostream& operator<<(std::ostream& os, const Registrar& rhs);
	public:
		Registrar();
		bool addCourse(const std::string& cour);
		bool addStudent(const std::string& stud);
		bool enrollStudentInCourse(const std::string& studentName,
			const std::string& courseName);
		bool cancelCourse(const std::string& courseName);
		void purge();
		//extra
		bool changeStudentName(const std::string& old, const std::string& newName);
		bool dropStudentFromCourse(const std::string& stud, const std::string& cour);
		bool removeStudent(const std::string& stud);
	private:
		size_t findStudent(const std::string&) const;
		size_t findCourse(const std::string&) const;

		std::vector<Course*> courses;
		std::vector<Student*> students;
	};
}

#endif