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
int isSelect = 1;

std::vector<Shape> shapes; 
std::vector<int> objSelect; 
Shape new_shape(startX, startY, currentX, currentY, 0.0f, 0.0f, 0.0f,1);

void translations(int xr, int yr,int* cen,int index);
int* center();

void display(void)
{   
    glClear(GL_COLOR_BUFFER_BIT); 
    if(option == 5 && !isSelect){
    	int *cen = center();
		for (int i = 0; i < objSelect.size(); i++) {
			translations(currentX,currentY,cen,objSelect[i]);
		}
		free(cen);
	}

	
	
	for (std::vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it){
		(*it).draw();
	}		

		//printf("o %i,%i \n",currentX,currentY);
		if (isSelect){
			new_shape.setNewDot(currentX,currentY);
			new_shape.draw();
		}
	


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

void delSelect(){
	for(int i = 0; i < shapes.size();i++ ){
		shapes[i].setColor(0.0,0.0,0.0);
	}
	objSelect.clear();
	display();
}

void del() {
    std::sort(objSelect.begin(), objSelect.end(), std::greater<int>()); // ordem decrescente 
    for (int i = 0; i < objSelect.size(); i++) {
        shapes.erase(shapes.begin() + objSelect[i]);
    }
    objSelect.clear();
}

int** T(int xr, int yr) {
    // Alocar a matriz
    int** matriz = new int*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new int[3];
    }

    // Definir os valores da matriz
    matriz[0][0] = 1;
    matriz[0][1] = 0;
    matriz[0][2] = xr;
    matriz[1][0] = 0;
    matriz[1][1] = 1;
    matriz[1][2] = yr;
    matriz[2][0] = 0;
    matriz[2][1] = 0;
    matriz[2][2] = 1;

    return matriz;
}

int** P(int x1,int y1, int x2,int y2){
	int** matriz = new int*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new int[2];
    }
    
    matriz[0][0] = x1;
    matriz[1][0] = y1;
	matriz[2][0] = 1;
	
	matriz[0][1] = x2;   
    matriz[1][1] = y2;
    matriz[2][1] = 1;
    
    return matriz;
}

int* center(){
	int* x;
	int* y;
	int x_maior =0 ,y_maior=0,x_menor,y_menor;
	x_menor = shapes[objSelect[0]].getX()[0];
	y_menor = shapes[objSelect[0]].getY()[0];
	
	for (int i = 0; i < objSelect.size(); i++) {
		x = shapes[objSelect[i]].getX();
		y = shapes[objSelect[i]].getY();
		
		if (x_maior < x[0]){
			x_maior = x[0];
		}
		if (x_maior < x[1]){
			x_maior = x[1];
		}
		
		if (y_maior < y[0]){
			y_maior = y[0];
		}
		if (y_maior < y[1]){
			y_maior = y[1];
		}
		
		if (x_menor > x[0]){
			x_menor = x[0];
		}
		if (x_menor > x[1]){
			x_menor = x[1];
		}
		
		if (y_menor > y[0]){
			y_menor = y[0];
		}
		if (y_menor > y[1]){
			y_menor = y[1];
		}
		
		free(x); free(y);
	}
	
	int* center = new int[2];
	center[0] = (x_maior + x_menor)/2;
	center[1] = (y_maior + y_menor)/2;
	
	return center;
}

void translations(int xr, int yr,int* cen,int index){
	int* x = shapes[index].getX();
	int* y = shapes[index].getY();
	int x1,y1;

	x1 = xr - cen[0];
	y1 = yr - cen[1];
	int** mP = P(x[0],y[0],x[1],y[1]);
	int** mP1 = P(0,0,0,0);
	int** mT = T(x1,y1);
	for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                mP1[i][j] += mT[i][k] * mP[k][j];
            }
        }
    }
        
    shapes[index].setNewDot1(mP1[0][0],mP1[1][0]);
    shapes[index].setNewDot(mP1[0][1],mP1[1][1]);
    
    free(x); free(y); free(mT); free(mP); free(mP1);
}


void keyboard(unsigned char key, int xIn, int yIn){
	printf("%i",key);
	switch (key){
		case 127:
			del();
			display();
			break;
			
		case 13:
			if(option == 5){
				isSelect = 0;
			}
			break;
		case 27:
			delSelect();
			isSelect = 1;
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
    }else if(isSelect){
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

