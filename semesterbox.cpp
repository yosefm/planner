#include "semesterbox.h"

SemesterBox::SemesterBox (QWidget* parent, int Isemester) 
	: QVBox(parent), semester(Isemester) {
	semester_lbl = new QLabel( "Semester " + QString::number(semester), this);
	semester_lbl->setSizePolicy( 
		QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed, false)
	);

	hours_lbl = new QLabel( "Hours: 0", this );
	hours_lbl->setSizePolicy( 
		QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed, false)
	);
}

CourseController* SemesterBox::newController(Course *Icourse, const char* name,
	WFlags fl) {
	CourseController* cont = 
		new CourseController(Icourse, semester, this, name, fl);
	QObject::connect( 
		cont, SIGNAL( used(QString, float) ),
		&courses_used, SLOT( keyUsed(QString, float) ) 
	);
	QObject::connect( 
		cont, SIGNAL( unused(QString, float) ),
		&courses_used, SLOT( keyUnused(QString, float) ) 
	);
	QObject::connect( 
		Icourse, SIGNAL( sel_changed() ), 
		this, SLOT( courseSelChanged() ) 
	);

	return cont;
}

void SemesterBox::courseSelChanged() {
	hours_lbl->setText( "Hours: " + QString::number( courses_used.total() ) );
}
