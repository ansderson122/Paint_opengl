#include <GL/glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>


#include "menu/menu.h"
#include "draw/shape/shape.h"
#include "draw/shape/shape.cpp"

int window_w = 400, window_h = 300;
int currentX=0 ,currentY=0 ,startX = 0,startY=0;
int isDrawing = 0;


std::vector<Line> lines; 

void display(void)
{   
    glClear(GL_COLOR_BUFFER_BIT); 

	for (std::vector<Line>::iterator it = lines.begin(); it != lines.end(); ++it){
	    (*it).draw();
	}	    
    
}

// Função que trata o redimensionamento da janela
void reshape(int w, int h)
{
    //glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, window_w, 0, window_h);
    glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y) {
    // atualiza a posição atual do mouse
    currentX = x;
    currentY = window_h - y; // inverte a posição y para corresponder à coordenada do OpenGL
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
			startX = x;
        	startY = window_h - y; 
        	isDrawing = 1;	
		}
    	
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        isDrawing = 0;
        Line new_shape(startX, startY, currentX, currentY, 0.0f, 0.0f, 0.0f);
		lines.push_back(new_shape);
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ATIVIDADE – INTRODUÇÃO AO OPENGL");
    
    createMenu();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glutMainLoop();
    return 0;
}

