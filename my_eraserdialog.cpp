/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_eraserdialog.cpp
//  Description: the source file
//  -- MyEraserDialog class implementation 
//     customizing the QDialog class for the Eraser tool
/****************************************/

#include <iostream>
using namespace std;
#include <string.h>

#include "my_eraserdialog.h"

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

MyEraserDialog::MyEraserDialog(QWidget* parent, const char* name)
:QDialog(parent, name)
{
   // For setting the eraser size
   widthslider = new QSlider( QSlider::Horizontal, this, "width slider" );
   widthslider->setRange ( 10, 100 );
   widthslider->setLineStep ( 1 );
   //widthslider->setValue ( pen.width() );
   widthslider->setGeometry  ( 60, 40, 250, 20 );
   widthslider->setTickmarks( QSlider::Below );
   widthslider->setTickInterval( 1 );
   size=10;
   connect( widthslider, SIGNAL(valueChanged(int)),
                 this, SLOT(OnSetEraserSize(int)) );

   wl = new QLabel( this );
   wl->setGeometry( 10,40,50,20 );
   wl->setText( "Size" );

   widthlabel = new QLabel( this );
   widthlabel->setGeometry( 310, 40, 30, 20 );
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",widthslider->value() );
   widthlabel->setText( widthsldrvalue );

   resize(350,70);
}

MyEraserDialog::~MyEraserDialog()
{
   delete widthslider;
   delete widthlabel;
   delete wl;
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////
// slot to set the pen width
void MyEraserDialog::OnSetEraserSize(int w)
{
   size=w;
   char widthsldrvalue[1024];
   sprintf( widthsldrvalue,"%d",w );
   widthlabel->setText( widthsldrvalue );

  // pen.setWidth( w );
}
