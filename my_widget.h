/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_widget.h
//  Description: the header file 
//  -- MyMainWindow class definition 
/****************************************/

#include <qmainwindow.h>
#include <qapplication.h>
#include <qmessagebox.h>
#include <qpopupmenu.h>
#include <qmenubar.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qpen.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qiconset.h>

#include "my_pendialog.h"
// TODO: include header of other dialogs here
#include "my_linedialog.h"        
#include "my_eraserdialog.h"
#include "my_rectdialog.h"

#include "my_toolbar.h"

#ifndef __DRAW_MODE__
#define __DRAW_MODE__

enum DrawMode
{
   DPen,
   DLine,
   DEraser,
   Drect
}; 

#endif

#ifndef _MY_WIDGET_H
#define _MY_WIDGET_H

// MyMainWindow: custormized QMainWindow widget
// The QMainWindow class provides a main application window, 
// with a menu bar, dock windows (e.g. for toolbars), and a status bar 

class MyMainWindow: public QMainWindow {
   // All classes that contain signals or slots
   // must mention Q_OBJECT in their declaration.
   Q_OBJECT

   public:
      /** constructor and destructor */
      MyMainWindow(QWidget* parent = 0, const char* name = 0);
      ~MyMainWindow();

      /** mouse event handler */
      void mousePressEvent (QMouseEvent *);
      void mouseMoveEvent (QMouseEvent *);
      void mouseReleaseEvent (QMouseEvent *);
      void mouseDoubleClickEvent(QMouseEvent *);
   
      /** paint handler */
      void paintEvent(QPaintEvent *);

   /** user defined slots */
   public slots:
      /** Menu bar slots */
      void OnNewImage();
      void OnLoadImage();
      void OnSaveImage();
      void OnChooseColor();
      void OnChooseBGColor();
      void OnExit();
      void OnEditUndo();
      void OnEditRedo();
      void OnEditResize();
      void OnEditClearAll();
      void OnViewToolBar();
      void OnAbout();

      void OnDockWindowPositionChanged();

      /** Tool bar slots */
      void OnChoosePen();
      // TODO: add other slots for tool bar here : DONE header
      void OnChooseLine();
      void OnChooseEraser();
      void OnChooseRect();

   private:
      /** Utility functions */
      // build the menu
      void CreateMenu();

      // copy the image to the widget
      void paintbmp() const;

      /** Popup menu pointers in the menu bar (pull-down menu or popup menu) */
      QPopupMenu* file;
      QPopupMenu* edit;
      QPopupMenu* view;
      QPopupMenu* help;

      /** Image pointer */
      QPixmap* undo;  // the image before the last action 
      QPixmap* redo;  // the image with the last action 
      QPixmap* image;  // the current image
      QPainter* paint;  // the painter for drawing
  
      /** Dialog pointers */
      MyPenDialog* pendialog;  // the pen dialog for the pen tool
      // TODO: define the other dialogs for tools including line, eraser and rectangles
      MyLineDialog* linedialog; 
      MyEraserDialog* eraserdialog;
      MyRectDialog* rectdialog;

      int mouseevent;  // 0 for none, 1 for left button click, or 2 for right button click 

      /** Tool bar related */
      int selectedbutton;
      MyToolBar* drawTools;

      QToolButton* newButton;
      QToolButton* openButton;
      QToolButton* saveButton;
      QToolButton* undoButton;
      QToolButton* redoButton;
      QToolButton* clearallButton;
      QToolButton* resizeButton;
      QToolButton* penButton;
      QToolButton* lineButton;
      QToolButton* eraserButton;
      QToolButton* rectButton;
      QToolButton* colorButton;
      QToolButton* bcolorButton;

      /** Storing the background color setting */
      QColor bgcolor;

      /** Storing positions of cursors for drawing */
      int px, py;
      int dx, dy;

      /** Storing margin sizes of the windown (with or without tool, menu bars)  */ 
      int xPos, yPos;  
         // xPos: the width between the left edge of painting area and the left edge of the window 
         // yPos: the height between the top edge of painting area and the top edge of the window

      /** flag variable for undo */
      bool undoflag;
   
};

#endif
