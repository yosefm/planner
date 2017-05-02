#include "coursecontrollerbase.h"

#ifndef COURSECONTROLLER_H
#define COURSECONTROLLER_H

class QString;
class Course;

class CourseController : public CourseControllerBase {
	Q_OBJECT
private:
	Course	*course;
	int		semester;
	bool	preffered;
	bool	selected;

	void	selectSelf();
	void	deselectSelf();

public:
	CourseController(Course *Icourse, int semester, QWidget* parent = 0,
		const char* name = 0, WFlags fl = 0 );

	Course* getCourse() const { return course; }
	void sync();

	QSize sizeHint() const { return size(); }

signals: 
	// Making the controller emit this, instead of the course,
	// allows us to maintain semester-based distinction.
	// We use the signals to pass data on the hours-worth so that
	// the listener doesn't have to know about the course.
	void used(QString number, float hours);
	void unused(QString number, float hours);

private slots:
	void selectionForced();
	void selectionRequested();
	void deselectionForced();
	void deselectionRequested();

public slots:
	void courseSelected			(int sem);
	void courseDeselected		();
	void requestPrefChange		();
	void prefChangeRequested	(int sem);
};
#endif
