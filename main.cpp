#include <GL/glut.h>
#include <stdio.h>

#include <algorithm>
#include <iostream>
#include <vector>


#include "menu/menu.h"
#include "draw/shape/shape.h"


int window_w = 800, window_h = 600;
int currentX=0 ,currentY=0 ,startX = 0,startY=0;
int isDrawing = 0;


std::vector<Shape> shapes; 
std::vector<int> objSelect; 
Shape new_shape(startX, startY, currentX, currentY, 0.0f, 0.0f, 0.0f,1);

void display(void)
{   
	glViewport(0, 0, window_w, window_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, window_w, 0, window_h);
    glMatrixMode(GL_MODELVIEW);


	glClear(GL_COLOR_BUFFER_BIT); 
	for (std::vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it){
		(*it).draw();
	}		

		//printf("o %i,%i \n",currentX,currentY);
		new_shape.setNewDot(currentX,currentY);
		new_shape.draw();


	glutSwapBuffers();
}

// Fun��o que trata o redimensionamento da janela
void reshape(int w, int h)
{
    glViewport(0, 0, window_w, window_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, window_w, 0, window_h);
    glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y) {
    // atualiza a posi��o atual do mouse
    currentX = x;
    currentY = window_h - y; // inverte a posi��o y para corresponder � coordenada do OpenGL
    glutPostRedisplay();
    
   
}

int selectObject(int x[2],int y[2],int x2[2],int y2[2]){
	
	if( x2[0] >= x[0] && x2[0] <= x[1] &&
		y2[0] >= y[0] && y2[0] <= y[1]
	){
			return 1;
	}
	
	if( x2[1] >= x[0] && x2[1] <= x[1] &&
		y2[1] >= y[0] && y2[0] <= y[1]
	){
			return 1;
	}

	return 0;
	
}

void select(){
	int x[2];
    x[0] = startX;
    x[1] = currentX;
    	
    int y[2];
    y[0] = startY;
    y[1] = currentY;
    	
    int* x2;
    int* y2;
    	
    for (int i = 0; i < shapes.size();i++){
    	x2 = shapes[i].getX();
    	y2 = shapes[i].getY();
			//printf("Q [%i,%i] [%i,%i] \n O[%i,%i]  [%i,%i] \n",x[0],y[0],x[1],y[1],x2[0],y2[0],x2[1],y2[1]);
		if (selectObject(x,y,x2,y2)){
			shapes[i].setColor(0.0,0.0,1.0);
			objSelect.push_back(i);	
		}
		free(x2);
		free(y2);
	}
	//printf("tamanho %i \n",objSelect.size());
	new_shape.setNewDot1(0,0);
	currentY=0;
	currentX=0;
}

void del() {
    std::sort(objSelect.begin(), objSelect.end(), std::greater<int>()); // ordem decrescente 
    for (int i = 0; i < objSelect.size(); i++) {
        shapes.erase(shapes.begin() + objSelect[i]);
    }
    objSelect.clear();
}


void keyboard(unsigned char key, int xIn, int yIn){
	//printf("%i",key);
	switch (key){
		case 127:
			del();
			display();
			break;
	}
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { 
	    	if (option > 0 && option <= 4){
	    		startX = x;
	        	startY = window_h - y; 
	        	isDrawing = 0;
				new_shape.setNewDot1(startX,startY);
				new_shape.setOp(option);	
			}else{
				startX = x;
	        	startY = window_h - y; 
	        	
	        	new_shape.setNewDot1(startX,startY);
				new_shape.setOp(2);	
			}
		}
    	
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && option > 0 && option <= 4) {
		isDrawing = 1;
		new_shape.setNewDot(currentX,currentY);
		shapes.push_back(new_shape);
    }else{
		select();
	}
}




int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ATIVIDADE � INTRODU��O AO OPENGL");
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	
    createMenu();
    glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}

