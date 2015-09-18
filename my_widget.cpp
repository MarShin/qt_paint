/****************************************/
//  COMP2012 2015S PA2 -- Paint
//  File: my_widget.cpp
//  Description: the source file
//  -- MyMainWindow class implementation 
/****************************************/

#include <iostream>
#include <cmath>
using namespace std;

#include "my_widget.h"

#include <qfiledialog.h>
#include <qmessagebox.h>
#include <qinputdialog.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qpopupmenu.h>
#include <qpen.h>
#include <qrect.h>
#include <qbrush.h>
#include <qtextedit.h>
#include <qfile.h>
#include <qfiledialog.h>
#include <qstatusbar.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qapplication.h>
#include <qaccel.h>
#include <qtextstream.h>
#include <qpainter.h>
#include <qpaintdevicemetrics.h>
#include <qwhatsthis.h>
#include <qsimplerichtext.h>
#include <qcolordialog.h> 

////////////////////////////////////////////////
// Constructor and Destructor
////////////////////////////////////////////////

MyMainWindow::MyMainWindow(QWidget* parent, const char* name)
:QMainWindow(parent, name)
{
   // initialize the default background color
   bgcolor = QColor( 255, 255, 255 );

   // build the menu
   CreateMenu();

   // build the tool bar 
   drawTools = new MyToolBar( this, "tool bar" );
   drawTools->setLabel( "Tool Bar" );

   connect( drawTools, SIGNAL( OnPaint() ), 
         this, SLOT( OnDockWindowPositionChanged() ) );
   
   QPixmap pix;

   pix.load( "new_icon.bmp" );
   newButton = new QToolButton( pix, "New Image", QString::null,
                                this, SLOT( OnNewImage() ), drawTools, "new image" );

   pix.load( "open_icon.bmp" );
   openButton = new QToolButton( pix, "Open Image", QString::null,
                                this, SLOT( OnLoadImage() ), drawTools, "open image" );

   pix.load( "save_icon.bmp" );
   saveButton = new QToolButton( pix, "Save Image", QString::null,
                                this, SLOT( OnSaveImage() ), drawTools, "save image" );

   pix.load( "undo_icon.bmp" );
   undoButton = new QToolButton( pix, "Undo", QString::null,
                                this, SLOT( OnEditUndo() ), drawTools, "undo" );

   pix.load( "redo_icon.bmp" );
   redoButton = new QToolButton( pix, "Redo", QString::null,
                                this, SLOT( OnEditRedo() ), drawTools, "redo" );

   pix.load( "clearall_icon.bmp" );
   clearallButton = new QToolButton( pix, "Clear All", QString::null,
                                this, SLOT( OnEditClearAll() ), drawTools, "clear all" );

   pix.load( "resize_icon.bmp" );
   resizeButton = new QToolButton( pix, "Resize", QString::null,
                                this, SLOT( OnEditResize() ), drawTools, "resize" );

   pix.load( "pen_icon.bmp" );
   penButton = new QToolButton( pix, "Pen", QString::null,
                                this, SLOT( OnChoosePen() ), drawTools, "pen" );
  
   pix.load( "line_icon.bmp" );
   lineButton = new QToolButton( pix, "Line", QString::null,
                                this, SLOT( OnChooseLine() ), drawTools, "line" );
   
   pix.load( "eraser_icon.bmp" );
   eraserButton = new QToolButton( pix, "Eraser", QString::null,
                                this, SLOT( OnChooseEraser() ), drawTools, "eraser" );                             
   
   pix.load( "rect_icon.bmp" );
   rectButton = new QToolButton( pix, "Rectangle", QString::null,
                                this, SLOT( OnChooseRect() ), drawTools, "rectangle" );
   
   pix.load( "fcolor_icon.bmp" );
   colorButton = new QToolButton( pix, "Color", QString::null,
                                this, SLOT( OnChooseColor() ), drawTools, "color" );
   
   pix.load( "bcolor_icon.bmp" );
   bcolorButton = new QToolButton( pix, "BG color", QString::null,
                                this, SLOT( OnChooseBGColor() ), drawTools, "bg color" );
   
   
   // create the QPixmap image
   image = new QPixmap();

   // create the QPainter object
   paint = new QPainter( this );

   // create the pen dialog
   pendialog = new MyPenDialog( this, "Pen Dialog" );
   pendialog->setCaption( "Pen Dialog" );

   resize(800,600);

   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
      
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();
   
   
   // create the eraser dialog
   eraserdialog = new MyEraserDialog( this, "Eraser Dialog" );
   eraserdialog->setCaption( "Eraser Dialog" );

   // create the line dialog
   linedialog = new MyLineDialog( this, "Line Dialog" );
   linedialog->setCaption( "Line Dialog" );
   
   // create the rect dialog
   rectdialog = new MyRectDialog( this, "Rectangle Dialog" );
   rectdialog->setCaption( "Rectangle Dialog" );
     
   // initialize the undo flag to false (i.e. disable undo)
   undoflag = false;
   undo = NULL;
   redo = NULL;
}

