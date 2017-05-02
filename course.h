
/********************* 
 * Defines a course with its dependencies 
 * and other needed information.
 */

#ifndef COURSE_H
#define COURSE_H

#include <qobject.h>
#include <qstring.h>

#include <vector>
#include <functional>

class Course;
typedef std::vector<Course *>	CourseVect;
typedef std::vector<int>		NumVect;

class Course : public QObject {
		Q_OBJECT
private:
		CourseVect	depend_on, depend_by;
		NumVect		semesters;
		QString		number;
		QString		title;
		
		float		hours, points;
		bool		is_user; // Was this course manually selected or as dep?
		
public:
		Course(const QString& Inumber, const QString& Ititle, 
			const NumVect& Isemesters, float Ihours);

		void addDependency	(Course *dep);
		void select			(int semester, Course *selector);
		void select			(int semester);
		void deselect		(Course *deselector);
		void deselect		();
		void changePrefSem	(int semester) { emit pref_changed(semester); }

		float	getHours() const		{ return hours; }
		QString getTitle() const		{ return title; }
		QString getNumber() const		{ return number; }
		NumVect getSemesters() const	{ return semesters; }
		bool	is_used() const			{ return (is_user || depend_by.size() ); }

signals:
		void pref_changed	(int semester);
		// This one should ALWAYS come AFTER selected() or deselected():
		void sel_changed	(); 
		void selected		(int semester);
		void deselected		();
};

class CourseByNum : public std::unary_function<Course *, bool> {
	QString number;
public:
	CourseByNum() {}
	CourseByNum(const QString& num) : number(num) {}

	void setNum(const QString& num) { number = num; }
	bool operator() (Course *course)	{ 
		if (!course) return 0;
		return course->getNumber() == number; 
	}
};

#endif //COURSE_H
