/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_rectdialog.cpp
//  Description: the source file
//  -- MyPenDialog class implementation 
//     customizing the QDialog class for the Rectangle tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_rectdialog.h"

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

MyRectDialog::MyRectDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the line's draw type
   // Create a button group to contain all buttons
   drawtypegroup = new QButtonGroup( this );
   drawtypegroup->setGeometry( 0, 0, 500, 60 );
   drawtypegroup->setTitle ( "Draw Type" );
   connect( drawtypegroup, SIGNAL(clicked(int)), SLOT(OnSetDrawType(int)) );

   rb_rectangle = new QRadioButton( "Rectangle", drawtypegroup );
   rb_rectangle->setGeometry( 20, 20, 125, 30 );

   rb_roundrectangle = new QRadioButton( "Round Rectangle", drawtypegroup );
   rb_roundrectangle->setGeometry( 135, 20, 125, 30 );

   rb_circle = new QRadioButton( "Circle", drawtypegroup );
   rb_circle->setGeometry( 270, 20, 125, 30 );
   
   rb_ellipse = new QRadioButton( "Ellipse", drawtypegroup );
   rb_ellipse->setGeometry( 395, 20, 125, 30 );

   drawtype=0;
   
   switch( drawtype ){
      case 0:
         rb_rectangle->setChecked( TRUE );
      break;
      case 1:
         rb_roundrectangle->setChecked( TRUE );
      break;
      case 2:
         rb_circle->setChecked( TRUE );
      break;
      case 3:
         rb_ellipse->setChecked( TRUE );
      break;
   }
   
   // For setting the line's fill style
   // Create a button group to contain all buttons
   fillstylegroup = new QButtonGroup(this );
   fillstylegroup->setGeometry( 0, 60, 500, 120 );
   fillstylegroup->setTitle ( "Fill Style" );
   connect( fillstylegroup, SIGNAL(clicked(int)), SLOT(OnSetFillStyle(int)) );
   //first row
   rb_solid = new QRadioButton( "Solid", fillstylegroup );
   rb_solid->setGeometry( 20, 20, 80, 30 );

   rb_dense1 = new QRadioButton( "Dense 1", fillstylegroup );
   rb_dense1->setGeometry( 100, 20, 80, 30  );

   rb_dense2 = new QRadioButton( "Dense 2", fillstylegroup );
   rb_dense2->setGeometry( 180, 20, 80, 30  );
   
   rb_dense3 = new QRadioButton( "Dense 3", fillstylegroup );
   rb_dense3->setGeometry( 260, 20, 80, 30  );
   
   rb_dense4 = new QRadioButton( "Dense 4", fillstylegroup );
   rb_dense4->setGeometry( 360, 20, 100, 30  );
   
   //second row
   rb_dense5 = new QRadioButton( "Dense 5", fillstylegroup );
   rb_dense5->setGeometry( 20, 50, 80, 30 );

   rb_dense6 = new QRadioButton( "Dense 6", fillstylegroup );
   rb_dense6->setGeometry( 100, 50, 80, 30  );

   rb_dense7 = new QRadioButton( "Dense 7", fillstylegroup );
   rb_dense7->setGeometry( 180, 50, 80, 30  );
   
   rb_horizontal = new QRadioButton( "Horizontal", fillstylegroup );
   rb_horizontal->setGeometry( 260, 50, 90, 30  );
   
   rb_vertical = new QRadioButton( "Vertical", fillstylegroup );
   rb_vertical->setGeometry( 360, 50, 100, 30  );
   
   //third row
   rb_cross = new QRadioButton( "Cross", fillstylegroup );
   rb_cross->setGeometry( 20, 80, 80, 30 );

   rb_BDiag = new QRadioButton( "B. Diag", fillstylegroup );
   rb_BDiag->setGeometry( 100, 80, 80, 30  );

   rb_FDiag = new QRadioButton( "F.Diag", fillstylegroup );
   rb_FDiag->setGeometry( 180, 80, 80, 30  );
   
   rb_CDiag = new QRadioButton( "C.Diag", fillstylegroup );
   rb_CDiag->setGeometry( 260, 80, 80, 30  );
   
   rb_nopattern = new QRadioButton( "No Pattern", fillstylegroup );
   rb_nopattern->setGeometry( 360, 80, 100, 30  );
   
   brush.setStyle( Qt::NoBrush );
   
   switch(brush.style()){
      case Qt::SolidPattern:
         rb_solid->setChecked( TRUE );
      break;
      case Qt::Dense1Pattern:
         rb_dense1->setChecked( TRUE );
      break;
      case Qt::NoBrush:
         rb_nopattern->setChecked( TRUE );
      break;
      
   }
      

   // For setting the line's boundary style
   // Create a button group to contain all buttons
   boundarystylebgroup = new QButtonGroup( this );
   boundarystylebgroup->setGeometry( 0, 180, 320, 100 );
   boundarystylebgroup->setTitle ( "Boundary Style" );
   connect( boundarystylebgroup, SIGNAL(clicked(int)), SLOT(OnSetBoundaryStyle(int)) );
   // first line
   rb_solidline = new QRadioButton( "Solid Line", boundarystylebgroup );
   rb_solidline->setGeometry( 20, 20, 100, 30 );

   rb_dashline = new QRadioButton( "Dash Line", boundarystylebgroup );
   rb_dashline->setGeometry( 120, 20, 100, 30 );

   rb_dotline = new QRadioButton( "Dot Line", boundarystylebgroup );
   rb_dotline->setGeometry( 220, 20, 80, 30 );
   
   //second line
   rb_dashdotline = new QRadioButton( "Dash dot line", boundarystylebgroup );
   rb_dashdotline->setGeometry( 20, 50, 100, 30  );
   
   rb_dashdotdotline = new QRadioButton( "Dash dot dot Line", boundarystylebgroup );
   rb_dashdotdotline->setGeometry( 120, 50, 100, 30 );

   rb_noline = new QRadioButton( "No Line", boundarystylebgroup );
   rb_noline->setGeometry( 220, 50, 80, 30 );

   
   switch( pen.style()){
      case Qt::SolidLine:
         rb_solidline->setChecked( TRUE );
      break;
      case Qt::DashLine:
         rb_dashline->setChecked( TRUE );
      break;
      case Qt::DotLine:
         rb_dotline->setChecked( TRUE );
      break;
      case Qt::DashDotLine:
         rb_dashdotline->setChecked( TRUE );
      break;
      case Qt::DashDotDotLine:
         rb_dashdotdotline->setChecked( TRUE );
      break;
      case Qt::NoPen:
         rb_noline->setChecked( TRUE );
      break;
   }

   // For setting the line's boundary join style
   // Create a button group to contain all buttons
   boundary_joinstylegroup = new QButtonGroup( this );
   boundary_joinstylegroup->setGeometry( 0, 280, 320, 60 );
   boundary_joinstylegroup->setTitle ( "Boundary join Style" );
   connect( boundary_joinstylegroup, SIGNAL(clicked(int)), SLOT(OnSetBoundaryJoinStyle(int)) );
   // first line
   rb_miter = new QRadioButton( "Miterjoin", boundary_joinstylegroup );
   rb_miter->setGeometry( 20, 20, 100, 30 );

   rb_bevel = new QRadioButton( "Bevel join", boundary_joinstylegroup );
   rb_bevel->setGeometry( 120, 20, 100, 30 );

   rb_round = new QRadioButton( "Round join", boundary_joinstylegroup );
   rb_round->setGeometry( 220, 20, 90, 30 );
   
   pen.setJoinStyle( Qt::MiterJoin );
   switch( pen.joinStyle()){
      case Qt::MiterJoin:
         rb_miter->setChecked( TRUE );
      break;
      case Qt::BevelJoin:
         rb_bevel->setChecked( TRUE );
      break;
      case Qt::RoundJoin :
         rb_round->setChecked( TRUE );
      break;
   }
   
   // For setting the line's fill color
   // Create a button group to contain all buttons
   fillcolorgroup = new QButtonGroup( this );
   fillcolorgroup->setGeometry( 320, 180, 180, 160 );
   fillcolorgroup->setTitle ( "FillColor" );
   connect( fillcolorgroup, SIGNAL(clicked(int)), SLOT(OnSetFillColor(int)) );
  
   rb_foreground = new QRadioButton( "Fore-ground", fillcolorgroup );
   rb_foreground->setGeometry( 10, 20, 100, 30 );

   rb_background = new QRadioButton( "Back-ground", fillcolorgroup );
   rb_background->setGeometry( 10, 50, 100, 30 );
   fillcolor=0;
    switch(fillcolor){
      case 0:
         rb_foreground->setChecked( TRUE );
      break;
      case 1:
         rb_background->setChecked( TRUE );
      break;
    }
    
   // For setting the line width
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 1, 40 );
   widthslider->setLineStep ( 1 );
   widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 120, 340, 300, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 1 );

   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetPenWidth(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,340,110,20 );
   wl->setText( "Boundary Width" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 450, 340, 20, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(500,400);
}

