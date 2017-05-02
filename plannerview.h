// Defines a class for the main view of the planner application.

#ifndef PLANNERVIEW_H
#define PLANNERVIEW_H

#include <vector>
#include <map>

#include <qmainwindow.h>
#include <qwidget.h>

#include "semesterbox.h"
#include "trackermap.h"
#include "course.h"

#define PV_DEFAULT_HEIGHT 500

typedef std::map<int, SemesterBox*>	NumToCol;

class PlannerView : public QMainWindow {
	Q_OBJECT
private:
	NumToCol	sem_cols;
	TrackerMap	hours_count;

	void	extractSemesters	(Course *course);

private slots:
	void statusUpdated();

public:
	PlannerView(CourseVect *courses, QWidget *parent = 0, 
		Qt::WindowFlags f = 0);
};

#endif