MyMainWindow::~MyMainWindow()
{
   delete newButton;
   delete openButton;
   delete saveButton;
   delete undoButton;
   delete redoButton;
   delete clearallButton;
   delete resizeButton;
   delete rectButton;
   delete penButton;
   delete lineButton;
   delete eraserButton;
   delete colorButton;
   delete bcolorButton;
   delete drawTools;

   delete image;
   if(undo != NULL) delete undo;
   if(redo != NULL) delete redo;
   delete paint;

   delete pendialog;
   delete eraserdialog;
   delete linedialog;
   delete rectdialog;

   delete file;
   delete edit;
   delete view;
   delete help;
}

////////////////////////////////////////////////
// Create the menu
////////////////////////////////////////////////

void MyMainWindow::CreateMenu()
{
   // create the "File" popup menu
   file = new QPopupMenu( this );

   file->insertItem( "New image", this, SLOT( OnNewImage() ) );
   file->insertItem( "Load image", this, SLOT( OnLoadImage() ) );
   file->insertItem( "Save image", this, SLOT( OnSaveImage() ) );
   file->insertSeparator();
   file->insertItem( "Foregound Color", this, SLOT( OnChooseColor() ) );
   file->insertItem( "Backgound Color", this, SLOT( OnChooseBGColor() ) );
   file->insertSeparator();
   file->insertItem( "Exit", this, SLOT( OnExit() ) );
   
   menuBar()->insertItem( "File", file );

   // create the "Edit" popup menu
   edit = new QPopupMenu( this );
   edit->insertItem( "Undo", this, SLOT( OnEditUndo() ) );
   edit->insertItem( "Redo", this, SLOT( OnEditRedo() ) );
   file->insertSeparator();
   edit->insertItem( "Clear All", this, SLOT( OnEditClearAll() ) );
   file->insertSeparator();
   edit->insertItem( "Resize", this, SLOT( OnEditResize() ) );
   menuBar()->insertItem( "Edit", edit );

   view = new QPopupMenu( this );
   view->insertItem( "Tool Bar", this, SLOT( OnViewToolBar() ) );
   menuBar()->insertItem( "View", view );

   help = new QPopupMenu( this );
   help->insertItem( "About", this, SLOT( OnAbout() ) );
   menuBar()->insertItem( "Help", help );
}

////////////////////////////////////////////////
// Paint the image onto the widget 
////////////////////////////////////////////////

void MyMainWindow::paintbmp() const
{
   // close active painter
   if(paint->isActive () )
   {
      paint->end();
   }

   paint->begin( this );
   if ( ! image->isNull() ) 
   {
      paint->drawPixmap( xPos, yPos, (*image) );
   }
   paint->end();
}

////////////////////////////////////////////////
// Handle Paint Event
////////////////////////////////////////////////

void MyMainWindow::paintEvent(QPaintEvent* e)
{
   paintbmp();
}

