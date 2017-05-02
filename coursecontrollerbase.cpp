/****************************************************************************
** Form implementation generated from reading ui file 'coursecontrollerbase.ui'
**
** Created: ו' אוק 21 00:12:49 2005
**      by: The User Interface Compiler ($Id: qt/main.cpp   3.3.4   edited Nov 24 2003 $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "coursecontrollerbase.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a CourseControllerBase as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CourseControllerBase::CourseControllerBase( QWidget* parent, const char* name, WFlags fl )
    : QWidget( parent, name, fl )
{
    if ( !name )
	setName( "CourseControllerBase" );
    setMinimumSize( QSize( 210, 50 ) );

    QWidget* privateLayoutWidget = new QWidget( this, "layout3" );
    privateLayoutWidget->setGeometry( QRect( 0, 0, 210, 52 ) );
    layout3 = new QHBoxLayout( privateLayoutWidget, 0, 0, "layout3"); 

    layout2 = new QVBoxLayout( 0, 0, 0, "layout2"); 

    courseNumber = new QLabel( privateLayoutWidget, "courseNumber" );
    courseNumber->setMinimumSize( QSize( 100, 15 ) );
    layout2->addWidget( courseNumber );

    courseTitle = new QLabel( privateLayoutWidget, "courseTitle" );
    courseTitle->setMinimumSize( QSize( 100, 15 ) );
    layout2->addWidget( courseTitle );
    layout3->addLayout( layout2 );

    controls = new QButtonGroup( privateLayoutWidget, "controls" );
    controls->setMinimumSize( QSize( 100, 20 ) );
    controls->setFrameShape( QButtonGroup::NoFrame );

    btnSelect = new QPushButton( controls, "btnSelect" );
    btnSelect->setGeometry( QRect( 0, 0, 20, 20 ) );
    btnSelect->setPaletteBackgroundColor( QColor( 0, 255, 0 ) );

    btnDeselect = new QPushButton( controls, "btnDeselect" );
    btnDeselect->setGeometry( QRect( 20, 0, 20, 20 ) );
    btnDeselect->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );

    btnDeselectNodeps = new QPushButton( controls, "btnDeselectNodeps" );
    btnDeselectNodeps->setGeometry( QRect( 20, 20, 20, 20 ) );
    btnDeselectNodeps->setPaletteBackgroundColor( QColor( 255, 0, 0 ) );

    btnSelectNodeps = new QPushButton( controls, "btnSelectNodeps" );
    btnSelectNodeps->setGeometry( QRect( 0, 20, 20, 20 ) );
    btnSelectNodeps->setPaletteBackgroundColor( QColor( 0, 255, 0 ) );

    btnUseMe = new QPushButton( controls, "btnUseMe" );
    btnUseMe->setGeometry( QRect( 40, 0, 60, 40 ) );
    layout3->addWidget( controls );
    languageChange();
    resize( QSize(210, 50).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( btnSelectNodeps, SIGNAL( clicked() ), this, SLOT( selectionForced() ) );
    connect( btnSelect, SIGNAL( clicked() ), this, SLOT( selectionRequested() ) );
    connect( btnDeselectNodeps, SIGNAL( clicked() ), this, SLOT( deselectionForced() ) );
    connect( btnDeselect, SIGNAL( clicked() ), this, SLOT( deselectionRequested() ) );
    connect( btnUseMe, SIGNAL( clicked() ), this, SLOT( requestPrefChange() ) );
}

/*
 *  Destroys the object and frees any allocated resources
 */
CourseControllerBase::~CourseControllerBase()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CourseControllerBase::languageChange()
{
    setCaption( tr( "Form1" ) );
    courseNumber->setText( QString::null );
    courseTitle->setText( QString::null );
    controls->setTitle( QString::null );
    btnSelect->setText( tr( "D" ) );
    btnDeselect->setText( tr( "D" ) );
    btnDeselectNodeps->setText( QString::null );
    btnSelectNodeps->setText( QString::null );
    btnUseMe->setText( tr( "Depend" ) );
}

void CourseControllerBase::selectionRequested()
{
    qWarning( "CourseControllerBase::selectionRequested(): Not implemented yet" );
}

void CourseControllerBase::selectionForced()
{
    qWarning( "CourseControllerBase::selectionForced(): Not implemented yet" );
}

void CourseControllerBase::deselectionRequested()
{
    qWarning( "CourseControllerBase::deselectionRequested(): Not implemented yet" );
}

void CourseControllerBase::deselectionForced()
{
    qWarning( "CourseControllerBase::deselectionForced(): Not implemented yet" );
}

void CourseControllerBase::requestPrefChange()
{
    qWarning( "CourseControllerBase::requestPrefChange(): Not implemented yet" );
}

