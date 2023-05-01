#ifndef SHAPE_H
#define SHAPE_H
#include <vector>

class Shape{
	public:
		Shape();
		Shape( float , float , float , int );
		~Shape();
		void draw();
		void setNewDot(float,float);
		void setNewDot1(float,float);
		void setOp(int);
		void setColor(float  r, float  g,float  b);
		std::vector<float> getX();
		std::vector<float> getY();
		void setDot(float,float,int);
	
	private:
		int m_op;
		float m_x, m_y, m_x2, m_y2;
    	float m_red, m_green, m_blue;
    	
    	std::vector<float> x; 
    	std::vector<float> y; 
};

#include "shape.cpp"
#endif
