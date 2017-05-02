#include <qapplication.h>
#include <qsqldatabase.h>
#include <qsqlcursor.h>
#include <qfile.h>

#include "course.h"
#include "plannerview.h"

Course	*readCourse		(QSqlCursor course_cursor);
NumVect	*getSemesters	(QString number);
void	addDependencies (Course *course, CourseVect available);

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	QString app_called_as(argv[0]);
	CourseVect	courses;

	// Decide on a DB name.
	QString dbname("courses.db");
	if (argc > 1) {
		dbname = argv[1];
	}

	// Check if the db file exists, else abort.
	if ( ! QFile::exists(dbname) ) {
		qWarning( app_called_as + ": " + dbname +
			"does not exist. Aborting." );
		return FALSE;
	}
	
	// Open the Database or abort:
	QSqlDatabase *courseDB = QSqlDatabase::addDatabase("QSQLITE");
	courseDB->setDatabaseName(dbname);
	
	if ( ! courseDB->open() ) {
		qWarning( "Failed to open database" + dbname + ":  " 
			+ courseDB->lastError().text() );
		return FALSE;
	}
	
	// Read courses and create their objects:
	QSqlCursor course_cursor("courses");
	course_cursor.select();

	while ( course_cursor.next() ) {
		courses.push_back( readCourse(course_cursor) );
	}
	
	// Connect dependencies now. We do this only now that all of the course
	// objects are available.
	for (CourseVect::iterator course_iter = courses.begin();
		course_iter != courses.end(); course_iter++ ) {
		addDependencies( *course_iter, courses );
	}

	PlannerView *pv = new PlannerView(&courses);
	pv->show();
	// Set the widget's width to show al semesters.

	app.setMainWidget(pv);
	return app.exec();
}

// <readcourse> does all the dirty work of constructing
// a course from the DB info.
Course *readCourse(QSqlCursor course_cursor) {
	QString course_number( course_cursor.value("number").toString() );
	NumVect *semesters = getSemesters( course_number );
	
	//TODO: Type checking.
	Course* course = new Course( course_number, 
		course_cursor.value("title").toString(), *semesters,
		(float)course_cursor.value("hours").toDouble() );

	return course;
}

// <addDependencies> connects each course with its dependencies.
void addDependencies( Course *course, CourseVect available ) {
	QSqlCursor deps_cursor("deps");

	deps_cursor.select( "course=" + course->getNumber() );
	CourseVect::iterator found;
	CourseByNum finder;
	while ( deps_cursor.next() ) {
		finder.setNum(deps_cursor.value("depends_on").toString());
		if ( (found = std::find_if(available.begin(), 
			available.end(), finder)) != available.end() ) {
			course->addDependency(*found);
		}
	}
}

// This function constructs a list of semesters
// in which a course is given. Uses the default database.
NumVect *getSemesters(QString number) {
	NumVect *semesters = new NumVect;
	QSqlCursor semesters_cursor("times");

	semesters_cursor.select("course=" + number);
	while ( semesters_cursor.next() ) {
		semesters->push_back(
			semesters_cursor.value("semester").toInt() );
	}
	
	return semesters;
}
