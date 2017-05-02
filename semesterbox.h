// A widget that holds a vertical column of CourseController 
// objects, and does some supervising.

#ifndef SEMESTERBOX_H
#define SEMESTERBOX_H

#include <QVBoxLayout>
#include <qlabel.h>

#include "coursecontroller.h"
#include "trackermap.h"
#include "course.h"

class SemesterBox : public QWidget {
	Q_OBJECT
private:
	TrackerMap 	courses_used;
	QLabel		*semester_lbl;
	QLabel		*hours_lbl;
	int			semester;

public:
	SemesterBox (QWidget* parent, int Isemester);

	CourseController* newController(Course *Icourse, 
		Qt::WindowFlags fl = 0 );
	QSize sizeHint() const { return size(); }
public slots:
	void courseSelChanged();
};

#endif
