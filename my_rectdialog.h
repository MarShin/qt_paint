/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_rectdialog.h
//  Description: the header file
//  -- MyRectDialog class definition
//     customizing the QDialog class for the Rectangle tool
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

#ifndef _MY_RECT_DIALOG_H
#define _MY_RECT_DIALOG_H

// MyRectDialog: custormized QDialog 
// The QDialog class provides a dialog window for communications with user

class MyRectDialog: public QDialog {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyRectDialog(QWidget* parent = 0, const char* name = 0);
      ~MyRectDialog();

      /** for storing the pen settings */
      QPen pen;
      QBrush brush;
      
      int drawtype;
      int boundarystyle;
      int boundaryjoinstyle;
      int fillcolor;
      
      QColor backgroundColor;

   /** user defined slots */
   public slots:
      void OnSetPenWidth(int w);
      void OnSetDrawType(int type);
      void OnSetFillStyle(int type);
      void OnSetBoundaryStyle(int type);
      void OnSetBoundaryJoinStyle(int type);
      void OnSetFillColor(int type);
   
   private:
      // Slider pointer
      QSlider* widthslider;
      // Slider labels
      QLabel* wl;
      QLabel* widthlabel;
      
      // Draw Type button pointers
      QButtonGroup* drawtypegroup;
      QRadioButton *rb_rectangle;
      QRadioButton *rb_roundrectangle;
      QRadioButton *rb_circle;
      QRadioButton *rb_ellipse;
      
      // Fill Style button pointers
      QButtonGroup* fillstylegroup;
      QRadioButton *rb_solid;
      QRadioButton *rb_dense1;
      QRadioButton *rb_dense2;
      QRadioButton *rb_dense3;
      QRadioButton *rb_dense4;
      QRadioButton *rb_dense5;
      QRadioButton *rb_dense6;
      QRadioButton *rb_dense7;
      QRadioButton *rb_horizontal;
      QRadioButton *rb_vertical;
      QRadioButton *rb_cross;
      QRadioButton *rb_BDiag;
      QRadioButton *rb_FDiag;
      QRadioButton *rb_CDiag;
      QRadioButton *rb_nopattern;
            
      // Boundary Style button pointers
      QButtonGroup* boundarystylebgroup;
      QRadioButton *rb_solidline;
      QRadioButton *rb_dashline;
      QRadioButton *rb_dotline;
      QRadioButton *rb_dashdotline;
      QRadioButton *rb_dashdotdotline;
      QRadioButton *rb_noline;
      
      // Boundary Join Style button pointers
      QButtonGroup* boundary_joinstylegroup;
      QRadioButton *rb_miter;
      QRadioButton *rb_bevel;
      QRadioButton *rb_round;
      
      // Boundary Style button pointers
      QButtonGroup* fillcolorgroup;
      QRadioButton *rb_foreground;
      QRadioButton *rb_background;
      
};

#endif