////////////////////////////////////////////////
// Handle Callback function
////////////////////////////////////////////////

// Create a new image
void MyMainWindow::OnNewImage()
{
   bool ok;

   // get the user input of width from the input diaplog
   int width = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", 400, 0, 10000, 1,
            &ok, this );

   if ( !ok || width <= 0 ) 
      return;

   // get the user input of height from the input diaplog
   int height = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", 300, 0, 10000, 1,
            &ok, this );

   if ( !ok || height <= 0 ) 
      return;
    
   if ( image->isNull() )
   {
      delete image;   
   }

   // create an image with the input width & height
   image = new QPixmap( width, height );
   // fill it with default background
   image->fill( bgcolor );

   undoflag = false;

 //  this->erase();
   paintbmp();
}

// Load an image
void MyMainWindow::OnLoadImage()
{
   QString s = QFileDialog::getOpenFileName( "", "*.bmp", this, "", "Load image..." );
   if ( ! s.isNull() ) 
   {
      if( image->load( s ) ){
         this->erase();
         undoflag = false;
         paintbmp();
      }
   }
}

// Save the image as a bitmap
void MyMainWindow::OnSaveImage()
{
   QString s = QFileDialog::getSaveFileName( "", "*.bmp", this, "", "Save image..." );
   if (! s.isNull() )
   {
      image->save( s, "BMP" );
   }
}

// Change the foreground color
void MyMainWindow::OnChooseColor()
{
   QColor windowcolor = QColorDialog::getColor( pendialog->pen.color(), this );
   if( windowcolor.isValid() ){
      pendialog->pen.setColor( windowcolor );  
      rectdialog->pen.setColor( windowcolor ); 
      rectdialog->brush.setColor( windowcolor );
      linedialog->pen.setColor( windowcolor ); 
   }

}

// Change the background color
void MyMainWindow::OnChooseBGColor()
{
   QColor windowcolor = QColorDialog::getColor( bgcolor, this );
   if( windowcolor.isValid() ){
      bgcolor = windowcolor;
      rectdialog->backgroundColor=windowcolor;
     // rectdialog->brush.setColor( bgcolor ); will set automatically without user choosing from dialog WRONG!
   }
}

// Undo the last action
void MyMainWindow::OnEditUndo()
{
   // TODO!
   
   if(undoflag==true){
     paint->begin(image);
   paint->drawPixmap( QRect(0,0,undo->width(), undo->height()), *undo );

   paint->end();
     paintbmp();
   }
}

// Redo the last action
void MyMainWindow::OnEditRedo()
{
   // TODO!
   if(undoflag==true){
   paint->begin(image);
   paint->drawPixmap( QRect(0,0,undo->width(), undo->height()), *redo );

   paint->end();
     paintbmp();
   }
}

// Clear the drawing
void MyMainWindow::OnEditClearAll()
{
   // TODO! : DONE
   if ( image->isNull() )
   {
      delete image;   
   }
  
   // fill it with default background
   image->fill( bgcolor );

   undoflag = true;

   this->erase();
   paintbmp();
   
}

// Resize the image
void MyMainWindow::OnEditResize()
{
   // TODO!
      bool ok;

   // get the user input of width from the input diaplog
   int width = QInputDialog::getInteger( "New Image", "Enter the bitmap width:", 400, 0, 10000, 1,
            &ok, this );

   if ( !ok || width <= 0 ) 
      return;

   // get the user input of height from the input diaplog
   int height = QInputDialog::getInteger( "New Image", "Enter the bitmap height:", 300, 0, 10000, 1,
            &ok, this );

   if ( !ok || height <= 0 ) 
      return;

   QPixmap temp = *image;

   image->resize(width,height);
   image->fill( bgcolor );
   paint->begin(image);
   paint->drawPixmap( QRect(0,0,temp.width(), temp.height()), (temp) );

   paint->end();

   this->erase();
   paintbmp();
   undoflag = false;
   
}

// Show the tool bar
void MyMainWindow::OnViewToolBar()
{
   drawTools->show();
}

