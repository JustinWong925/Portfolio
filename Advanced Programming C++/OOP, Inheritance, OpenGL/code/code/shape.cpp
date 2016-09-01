// $Id: shape.cpp,v 1.7 2014-05-08 18:32:56-07 - - $
//ctors for shapes here


#include <typeinfo>
#include <unordered_map>
#include <cmath>
using namespace std;

#include "shape.h"
#include "util.h"
#include "graphics.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}

shape::shape() {
   DEBUGF ('c', this);
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
   DEBUGF ('c', this);
}
*/

text::text (const string& f, const string& textdata):
      font(fontcode[f]), textdata(textdata) {
   DEBUGF ('c', this);
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices): vertices(vertices) {
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat width, GLfloat height):
            polygon({}), width(width), height(height) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

square::square (GLfloat width): rectangle (width, width), width(width) {
   DEBUGF ('c', this);
}

diamond::diamond (GLfloat width, GLfloat h):
			polygon({}), width(width), height(h) { 
	DEBUGF( 'c', this << "(" << width << "," << height << ")");
}

triangle::triangle(const vertex_list& vertices):polygon(vertices){}

right_triangle::right_triangle(const GLfloat width, const GLfloat height):
                   triangle({}), width(width), height(height){}
				   
isosceles::isosceles(const GLfloat width, const GLfloat height):triangle({}),
                   width(width), height(height){}
				   
equilateral::equilateral(const GLfloat width):triangle({}),
             width(width){}
			 

void text::draw (const rgbcolor& color, const vertex& center ) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv(color.ubvec);
   GLfloat width = glutBitmapLength (font, (GLubyte*) textdata.c_str());
   GLfloat height = glutBitmapHeight (font);
   GLfloat xpos = center.xpos - (width / 2.0);
   GLfloat ypos = center.ypos - (height / 4.0);
   glRasterPos2f(xpos,ypos);
   for (auto ch: textdata) glutBitmapCharacter (font, ch);
}

void ellipse::draw (const rgbcolor& color, const vertex& center ) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   const GLfloat delta = 2*M_PI / 32.0;
   glColor3ubv(color.ubvec);
   glBegin(GL_LINE_LOOP);
   for(GLfloat theta = 0; theta < (2*M_PI); theta += delta){
      GLfloat xpos = (dimension.xpos / 2.0) * cos(theta) + center.xpos;
	  GLfloat ypos = (dimension.ypos / 2.0) * sin(theta) + center.ypos;
	  glVertex2f(xpos, ypos);
   }
   glEnd();
}

void polygon::draw (const rgbcolor& color, const vertex& center ) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv(color.ubvec);
   GLfloat xsum, ysum, xavg, yavg = 0;
   GLfloat count = vertices.size();
   for(auto i = vertices.begin(); i != vertices.end(); ++i){
      xsum += i->xpos;
	  ysum += i->ypos;
   }
   xavg = xsum / count;
   yavg = ysum / count;
   glBegin(GL_LINE_LOOP);
   for(auto i = vertices.begin(); i != vertices.end(); ++i) {
      glVertex2f(i->xpos-xavg+center.xpos, i->ypos-yavg+center.ypos);
   }
   glEnd();
}

void triangle::draw(const rgbcolor& color, const vertex& center) const{
   polygon::draw(color, center);
}

void rectangle::draw(const rgbcolor& color, const vertex& center ) const{
   glBegin(GL_LINE_LOOP);
   glColor3ubv(color.ubvec);
   GLfloat x0 = center.xpos - (width/2);
   GLfloat y0 = center.ypos + (height /2);
   GLfloat x1 = center.xpos + (width / 2);
   GLfloat y1 = center.ypos + (height / 2);
   GLfloat x2 = center.xpos + (width / 2);
   GLfloat y2 = center.ypos - (height / 2);
   GLfloat x3 = center.xpos - (width / 2);
   GLfloat y3 = center.ypos - (height / 2);
   glVertex2f(x0,y0);
   glVertex2f(x1,y1);
   glVertex2f(x2,y2);
   glVertex2f(x3,y3);
   glEnd();
}

void diamond::draw(const rgbcolor& color, const vertex& center ) const{

   glColor3ubv(color.ubvec);

   GLfloat topx = center.xpos;
   GLfloat topy = center.ypos + (height / 2);
   GLfloat botx = center.xpos;
   GLfloat boty = center.ypos - (height / 2);
   GLfloat lefx = center.xpos - (width / 2);
   GLfloat lefy = center.ypos;
   GLfloat ritx = center.xpos + (width / 2);
   GLfloat rity = center.ypos;

   glBegin(GL_LINE_LOOP);
   glVertex2f(topx, topy);
   glVertex2f(lefx, lefy);
   glVertex2f(botx, boty);
   glVertex2f(ritx, rity);
   glEnd();
}

void right_triangle::
                 draw(const rgbcolor& color, const vertex& center)const{
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv(color.ubvec);

   GLfloat x0 = center.xpos - ((2.0/3.0)*(width));
   GLfloat y0 = center.ypos - ((1.0/3.0)*(height));
   GLfloat x1 = center.xpos + ((1.0/3.0)*(width));
   GLfloat y1 = center.ypos + ((2.0/3.0)*(height));
   GLfloat x2 = center.xpos + ((1.0/3.0)*(width));
   GLfloat y2 = center.ypos - ((1.0/3.0)*(height));
 
   glBegin(GL_LINE_LOOP);
   glEnable(GL_LINE_SMOOTH);
   glVertex2f(x0,y0);
   glVertex2f(x1,y1);
   glVertex2f(x2,y2);
   glEnd();
}

void isosceles::draw(const rgbcolor& color, const vertex& center ) const{
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv(color.ubvec);

   GLfloat x0 = center.xpos - (width/2);
   GLfloat y0 = center.ypos - (height/2);
   GLfloat x1 = center.xpos;
   GLfloat y1 = center.ypos + (height/2);
   GLfloat x2 = center.xpos + (width/2);
   GLfloat y2 = center.ypos - (height/2);\

   glBegin(GL_LINE_LOOP);
   glVertex2f(x0,y0);
   glVertex2f(x1,y1);
   glVertex2f(x2,y2);
   glEnd();
}

void equilateral::
                 draw(const rgbcolor& color, const vertex& center)const{
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   glColor3ubv(color.ubvec);
   GLfloat x0 = center.xpos - (width/2);
   GLfloat y0 = center.ypos - (width/2);
   GLfloat x1 = center.xpos;
   GLfloat y1 = center.ypos + (width/2);
   GLfloat x2 = center.xpos + (width/2);
   GLfloat y2 = center.ypos - (width/2);

   glBegin(GL_LINE_LOOP);
   glVertex2f(x0,y0);
   glVertex2f(x1,y1);
   glVertex2f(x2,y2);
   glEnd();
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << /*glut_bitmap_*/font << "(" << fontname[/*glut_bitmap_*/font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