MyRectDialog::~MyRectDialog()
{
    //delete draw type
   delete drawtypegroup;
   delete rb_rectangle;
   delete rb_roundrectangle;
   delete rb_circle;
   delete rb_ellipse;
   
   //delete fill style
   delete fillstylegroup;
   delete rb_solid;
   delete rb_dense1;
   delete rb_dense2;
   delete rb_dense3;
   delete rb_dense4;
   delete rb_dense5;
   delete rb_dense6;
   delete rb_dense7;
   delete rb_horizontal;
   delete rb_vertical;
   delete rb_cross;
   delete rb_BDiag;
   delete rb_FDiag;
   delete rb_CDiag;
   delete rb_nopattern;
   
   //delete boundary style
   delete boundarystylebgroup;
   delete rb_solidline;
   delete rb_dashline;
   delete rb_dotline;
   delete rb_dashdotline;
   delete rb_dashdotdotline;
   delete rb_noline;
   
   //delete boundary join style
   delete boundary_joinstylegroup;
   delete rb_miter;
   delete rb_bevel;
   delete rb_round;
   
   //delete boundary join style
   delete fillcolorgroup;
   delete rb_foreground;
   delete rb_background;
   
   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyRectDialog::OnSetPenWidth(int w)
{
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

   pen.setWidth( w );
}

void MyRectDialog::OnSetDrawType(int type){
    switch( type ){
      case 0://draw rectangle
         drawtype=0;
         break;
      case 1://draw round rectangle
         drawtype=1;
         break;
      case 2://draw circle
         drawtype=2;
         break;
      case 3://draw ellipse
         drawtype=3;
         break;   
   }
}

void MyRectDialog::OnSetFillStyle(int type){
    switch( type ){
      case 0:
         brush.setStyle( Qt::SolidPattern );
         break;
      case 1:
         brush.setStyle( Qt::Dense1Pattern );
         break;
      case 2:
         brush.setStyle( Qt::Dense2Pattern );
         break;
      case 3:
         brush.setStyle( Qt::Dense3Pattern );
         break;   
      case 4:
         brush.setStyle( Qt::Dense4Pattern );
         break;   
      case 5:
         brush.setStyle( Qt::Dense5Pattern );
         break;
      case 6:
         brush.setStyle( Qt::Dense6Pattern );
         break;
      case 7:
         brush.setStyle( Qt::Dense7Pattern );
         break;
      case 8:
         brush.setStyle( Qt::HorPattern );
         break;
      case 9:
         brush.setStyle( Qt::VerPattern );
         break; 
      case 10:
         brush.setStyle( Qt::CrossPattern );
         break;
      case 11:
         brush.setStyle( Qt::BDiagPattern );
         break;
      case 12:
         brush.setStyle( Qt::FDiagPattern );
         break;
      case 13:
         brush.setStyle( Qt::DiagCrossPattern );
         break;
      case 14:
         brush.setStyle( Qt::NoBrush );
         break;
    }
}

void MyRectDialog::OnSetBoundaryStyle(int type){
    switch( type ){
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

// slot to set the boundary join style
void MyRectDialog::OnSetBoundaryJoinStyle(int type)
{
   switch( type ){
      case 0:
         pen.setJoinStyle( Qt::MiterJoin );
         break;
      case 1:
         pen.setJoinStyle( Qt::BevelJoin );
         break;
      case 2:
         pen.setJoinStyle( Qt::RoundJoin );
         break;
   }
}

//slot to set the fill color
void MyRectDialog::OnSetFillColor(int type){
    switch( type ){
      case 0://set foreground for outline and fill
        
         break;
      case 1://set background for fill
         brush.setColor( backgroundColor );
         break;
    }
}