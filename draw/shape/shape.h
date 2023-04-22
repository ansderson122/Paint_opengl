#ifndef SHAPE_H
#define SHAPE_H


class Line{
	public:
		Line();
		Line(int , int , int , int , float , float , float );
		~Line();
		void draw();
		void setNewDot(int,int);
		void setNewDot1(int,int);
	
	private:
		int m_x, m_y, m_width, m_height;
    	float m_red, m_green, m_blue;
};
#endif
