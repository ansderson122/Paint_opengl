#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>



#include "menu/menu.h"
#include "draw/shape/shape.h"


float window_w = 800, window_h = 600;
float currentX=0 ,currentY=0 ,startX = 0,startY=0;
int isDrawing = 0;
int isSelect = 1;

std::vector<Shape> shapes; 
std::vector<int> objSelect; 
Shape new_shape(0.0f, 0.0f, 0.0f,1);

void translations(float xr, float yr,float* cen,int index);
float* center();
//void rotation(float* cen,int index);

void display(void){   
    glClear(GL_COLOR_BUFFER_BIT); 
    if(option == 5 && !isSelect){
    	float *cen = center();
		for (int i = 0; i < objSelect.size(); i++) {
			translations(currentX,currentY,cen,objSelect[i]);
		}
		free(cen);
	}else if(option == 6 && !isSelect){
		float *cen = center();
		for (int i = 0; i < objSelect.size(); i++) {
			//rotation(cen,objSelect[i]);
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
void reshape(int w, int h){
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

int selectObject(float x[2],float y[2],std::vector<float> x2,std::vector<float> y2){
	std::sort(x, x + 2); // ordem cresente 
	std::sort(y, y + 2);
	
	for(int i = 0; i < x2.size();i++){
		if( x2[i] >= x[0] && x2[i] <= x[1] &&
			y2[i] >= y[0] && y2[i] <= y[1]){
			return 1;
		}
	}
	return 0;	
}

void select(){
	float x[2];
    x[0] = startX;
    x[1] = currentX;
    	
    float y[2];
    y[0] = startY;
    y[1] = currentY;
    	
    std::vector<float> x2;
    std::vector<float> y2;
    	
    for (int i = 0; i < shapes.size();i++){
    	x2 = shapes[i].getX();
    	y2 = shapes[i].getY();
			//printf("Q [%i,%i] [%i,%i] \n O[%i,%i]  [%i,%i] \n",x[0],y[0],x[1],y[1],x2[0],y2[0],x2[1],y2[1]);
		if (selectObject(x,y,x2,y2)){
			shapes[i].setColor(0.0,0.0,1.0);
			objSelect.push_back(i);	
		}
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

float** T(float xr, float yr) {
    // Alocar a matriz
    float** matriz = new float*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new float[3];
    }

    // Definir os valores da matriz
    matriz[0][0] = 1;    matriz[0][1] = 0;    matriz[0][2] = xr;
	matriz[1][0] = 0;    matriz[1][1] = 1;    matriz[1][2] = yr;
    matriz[2][0] = 0;    matriz[2][1] = 0;    matriz[2][2] = 1;

    return matriz;
}

float** P(float x1,float y1){
	float** matriz = new float*[3];
    for (int i = 0; i < 3; i++) {
        matriz[i] = new float[1];
    }

    matriz[0][0] = x1;
    matriz[1][0] = y1;
	matriz[2][0] = 1;

    return matriz;
}

float* center(){
	std::vector<float> x;
	std::vector<float> y;
	float x_maior =0 ,y_maior=0,x_menor,y_menor;
	x_menor = shapes[objSelect[0]].getX()[0];
	y_menor = shapes[objSelect[0]].getY()[0];
	
	for (int i = 0; i < objSelect.size(); i++) {
		x = shapes[objSelect[i]].getX();
		y = shapes[objSelect[i]].getY();
		
		for(int j = 0; j < x.size();j++){
			if (x_maior < x[j]){
				x_maior = x[j];
			}		
			
			if (y_maior < y[j]){
				y_maior = y[j];
			}
			
			if (x_menor > x[j]){
				x_menor = x[j];
			}
			
			if (y_menor > y[j]){
				y_menor = y[j];
			}
		}
		
	}
	
	float* center = new float[2];
	
	center[0] = (x_maior + x_menor)/2;
	center[1] = (y_maior + y_menor)/2;
	
	return center;
}

void translations(float xr, float yr,float* cen,int index){
	std::vector<float> x = shapes[index].getX();
	std::vector<float> y = shapes[index].getY();
	float x1,y1;

	x1 = xr - cen[0];
	y1 = yr - cen[1];
	float** mT = T(x1,y1);
	
	
	
	for(int t = 0; t < x.size();t++){
		float** mP1 = P(0,0);
		float** mP = P(x[t],y[t]);
		for (int i = 0; i < 3; ++i) {
        	for (int j = 0; j < 2; ++j) {
            	for (int k = 0; k < 3; ++k) {
                	mP1[i][j] += mT[i][k] * mP[k][j];
            	}
        	}
    	}
    	shapes[index].setDot(mP1[0][0],mP1[1][0],t);
		free(mP);free(mP1);
	}
    free(mT); 
}

float** R(float* center,float angle){
	float xr = center[0];
	float yr = center[1];

	float **T1 = T(-xr,-yr);
	float **T2 = T(xr,yr);
	
	float radians = angle * M_PI / 180;
	float cosAngle = cos(radians);
	float sinAngle = sin(radians);
	
	float rotationMatrix[3][3] = {
    {cosAngle, -sinAngle, 0},
    {sinAngle, cosAngle, 0},
    {0, 0, 1}
	};
		
	float** transformMatrix = new float*[3];
	for (int i = 0; i < 3;i++){
		transformMatrix[i] = new float[3];
		for (int j = 0; j < 3;j++){
			transformMatrix[i][j] = 0.0;
		}
	}
	
	float** aux = new float*[3];
	for (int i = 0; i < 3;i++){
		aux[i] = new float[3];
		for (int j = 0; j < 3;j++){
			aux[i][j] = 0.0;
		}
	}

	for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
        	for (int k = 0; k < 3; k++) {
            	aux[i][j] += T2[i][k] * rotationMatrix[k][j];
        	}
    	}
	}
	
	for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
        	for (int k = 0; k < 3; k++) {
           	 	transformMatrix[i][j] += aux[i][k] * T1[k][j];
        	}
    	}
	}

	return transformMatrix;
}

/*
void rotation(float* cen,int index){
	
	float** mR = R(cen,30);
	
	
	float* x = shapes[index].getX();
	float* y = shapes[index].getY();
	float** mP = P(x[0],y[0],x[1],y[1]);
	
	float** mP1 = new float*[3];
    for (int i = 0; i < 3; i++) {
        mP1[i] = new float[2];
    }
	
	for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                mP1[i][j] += mR[i][k] * mP[k][j];
            }
        }
    }
    printf("Center %f %f\n",cen[0],cen[1]);
    printf("mP1 %f %f    %f %f \n",mP1[0][0],mP1[1][0],mP1[0][1],mP1[1][1]);
    shapes[index].setNewDot1(mP1[0][0],mP1[1][0]);
    shapes[index].setNewDot(mP1[0][1],mP1[1][1]);
    
    free(x); free(y); free(mR); free(mP); free(mP1);
}*/

void keyboard(unsigned char key, int xIn, int yIn){
	printf("%i",key);
	switch (key){
		case 127:
			del();
			display();
			break;
			
		case 13:
			if(isSelect){
				isSelect = 0;
			}else{
				delSelect();
				isSelect = 1;
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
	        	new_shape.setOp(option);
				new_shape.setNewDot1(startX,startY);
					
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




int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("ATIVIDADE � INTRODU��O AO OPENGL");
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	
	/*
	new_shape.setNewDot(300,300);
	new_shape.setNewDot1(100,100);
	new_shape.setOp(2);
	shapes.push_back(new_shape);
	objSelect.push_back(0);	
	float* cen = center();
	
	rotation(cen,0);
	*/
    createMenu();
    glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}

