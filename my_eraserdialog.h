/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_eraserdialog.h
//  Description: the header file
//  -- MyEraserDialog class definition
//     customizing the QDialog class for the Eraser tool
/****************************************/

#include <qmainwindow.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qapplication.h>
#include <qpushbutton.h>
#include <qpen.h>
#include <qslider.h> 
#include <qdialog.h>
#include <qlabel.h>
#include <qbuttongroup.h>
#include <qradiobutton.h>

#ifndef _MY_ERASER_DIALOG_H
#define _MY_ERASER_DIALOG_H

// MyEraserDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyEraserDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyEraserDialog(QWidget* parent = 0, const char* name = 0);
      ~MyEraserDialog();
      int size;

   /** user defined slots */
   public slots:
      void OnSetEraserSize(int w);
   
   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;
      
};

#endif
