#include "semesterbox.h"

SemesterBox::SemesterBox (QWidget* parent, int Isemester) 
	: QWidget(parent), semester(Isemester) 
{
	semester_lbl = new QLabel( "Semester " + QString::number(semester));
	semester_lbl->setSizePolicy( 
		QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed)
	);

	hours_lbl = new QLabel( "Hours: 0");
	hours_lbl->setSizePolicy( 
		QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed)
	);
        
        auto lay = new QVBoxLayout();
        lay->addWidget(semester_lbl);
        lay->addWidget(hours_lbl);
        setLayout(lay);
}

CourseController* SemesterBox::newController(Course *Icourse, Qt::WindowFlags fl) {
	CourseController* cont = 
		new CourseController(Icourse, semester, this, fl);
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
        
        layout()->addWidget(cont);
	return cont;
}

void SemesterBox::courseSelChanged() {
	hours_lbl->setText( "Hours: " + QString::number( courses_used.total() ) );
}
