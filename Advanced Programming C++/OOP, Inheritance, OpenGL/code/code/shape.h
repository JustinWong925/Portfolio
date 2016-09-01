// $Id: shape.h,v 1.7 2014-06-05 16:11:09-07 - - $
//add functions to header file

#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <iomanip>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>
using namespace std;

#include "rgbcolor.h"

//
// Shapes constitute a single-inheritance hierarchy, summarized
// here, with the superclass listed first, and subclasses indented
// under their immediate superclass.
//
// shape
//    text
//    ellipse
//       circle
//    polygon
//       rectangle
//          square
//       diamond
//       triangle
//          right_triangle
//          isosceles
//          equilateral
//

class shape;
struct vertex {GLfloat xpos; GLfloat ypos; };
using vertex_list = vector<vertex>;
using shape_ptr = shared_ptr<shape>; 

//
// Abstract base class for all shapes in this system.
//

class shape {
   friend ostream& operator<< (ostream& out, const shape&);
   private:
      shape (const shape&) = delete; // Prevent copying.
      shape& operator= (const shape&) = delete; // Prevent copying.
      shape (shape&&) = delete; // Prevent moving.
      shape& operator= (shape&&) = delete; // Prevent moving.
   protected:
      inline shape(); // Only subclass may instantiate.
   public:
      virtual ~shape() {}
      virtual void draw (const rgbcolor&, const vertex& ) const = 0;
      virtual void show (ostream&) const;
};


//
// Class for printing text.
//

class text: public shape {
   protected:
      void* /*glut_bitmap_*/font = nullptr;
      // GLUT_BITMAP_8_BY_13
      // GLUT_BITMAP_9_BY_15
      // GLUT_BITMAP_HELVETICA_10
      // GLUT_BITMAP_HELVETICA_12
      // GLUT_BITMAP_HELVETICA_18 
      // GLUT_BITMAP_TIMES_ROMAN_10
      // GLUT_BITMAP_TIMES_ROMAN_24
      string textdata;
   public:
      text (const string& font, const string& textdata);
      virtual void draw (const rgbcolor&, const vertex& ) const override;
      virtual void show (ostream&) const override;
};

//
// Classes for ellipse and circle.
//

class ellipse: public shape {
   protected:
      vertex dimension;
   public:
      ellipse (GLfloat width, GLfloat height);
	  virtual ~ellipse(){}
      virtual void draw (const rgbcolor&, const vertex& ) const override;
      virtual void show (ostream&) const override;
};

class circle: public ellipse {
   public:
      circle (GLfloat diameter);
};

//
// Class polygon.
//

class polygon: public shape {
   protected:
      const vertex_list vertices;
   public:
      polygon (const vertex_list& vertices);
	  virtual ~polygon(){}
      virtual void draw (const rgbcolor&, const vertex& ) const override;
      virtual void show (ostream&) const override;
};


//
// Classes rectangle, square, etc.
//

class rectangle: public polygon {
   private:
      GLfloat width, height;
   public:
      virtual ~rectangle(){}
      rectangle (GLfloat width, GLfloat height);
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
};

class square: public rectangle {
   private:
      GLfloat width;
   public:
      square (GLfloat width);
};

class diamond: public polygon {
   private:
      GLfloat width, height;
   public:
      virtual ~diamond(){}
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
      diamond (const GLfloat width, const GLfloat height);
};

class triangle: public polygon {
   public:
      virtual ~triangle(){}
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
	  triangle(const vertex_list& vertices);
};

class right_triangle: public triangle {
   private:
      GLfloat width;
	  GLfloat height;
   public:
      virtual ~right_triangle(){}
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
	  right_triangle(const GLfloat width, const GLfloat height);
};

class isosceles: public triangle{
   private:
      GLfloat width;
	  GLfloat height;
   public:
      virtual ~isosceles(){}
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
	  isosceles(const GLfloat width, const GLfloat height);
};

class equilateral: public triangle{
   private:
      GLfloat width;
   public:
      virtual ~equilateral(){}
	  virtual void draw(const rgbcolor&, const vertex& ) const override;
	  equilateral(const GLfloat width);
};

ostream& operator<< (ostream& out, const shape&);

#endif

