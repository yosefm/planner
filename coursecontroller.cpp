#include <qlabel.h>
#include <qpushbutton.h>

#include "coursecontroller.h"
#include "course.h"

//  The constructor is the only way to set the private variables.
//  Here we also connect the controller to 3 signals that the course emits.
//  The signalling is one-way: the controller emits nothing. It calls 
//  methods directly on the course. 
CourseController::CourseController(Course *Icourse, int Isemester, 
		QWidget* parent, Qt::WindowFlags fl) : 
		QWidget(parent, fl) {
        setupUi(this);
        setAutoFillBackground(true);
        backgr = palette().color(QPalette::Window);
        
	course = Icourse;
	semester = Isemester;
	preffered = false;
	selected = false;
	sync();

	connect( course, SIGNAL(pref_changed(int)), SLOT(prefChangeRequested(int)) );
	connect( course, SIGNAL(selected(int)), SLOT(courseSelected(int)) );
	connect( course, SIGNAL(deselected()), SLOT(courseDeselected()) );
}

//  <sync> does the initialization of internal widgets. 
void CourseController::sync() {
	courseNumber->setText( course->getNumber() );
	courseTitle->setText( course->getTitle() );
}

void CourseController::selectSelf() {
	selected = true;
        auto pal = palette();
        pal.setColor(QPalette::Background, Qt::green);
	setPalette(pal);
	emit used( course->getNumber(), course->getHours() );
}

void CourseController::deselectSelf() {
	selected = false;
	auto pal = palette();
        pal.setColor(QPalette::Background, backgr);
	setPalette(pal);;
	emit unused( course->getNumber(), course->getHours() );
}

//  This one is connected with the button that selects 
//  the course without selecting its dependencies. 
void CourseController::selectionForced() {
	course->select(semester);
}

//  Connected with the button that selects the course and its dependencies 
void CourseController::selectionRequested() {
	//We need to recurse over dependencies now.
	course->select(semester, course);
}

//  Connected with the button that deselects the course even if it supplies a
//  dependency. 
void CourseController::deselectionForced() {
	course->deselect();
}

//  Connected with the button that requests to remove the course only if it 
//  does not supply a dependency. 
void CourseController::deselectionRequested() {
	course->deselect(course);
}

// Traps the signal from the course and decides if its relevant
// to the controller. If it is, lights the controller.
void CourseController::courseSelected(int sem) {
	// sem = 0 means 'use default'.
	if ((sem == semester) || (!sem && preffered)) {
		if ( ! selected ) {
			selectSelf();
		}
	} else {
		if ( selected ) {
			deselectSelf();
		}
	}
}

// Traps the signal from the course, and dimms the controller.
void CourseController::courseDeselected() {
	if ( selected ) {
		deselectSelf();
	}
}

// Used by the dependency selection button and others. It is used to
// declare the controller as the preferred one for dependency use of
// the course.
void CourseController::requestPrefChange() {
	course->changePrefSem(semester);
}

// When a preference is changes, the course is used as a hub and it 
// informs all the controllers by a signal. This method checks to see
// If this controller is the new preferred one, and indicates it if so.
void CourseController::prefChangeRequested(int sem) {
	if (sem == semester) {
		preffered = true;
                auto pal = btnUseMe->palette();
                pal.setColor(QPalette::Background, Qt::yellow);
		btnUseMe->setPalette(pal);
	} else {
		preffered = false;
                auto pal = btnUseMe->palette();
                pal.setColor(QPalette::Background, backgr);
		btnUseMe->setPalette(pal);
	}
}
