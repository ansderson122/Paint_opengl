#include <GL/glut.h>
#include "shape.h"
#include <math.h>
#include <stdio.h>
Shape::Shape() {
}

Shape::Shape(int x, int y, int w, int h, float r, float g, float b,int op) :
    m_x(x), m_y(y), m_x2(w), m_y2(h), m_red(r), m_green(g), m_blue(b), m_op(op)  {}

Shape::~Shape() {
}

void Shape::draw() {
	glColor3f(m_red, m_green, m_blue);
	glBegin(GL_LINES);
  	switch (m_op){
  		case 1:
			glVertex2i(m_x, m_y);
			glVertex2i(m_x2, m_y2);
		    break;
		case 2:
			glVertex2i(m_x, m_y);
			glVertex2i(m_x, m_y2);
			
			glVertex2i(m_x, m_y2);
			glVertex2i(m_x2, m_y2);
			
			glVertex2i(m_x2, m_y2);
			glVertex2i(m_x2, m_y);
			
			glVertex2i(m_x2, m_y);
			glVertex2i(m_x, m_y);
			break;
		case 3:
			int x;
			if (m_x2 > m_x){
				 x = m_x+((m_x2 - m_x)/2);
			}else{
				 x = m_x2+((m_x - m_x2)/2);
			}
			
			
			glVertex2i(m_x, m_y);
			glVertex2i(m_x2, m_y);
			
			glVertex2i(m_x2, m_y);
			glVertex2i(x, m_y2);
			
			glVertex2i(x, m_y2);
			glVertex2i(m_x, m_y);
			break;
		case 4:
			int r =sqrt(pow((m_x-m_x2),2) + pow((m_y-m_y2),2));
			int i = 0;
			float rad = i * 3.14159 / 180.0;
			float x1 = m_x + r * cos(rad);
		    float y1 = m_y + r * sin(rad);
			for (i = 0; i < 360; i++) {
				glVertex2f(x1, y1);
		        rad = i * 3.14159 / 180.0;
		        x1 = m_x + r * cos(rad);
		        y1 = m_y + r * sin(rad);
	        	glVertex2f(x1, y1);
    		} 
			glVertex2f(x1, y1);
			x1 = m_x + r * cos(0);
			y1 = m_y + r * sin(0);
			glVertex2f(x1, y1);
	}
	glEnd();
	glFlush();
}
		  

void Shape::setNewDot(int x, int y){
	m_x2 = x;
	m_y2 = y;
}

void Shape::setNewDot1(int x, int y){
	m_x = x;
	m_y = y;
}

void Shape::setOp(int x){
	m_op = x;
}
