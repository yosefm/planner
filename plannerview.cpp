#include <algorithm>

#include <QtGui>
#include <QScrollArea>
#include <qstatusbar.h>

#include "plannerview.h"
#include "coursecontroller.h"

PlannerView::PlannerView(CourseVect *courses, QWidget *parent,
	Qt::WindowFlags f) : QMainWindow(parent, f)
{
	auto *sv = new QScrollArea( this );
        auto canvas = new QFrame();
	sv->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );

	// An HBox to hold semester collumns:
	auto columns = new QHBoxLayout();
	canvas->setLayout( columns );

	// Prepare the map of column per semester:
	for (CourseVect::iterator course = courses->begin(); 
		course != courses->end(); course++) {
                extractSemesters((*course));
	}

	// Create a column for each semester:
	QWidget *widg;
	for (NumToCol::iterator sems_iter = sem_cols.begin(); 
		sems_iter != sem_cols.end(); sems_iter++) {
                widg = new QWidget();
		(*sems_iter).second = new SemesterBox(widg, (*sems_iter).first);
                columns->addWidget((*sems_iter).second);
	}

	//Create all relevant controllers:
	for (CourseVect::iterator course_iter = courses->begin(); 
		course_iter != courses->end(); course_iter++) {
		CourseController *course_first = NULL, *new_cont;

		// We want the semesters list sorted to help us select the 
		// first controller to be the default.
		NumVect semesters = (*course_iter)->getSemesters();
		std::sort( semesters.begin(), semesters.end() );
		
		for (unsigned int indx = 0; indx < semesters.size(); indx++) {
			new_cont = sem_cols[semesters[indx]]->newController(*course_iter);
			QObject::connect( 
				new_cont, SIGNAL( used(QString, float) ), 
				&hours_count, SLOT( keyUsed(QString, float) )
			);
			QObject::connect( 
				new_cont, SIGNAL( unused(QString, float) ), 
				&hours_count, SLOT( keyUnused(QString, float) )
			);
			QObject::connect(
				new_cont->getCourse(), SIGNAL( sel_changed() ),
				this, SLOT( statusUpdated() ) 
			);

			if (! course_first) {
				course_first = new_cont;
			}
		}

		// Set the first semester as the default when a course is selected 
		// as dependency
		course_first->requestPrefChange();
	}

	//sv->setResizePolicy(QScrollArea::AutoOneFit);
        sv->setWidget(canvas);

	sv->resize(columns->sizeHint().width() + sv->verticalScrollBar()->width(),
		 PV_DEFAULT_HEIGHT);
	setCentralWidget( sv );
	resize(sv->size());
        sv->widget()->show();

	statusBar()->showMessage("Hours: 0");
}

void PlannerView::extractSemesters(Course *course) {
	NumVect	semesters = course->getSemesters();

	for (unsigned int indx = 0; indx < semesters.size(); indx++) {
		sem_cols.insert( NumToCol::value_type(semesters[indx], NULL) );
	}
}

void PlannerView::statusUpdated() {
		statusBar()->showMessage( "Hours: " + QString::number(hours_count.total()) );
}
