/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_linedialog.cpp
//  Description: the source file
//  -- MyLineDialog class implementation 
//     customizing the QDialog class for the Line tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_linedialog.h"

#include <qpainter.h>
#include <qmessagebox.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtextedit.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpushbutton.h>
#include <qradiobutton.h>
#include <qbuttongroup.h>

MyLineDialog::MyLineDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's linestyle
   // Create a button group to contain all buttons
   linestylebgroup = new QButtonGroup( this );
   linestylebgroup->setGeometry( 0, 0, 200, 220 );
   linestylebgroup->setTitle ( "Line Style" );
   connect( linestylebgroup, SIGNAL(clicked(int)), SLOT(OnSetLineStyle(int)) );

   rb_solidline = new QRadioButton( "Solid line", linestylebgroup );
   rb_solidline->setGeometry( 5, 20, 100, 30 );

   rb_dashline = new QRadioButton( "Dash line", linestylebgroup );
   rb_dashline->setGeometry( 5, 50, 100, 30 );

   rb_dotline = new QRadioButton( "Dot line", linestylebgroup );
   rb_dotline->setGeometry( 5, 80, 100, 30 );
   
   rb_dashdotline = new QRadioButton( "Dash dot line", linestylebgroup );
   rb_dashdotline->setGeometry( 5, 110, 120, 30 );
   
   rb_dashdotdotline = new QRadioButton( "Dash dot dot line", linestylebgroup );
   rb_dashdotdotline->setGeometry( 5, 140, 180, 30 );

   pen.setStyle( Qt::SolidLine  );
   switch( pen.style() ){
      case Qt::MPenStyle :
      case Qt::SolidLine :
         rb_solidline->setChecked( TRUE );
      break;
      case Qt::DashLine :
         rb_dashline->setChecked( TRUE );
      break;
      case Qt::DotLine :
         rb_dotline->setChecked( TRUE );
      break;
      case Qt::DashDotLine :
         rb_dashdotline->setChecked( TRUE );
      break;
      case Qt::DashDotDotLine :
         rb_dashdotdotline->setChecked( TRUE );
      break;
   }
   
   // For setting the line's linetype
   // Create a button group to contain all buttons
   linetypegroup = new QButtonGroup( this );
   linetypegroup->setGeometry( 210, 130, 170, 100 );
   linetypegroup->setTitle ( "Line Type" );
   connect( linetypegroup, SIGNAL(clicked(int)), SLOT(OnSetLineType(int)) );

   rb_single = new QRadioButton( "Single", linetypegroup );
   rb_single->setGeometry( 10, 20, 100, 30 );

   rb_poly = new QRadioButton( "Poly", linetypegroup );
   rb_poly->setGeometry( 10, 50, 100, 30);
  
  poly=false;
   if (poly){
         rb_poly->setChecked( TRUE );
      }else
         rb_single->setChecked( TRUE );
         
  firstChoosePoly=false;
   
   
   // For setting the line's captstyle
   // Create a button group to contain all buttons
   capstylebgroup = new QButtonGroup( this );
   capstylebgroup->setGeometry( 210, 0, 170, 120 );
   capstylebgroup->setTitle ( "Cap Style" );
   connect( capstylebgroup, SIGNAL(clicked(int)), SLOT(OnSetCapStyle(int)) );

   rb_flatcap = new QRadioButton( "Flat", capstylebgroup );
   rb_flatcap->setGeometry( 10, 20, 100, 30 );

   rb_squarecap = new QRadioButton( "Square", capstylebgroup );
   rb_squarecap->setGeometry( 10, 50, 100, 30);

   rb_roundcap = new QRadioButton( "Round", capstylebgroup );
   rb_roundcap->setGeometry( 10, 80, 100, 30);
  
  
   pen.setCapStyle( Qt::FlatCap );
   switch( pen.capStyle() ){
      case Qt::MPenCapStyle:
      case Qt::FlatCap:
         rb_flatcap->setChecked( TRUE );
      break;
      case Qt::SquareCap:
         rb_squarecap->setChecked( TRUE );
      break;
      case Qt::RoundCap:
         rb_roundcap->setChecked( TRUE );
      break;
     
   }

   // For setting the line width
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setLineStep ( 1 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 80, 220, 190, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 1 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetLineWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,220,70,20 );
   wl->setText( "Line Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 280, 220, 20, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(400,250);
}

MyLineDialog::~MyLineDialog()
{
   delete linestylebgroup;
   delete rb_solidline;
   delete rb_dashline;
   delete rb_dotline;
   delete rb_dashdotline;
   delete rb_dashdotdotline;

   delete linetypegroup;
   delete rb_single;
   delete rb_poly;

   delete rb_flatcap;
   delete rb_squarecap;
   delete rb_roundcap;
   delete capstylebgroup;

   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
void MyLineDialog::OnSetLineStyle(int style){
    switch( style){
      case 0:
         pen.setStyle( Qt::SolidLine );
         break;
      case 1:
         pen.setStyle( Qt::DashLine );
         break;
      case 2:
         pen.setStyle( Qt::DotLine );
         break;
      case 3:
         pen.setStyle( Qt::DashDotLine);
         break;
      case 4:
         pen.setStyle( Qt::DashDotDotLine);
         break;
      case 5:
         pen.setStyle( Qt::NoPen );
         break;  
    }
}

// slot to set the cap style
void MyLineDialog::OnSetCapStyle(int type)
{
   switch( type ){
      case 0:
         pen.setCapStyle( Qt::FlatCap );
         break;
      case 1:
         pen.setCapStyle( Qt::SquareCap );
         break;
      case 2:
         pen.setCapStyle( Qt::RoundCap );
         break;
   }
}

void MyLineDialog::OnSetLineType(int type){
  switch(type) {
    case 0: //single
      poly=false;
      firstChoosePoly=false;
      break;
    case 1: //poly
      poly=true;
      firstChoosePoly=true;
      resetPoly = false;
      break;
  }
   
}

// slot to set the line width
void MyLineDialog::OnSetLineWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}