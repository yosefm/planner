
#include "course.h"

// The constructor is the only way to set private variables, except for 
// the dependency lists which are set either directly (addDependency)
// or indirectly (selecting the course by another course).
Course::Course(const QString& Inumber, const QString& Ititle, 
	const NumVect& Isemesters, float Ihours) {
	hours = Ihours;
	number = Inumber;
	title = Ititle;
	semesters = Isemesters;
	is_user = false;
}

// <addDependency> adds a course to the list of courses that must be taken
// before this one.
void Course::addDependency(Course *dep) {
	depend_on.push_back(dep);
}

// <select>, in its two forms, does the selection in 3 possible ways:
// 1. no selector: Only activate the course, do nothing with deps.
// 2. selector = this: Activate the course and the deps, and mark the course
//    as user-selected.
// 3. else: activate the course and the dependencies.
// If the course was not already selected, signals the selection.
void Course::select(int semester, Course *selector) {
	// Save current selection flag so we'll know whether to emit a signal or 
	// not. If the course was already selected, there's no need to inform the
	// GUI that it was.
	bool was_selected = is_user || depend_by.size();

	// Update selection status (including dependency list).
	if (selector != this) {
		// Try to find our selector in the dependency by its numer.
		CourseByNum finder(selector->getNumber());
		CourseVect::iterator iter = find_if (depend_by.begin(), depend_by.end(), 
			finder);

		if ( iter == depend_by.end() ) {
			depend_by.push_back(selector);
		}
	} else {
		is_user = true;
	}
	
	for (CourseVect::iterator iter = depend_on.begin(); 
		iter != depend_on.end(); iter++) {
		(*iter)->select(0, this);
	}
	
	if (is_user || ! was_selected) {
		emit selected(semester);
		emit sel_changed();
	}
}

void Course::select(int semester) {
	is_user = true;
	emit selected(semester);
	emit sel_changed();
}

// <deselect>, in its two forms, deselects the course in 3 ways:
// 1, no deselector: Deselect the course and clear the list of courses depending 
//    on it.
// 2. deselector = this: mark the object as not user-selected,
//    deselect it if nobody depends on it.
// 3. else: Remove the deselector from the list of courses 
//    depending on this one and if its empty and the course is not 
//    user-selected, deselect the course.
// If the course was indeed deselected, a signal is emitted.
void Course::deselect(Course *deselector) {
	if (deselector != this) {
		// Use the course number for removal.
		CourseByNum finder(deselector->getNumber());
		CourseVect::iterator current = 
			find_if(depend_by.begin(), depend_by.end(), finder);

		if (current != depend_by.end()) {
				depend_by.erase(current);
		}
	} else {
		is_user = false;
	}
	
	for (CourseVect::iterator iter = depend_on.begin(); 
		iter != depend_on.end(); iter++) {
		(*iter)->deselect(this);
	}
	
	// Emit signal only if the course is totally removed.
	if (!( is_user || depend_by.size() )) {
		emit deselected();
		emit sel_changed();
	}
}

void Course::deselect() {
	is_user = false;
	depend_by.erase( depend_by.begin(), depend_by.end() );

	emit deselected();
	emit sel_changed();
}
