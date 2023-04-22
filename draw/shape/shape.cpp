#include <GL/glut.h>
#include "shape.h"
#include <stdio.h>
Line::Line() {
}

Line::Line(int x, int y, int w, int h, float r, float g, float b) :
    m_x(x), m_y(y), m_width(w), m_height(h), m_red(r), m_green(g), m_blue(b) {}

Line::~Line() {
}

void Line::draw() {
  
        glColor3f(m_red, m_green, m_blue);
        glBegin(GL_LINES);
	        glVertex2i(m_x, m_y);
	        glVertex2i(m_width, m_height);
        glEnd();
        glFlush();
}

void Line::setNewDot(int x, int y){
	m_width = x;
	m_height = y;
}

void Line::setNewDot1(int x, int y){
	m_x = x;
	m_y = y;
}


