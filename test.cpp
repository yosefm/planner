#include <qapplication.h>
#include "coursecontroller.h"
#include "semesterbox.h"
#include "course.h"

int main(int argc, char **argv) {
	QApplication app(argc, argv);
	SemesterBox sb(NULL, 5);
	sb.newController( new Course("1", "2", NumVect(), 5) );
	sb.show();
	app.setMainWidget( &sb );
	app.exec();
	qDebug("size hint: %d", sb.sizeHint().width());
	return 0;
}