// Close the application
void MyMainWindow::OnExit()
{
   // qApp is a global pointer points to
   // our application object (QApplication)
   qApp->quit(); // quit this application program
}

// About Paint
void MyMainWindow::OnAbout()
{
   QMessageBox::about( this, "About", "CS2012 Spring 2015 Paint" );
}

// Activate the Pen tool
void MyMainWindow::OnChoosePen()
{
   selectedbutton = DPen;
   mouseevent = 0;
   // linedialog->linedrawing = false;
   // rectdialog->isdrawing = false;
}
  
// Activate the other drawing tools
// TODO: other OnChooseXX()
void MyMainWindow::OnChooseLine(){
    selectedbutton = DLine;
    mouseevent = 0;
}


void MyMainWindow::OnChooseEraser(){
    selectedbutton = DEraser;
    mouseevent = 0;
}


void MyMainWindow::OnChooseRect(){
   selectedbutton = Drect;
   mouseevent = 0;
}

////////////////////////////////////////////////
// Handle Mouse Event
////////////////////////////////////////////////
// Mouse press event handler
void MyMainWindow::mousePressEvent(QMouseEvent* e)
{
   // User presses the left button -- start drawing
   if ( e->button() == Qt::LeftButton )
   {
      // updating the images for undo and redo
      if( undo != NULL ) delete undo;
      undo = new QPixmap( *image );

      undoflag = true;
      if( redo != NULL ) delete redo;
      redo = NULL;

      mouseevent = 1;

      // Create a new image if necessary
      if ( image->isNull() ) 
      { 
         OnNewImage(); 
      } 
      else 
      { 
         if( paint->isActive() )
         {
            paint->end();
         }
         QPen tpen;
         QBrush tbrush;

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               // update the cursor positions
               px = e->x(); py = e->y();
               dx = e->x(); dy = e->y();
               break;
            case DLine: // drawing with the Line tool
               // TODO: 
               px = e->x();
               py = e->y();
               //in poly mode
               if(linedialog->poly){
                 if(!linedialog->firstChoosePoly){
                   paint->begin( this ); // begin painting onto the picture
                   paint->setClipRect ( xPos, yPos, image->width(), image->height() );  // clipping
                   paint->setPen( linedialog->pen );  
                   paint->drawLine(dx, dy, e->x(), e->y());
                   paint->end();
                 } else{//do nothing}
                            }
                 }
               
               break;
            case DEraser: { // drawing with the Eraser tool
               
                int size=eraserdialog->size;
                QPen pen(black, 1, Qt::SolidLine);
                QBrush brush(bgcolor);
               
               paintbmp();
               // TODO
               //set widget eraser
               paint->begin( this ); // begin painting onto the picture
               paint->setPen(pen); 
               paint->setBrush(brush);
               paint->setClipRect ( xPos, yPos, image->width(), image->height() );  // clipping
               paint->drawRect(e->x()-size/2, e->y()-size/2, size, size);
               paint->end();
               
               //set Pixmap eraser
               paint->begin( image ); // begin painting onto the picture
               pen.setColor(bgcolor);
               paint->setPen(pen); 
               paint->setBrush(brush);
               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->drawRect(e->x()-size/2-xPos, e->y()-size/2-yPos, size, size);
               paint->end();
               break;
               }

               break;
            case Drect:  // drawing witth the Rectangle tool
               // TODO
               px = e->x();
               py = e->y();
               break;
         }
      }
   }
   // User presses the right button -- show the tools' dialogs 
   else if( e->button() == Qt::RightButton )
   {
      mouseevent = 2;

      //TODO MODIFY THE DIALOG CALL
      switch( selectedbutton ){
         case DPen:
            pendialog->show();
            break;
         case DLine:
            linedialog->show();
            break;
         case DEraser:
            eraserdialog->show();
            break;
         case Drect:
            rectdialog->show();
            break;
      }
   }
}

