/****************************************************************************
** Form interface generated from reading ui file 'coursecontrollerbase.ui'
**
** Created: ו' אוק 21 00:12:35 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef COURSECONTROLLERBASE_H
#define COURSECONTROLLERBASE_H

#include <qvariant.h>
#include <qwidget.h>

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QButtonGroup;
class QPushButton;

class CourseControllerBase : public QWidget
{
    Q_OBJECT

public:
    CourseControllerBase( QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~CourseControllerBase();

    QLabel* courseNumber;
    QLabel* courseTitle;
    QButtonGroup* controls;
    QPushButton* btnSelect;
    QPushButton* btnDeselect;
    QPushButton* btnDeselectNodeps;
    QPushButton* btnSelectNodeps;
    QPushButton* btnUseMe;

public slots:
    virtual void requestPrefChange();

protected:
    QHBoxLayout* layout3;
    QVBoxLayout* layout2;

protected slots:
    virtual void languageChange();

    virtual void selectionRequested();
    virtual void selectionForced();
    virtual void deselectionRequested();
    virtual void deselectionForced();


};

#endif // COURSECONTROLLERBASE_H
