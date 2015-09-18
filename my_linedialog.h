/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_linedialog.h
//  Description: the header file
//  -- MyLIneDialog class definition
//     customizing the QDialog class for the Line tool
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

#ifndef _MY_LINE_DIALOG_H
#define _MY_LINE_DIALOG_H

// MyLineDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyLineDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyLineDialog(QWidget* parent = 0, const char* name = 0);
      ~MyLineDialog();
      bool poly;
      bool firstChoosePoly;
      bool resetPoly;

      /** for storing the pen settings */
      QPen pen;

   /** user defined slots */
   public slots:
      void OnSetLineStyle(int style);      
      void OnSetCapStyle(int type);
      void OnSetLineType(int type);
      void OnSetLineWidth(int w);
         
   private:
          
      // Line Style button pointers
      QButtonGroup* linestylebgroup;
      QRadioButton *rb_solidline;
      QRadioButton *rb_dashline;
      QRadioButton *rb_dotline;
      QRadioButton *rb_dashdotline;
      QRadioButton *rb_dashdotdotline;
      
      // Line Type button pointers
      QButtonGroup* linetypegroup;
      QRadioButton *rb_single;
      QRadioButton *rb_poly;
      
      // Cap Style button pointers
      QButtonGroup* capstylebgroup;
      QRadioButton *rb_flatcap;
      QRadioButton *rb_squarecap;
      QRadioButton *rb_roundcap;
      
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;
};

#endif
