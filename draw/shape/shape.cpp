#include <GL/glut.h>
#include <vector>
#include "shape.h"
#include <math.h>
#include <stdio.h>
Shape::Shape() {	
	x.reserve(1);
	y.reserve(1);
}

Shape::Shape(float r, float g, float b,int op) :
     m_red(r), m_green(g), m_blue(b), m_op(op)  {}

Shape::~Shape() {
}

void Shape::draw() {
	glColor3f(m_red, m_green, m_blue);
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  	switch (m_op){
  		case 1:{
  			glBegin(GL_LINES);
			glVertex2i(x[0], y[0]);
			glVertex2i(x[1], y[1]);
			break;
		  }
		case 2:{
			glBegin(GL_QUADS);
			glVertex2i(x[0], y[0]);
			glVertex2i(x[1], y[1]);
			glVertex2i(x[2], y[2]);
			glVertex2i(x[3], y[3]);
			break;
		}
			
		case 3:{
			glBegin(GL_TRIANGLES);
			glVertex2i(x[0], y[0]);
			glVertex2i(x[1], y[1]);
			glVertex2i(x[2], y[2]);
			break;
		}
		

		case 4:{	
			glBegin(GL_LINE_LOOP);
			float r =sqrt(pow((x[0]-x[1]),2) + pow((y[0]-y[1]),2));
			float rad, x1 ,y1;
			for (int i = 0; i < 360; i++) {
		        rad = i * 3.14159 / 180.0;
		        x1 = x[0] + r * cos(rad);
		        y1 = y[0] + r * sin(rad);
	        	glVertex2f(x1, y1);
    		}
			break;
		}
    	 default:{
    	 	glEnable(GL_POINT_SMOOTH);
    		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		 	glPointSize(5.0);
   			glBegin(GL_POINTS);
   			glVertex2i(x[0], y[0]);
			break;
		 }
    		
   		
	}
	glEnd();
}
		  

void Shape::setNewDot(float x1, float y1){
	switch (m_op){
		case 1:
			x.resize(2);
			y.resize(2);
			
			x[1] = x1;
			y[1] = y1;
			break;
		case 2:
			x.resize(4);
			y.resize(4);
			
			x[1]=(x1);
			y[1]=(y[0]);
			
			x[2]=(x1);
			y[2]=(y1);
			
			x[3]=(x[0]);
			y[3]=(y1);
			break;
		case 3:
			x.resize(3);
			y.resize(3);
			
			int x2;
			if (x1 > x[0]){
				 x2 = x[0]+((x1 - x[0])/2);
			}else{
				 x2 = x1+((x[0] - x1)/2);
			}
			x[1]=(x1);
			y[1]=(y[0]);
			
			x[2]=(x2);
			y[2]=(y1);
			break;
		case 4:
			x.resize(2);
			y.resize(2);
			
			x[1] = x1;
			y[1] = y1;
			break;
	}
}

void Shape::setNewDot1(float x1, float y1){
	x[0]= x1;
	y[0]= y1;
}

void Shape::setOp(int x){
	m_op = x;
}

void Shape::setDot(float x1,float y1,int index){
	x[index] = x1;
	y[index] = y1;
}


void Shape::setColor(float  r, float  g,float  b){
	m_red = r;
	m_green = g;
	m_blue = b;
}

std::vector<float> Shape::getX() {
    return x;
}

std::vector<float> Shape::getY() {
    return y;
}

