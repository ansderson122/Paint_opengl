#ifndef SHAPE_H
#define SHAPE_H


class Shape{
	public:
		Shape();
		Shape(int , int , int , int , float , float , float , int );
		~Shape();
		void draw();
		void setNewDot(int,int);
		void setNewDot1(int,int);
		void setOp(int);
	
	private:
		int m_x, m_y, m_x2, m_y2, m_op;
    	float m_red, m_green, m_blue;
};

#include "shape.cpp"
#endif