// Mouse move event handler
void MyMainWindow::mouseMoveEvent(QMouseEvent* e)
{
   // dragging by left button click
   if( mouseevent == 1 )
   {
      if ( image->isNull() ) 
      { 
      }
      else 
      { 
         QPointArray a;

         // For any temporary pen and brush settings
         QPen tpen;
         QBrush tbrush;

         // close active painter
         if( paint->isActive() )
         {
            paint->end();
         }

     //    int mx, my;  // displacements of user moving the mouse

         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( image ); // begin painting onto the picture
               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->setPen( pendialog->pen );  // set the painter settings from the pen dialog
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos, 
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );//**
 
               // update the cursor positions
               dx = px; dy = py; 
               px = e->x(); py = e->y();

               paint->end(); // end painting onto the picture
               paintbmp();
               break;

            case DLine: { // drawing with the Line tool
               paintbmp();
               // TODO
               if(linedialog->poly){
                 px = dx;
                 py = dy;
               }
               paint->begin( this ); // begin painting onto the picture
               paint->setClipRect ( xPos, yPos, image->width(), image->height() );  // clipping
               paint->setPen( linedialog->pen );  
               paint->drawLine(px, py, e->x(), e->y());
               paint->end();
                  
               break;
            }
            
            case DEraser: { // drawing with the Eraser tool
               
                int size=eraserdialog->size;
                QPen pen(black, 1, Qt::SolidLine);
                QBrush brush(bgcolor);
               
               paintbmp();
               // TODO
               //set widget eraser
               paint->begin( this ); // begin painting onto the picture
               paint->setPen(pen); 
               paint->setBrush(brush);
               paint->setClipRect ( xPos, yPos, image->width(), image->height() );  // clipping
               paint->drawRect(e->x()-size/2, e->y()-size/2, size, size);
               paint->end();
               
               //set Pixmap eraser
               paint->begin( image ); // begin painting onto the picture
               pen.setColor(bgcolor);
               paint->setPen(pen); 
               paint->setBrush(brush);
               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->drawRect(e->x()-size/2-xPos, e->y()-size/2-yPos, size, size);
               paint->end();
               break;
               }

            case Drect:  // drawing with the Rectangle tool
            paintbmp();
               // TODO
		            
               
               // begins painting the widget
                paint->begin(this);
                paint->setPen( rectdialog->pen ); // set the pen of the painter
                paint->setBrush(rectdialog->brush); // set the brush of the painter
                paint->setClipRect(xPos, yPos, image->width(), image->height()); // enable drawing with a rectangular area only
                
                switch (rectdialog->drawtype){
                  case 0://rect
                   paint->drawRect(px, py, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                   
                  case 1://round-rect
                   paint->drawRoundRect(px, py, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                  
                  case 2://circle
                  {
                   double diagonal=sqrt(pow((double)(e->x()-px),2.0)+pow((double)(e->y()-py),2.0));
                   int negativeX, negativeY;
                   if ((e->x()-px)>0) negativeX=1;else negativeX=-1;
                   if ((e->y()-py)>0) negativeY=1;else negativeY=-1;
                   paint->drawEllipse(px, py, negativeX*diagonal, negativeY*diagonal); // draw a rectangle of size determined dynamically
                   break;
                   }
                  case 3://ellipse
                   paint->drawEllipse(px, py, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                }
                paint->end();
                break;
         }
      }
   }
}

// Mouse release event handler
void MyMainWindow::mouseReleaseEvent(QMouseEvent* e)
{
   if( e->button() == Qt::LeftButton )
   {
      
      if ( image->isNull() ) 
      { 
         OnLoadImage(); 
      }
      else 
      { 
         QPointArray a;

         // For any temporary pen and brush settings
         QPen tpen;
         QBrush tbrush;

         int mx, my;  // displacements of user moving the mouse

         // close active painter
         if( paint->isActive () )
         {
            paint->end();
         }
         switch( selectedbutton ){
            case DPen:  // drawing with the Pen tool
               paint->begin( image );  // begin painting onto picture   
               paint->setClipRect ( 0, 0, image->width(), image->height() ); // clipping
               paint->setPen( pendialog->pen ); // set the painter settings from the pen dialog
              
               // Set the array of points 
               a.setPoints( 3, dx - xPos, dy - yPos,
                               px - xPos, py - yPos,
                               e->x() - xPos, e->y() - yPos );
               paint->drawPolyline( a, 0, 3 );

               // update the cursor positions
               dx = px; dy = py;
               px = e->x(); py = e->y();

               paint->end();
               break;

            case DLine:  // drawing with the Line tool 
               // TODO 
               if(!linedialog->poly){
               paint->begin( image ); // begin painting onto the picture
               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->setPen( linedialog->pen ); 
               paint->drawLine(px-xPos, py-yPos, e->x()-xPos, e->y()-yPos);
               //store previous coord. for poly line 
               paint->end();
               }
               
               if(linedialog->poly && !linedialog->firstChoosePoly){
               paint->begin( image ); // begin painting onto the picture
               paint->setClipRect ( 0, 0, image->width(), image->height() );  // clipping
               paint->setPen( linedialog->pen ); 
               paint->drawLine(dx-xPos, dy-yPos, e->x()-xPos, e->y()-yPos);
               paint->end();
               }
               dx = e->x(); 
               dy = e->y();
               
               if(linedialog->firstChoosePoly)
                  linedialog->firstChoosePoly = false;
                  
               if(linedialog->resetPoly){
                  linedialog->firstChoosePoly = true;
                  linedialog->resetPoly = false;
               }
               
               break;

            case DEraser:  // drawing with the Eraser tool
               // TODO
            break;

            case Drect:  // drawing with the Rectangle tool
               // TODO  
                // begins painting the pixmap image
                paint->begin(image);
                paint->setPen( rectdialog->pen ); // set the pen of the painter
                paint->setBrush(rectdialog->brush); // set the brush of the painter
                paint->setClipRect(0, 0, image->width(), image->height()); // enable drawing with a rectangular area only
                switch (rectdialog->drawtype){
                  case 0://rect
                   paint->drawRect(px-xPos, py-yPos, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                   
                  case 1://round-rect
                   paint->drawRoundRect(px-xPos, py-yPos, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                  
                  case 2://circle
                  {
                   double diagonal=sqrt(pow((double)(e->x()-px),2.0)+pow((double)(e->y()-py),2.0));
                   int negativeX, negativeY;
                   if ((e->x()-px)>0) negativeX=1;else negativeX=-1;
                   if ((e->y()-py)>0) negativeY=1;else negativeY=-1;
                   paint->drawEllipse(px-xPos, py-yPos, negativeX*diagonal, negativeY*diagonal); // draw a rectangle of size determined dynamically
                   break;
                   }
                  case 3://ellipse
                   paint->drawEllipse(px-xPos, py-yPos, e->x()-px, e->y()-py); // draw a rectangle of size determined dynamically
                   break;
                }
                paint->end();
      
      break;
         }     
                 
         paintbmp();
      }
   }
   redo = new QPixmap( *image );
   mouseevent = 0; // reset the mouse event type
}

// Mouse double click event handler
void MyMainWindow::mouseDoubleClickEvent(QMouseEvent* e)
{
   mouseevent = 0;
   if( e->button() == Qt::LeftButton )
     if(linedialog->poly){
       linedialog->poly = true;
       linedialog->firstChoosePoly = true;
       linedialog->resetPoly = true;
       }
    
}

////////////////////////////////////////////////
// Other user defined slots 
////////////////////////////////////////////////

void MyMainWindow::OnDockWindowPositionChanged()
{
   QDockArea* leftDockWin = leftDock();
   QDockArea* topDockWin = topDock();
      
   xPos = ((QWidget*)leftDockWin)->frameSize().width();
   yPos = menuBar()->height() + ((QWidget*)topDockWin)->frameSize().height();

   this->erase();
   paintbmp();
}
