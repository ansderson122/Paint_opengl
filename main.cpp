#include <GL/glut.h>
#include<GL/freeglut.h>
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
int scrollDirection  = 0;
int isSelect = 1;

std::vector<Shape> shapes; 
std::vector<int> objSelect; 
Shape new_shape(0.0f, 0.0f, 0.0f,1);

void translations(float xr, float yr,float* cen,int index);
float* center();
void rotation(float* cen,int index);
void scale(float* cen, int index,float Xc,float Yc);

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
			rotation(cen,objSelect[i]);
		}
		startX=currentX;
		startY=currentY;
		free(cen);
	}else if(option == 7 && !isSelect){
		float *cen = center();
		for (int i = 0; i < objSelect.size(); i++) {
			scale(cen,objSelect[i],currentX,currentY);
		}
		
		free(cen);
	}

	
	
	for (std::vector<Shape>::iterator it = shapes.begin(); it != shapes.end(); ++it){
		(*it).draw();
	}		

	
	if (isSelect){
		new_shape.setNewDot(currentX,currentY);
		new_shape.draw();
	}
	


	glutSwapBuffers();
}


void reshape(int w, int h){
    glViewport(0, 0, window_w, window_h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, window_w, 0, window_h);
    glMatrixMode(GL_MODELVIEW);
}

void motion(int x, int y) {
    currentX = x;
    currentY = window_h - y; 
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
		if (selectObject(x,y,x2,y2)){
			shapes[i].setColor(0.0,0.0,1.0);
			objSelect.push_back(i);	
		}
	}
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

float* P(float x1,float y1){
	float* matriz = new float[3];
   
    matriz[0] = x1;
    matriz[1] = y1;
	matriz[2] = 1;

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

void applyProperty(float** matriz, int index){
	std::vector<float> x = shapes[index].getX();
	std::vector<float> y = shapes[index].getY();
	for(int t = 0; t < x.size();t++){
		float* mP1 = P(0,0);
		float* mP = P(x[t],y[t]);
		for (int i = 0; i < 3; ++i) {
            for (int k = 0; k < 3; ++k) {
                mP1[i] += matriz[i][k] * mP[k];
            }
    	}
    	shapes[index].setDot(mP1[0],mP1[1],t);
		free(mP);free(mP1);
	}
}

void translations(float xr, float yr,float* cen,int index){
	float** mT = T(xr - cen[0],yr - cen[1]);
	applyProperty(mT,index);
    free(mT); 
}

float** M3x3(){
	float** m = new float*[3];
	for(int i = 0; i < 3;i++){
		m[i]  = new float[3];
		for (int j = 0; j < 3;j++){
			m[i][j] = 0.0;
		}
	}
	return m;
}

float** multiply3M3x3(float **m1, float **m2,float **m3){
	float** aux = M3x3();
	float** res = M3x3();
	
	for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
        	for (int k = 0; k < 3; k++) {
            	aux[i][j] += m1[i][k] * m2[k][j];
        	}
    	}
	}
	
	
	
	for (int i = 0; i < 3; i++) {
    	for (int j = 0; j < 3; j++) {
        	for (int k = 0; k < 3; k++) {
           	 	res[i][j] += aux[i][k] * m3[k][j];
        	}
    	}
	}
	free(aux);
	return res;
}

float** R(float* center,float angle){
	float xr = center[0];
	float yr = center[1];

	float **T1 = T(-xr,-yr);
	float **T2 = T(xr,yr);
	
	float cosAngle = cos(angle);
	float sinAngle = sin(angle);
	
	float**rotationMatrix=  M3x3();
	rotationMatrix[0][0] = cosAngle;   rotationMatrix[0][1] = -sinAngle;   rotationMatrix[0][2] = 0;
	rotationMatrix[1][0] = sinAngle;   rotationMatrix[1][1] = cosAngle;	   rotationMatrix[1][2] = 0;
	rotationMatrix[2][0] = 0;          rotationMatrix[2][1] = 0;           rotationMatrix[2][2] = 1;
	

	float** transformMatrix = multiply3M3x3(T2, rotationMatrix,T1);
	
	free(T1);free(T2);free(rotationMatrix);
	return transformMatrix;
}

float angleBetweenVectors(float x1, float y1, float x2, float y2) {
   float theta = atan2(y2, x2) - atan2(y1, x1);
	if (theta < 0) {
    	theta += 2 * M_PI;
	}
    return theta;
}

void rotation(float* cen,int index){
	float angle = angleBetweenVectors(startX - cen[0], startY - cen[1] , currentX - cen[0], currentY - cen[1]) ;
	float** mR = R(cen,angle);
	applyProperty(mR,index);
    free(mR); 
}

void scale(float* cen, int index,float Xc,float Yc){
	float** mT = T(cen[0],cen[1]);
	float** mT2 = T(-cen[0],-cen[1]);
	float** mS  =  M3x3();
	
	if(scrollDirection == 1){
		mS[0][0] = 1.05f;
    	mS[1][1] = 1.05f;
	}else if(scrollDirection == -1){
		mS[0][0] = 0.95f;
    	mS[1][1] = 0.95f;
	}else{
		mS[0][0] = 0.0f;
    	mS[1][1] = 0.0f;
	}
    mS[2][2] = 1;

    float** S = multiply3M3x3(mT, mS,mT2);
   
   applyProperty(S,index);
}

void keyboard(unsigned char key, int xIn, int yIn){
	//printf("%i",key);
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
    		startX = x;
	        startY = window_h - y; 
	        if(option == 8){
	        	new_shape.setOp(option);
				new_shape.setNewDot1(startX,startY);
				shapes.push_back(new_shape);
			}else if (option > 0 && option <= 4  ){
	        	new_shape.setOp(option);
				new_shape.setNewDot1(startX,startY);
					
			}else{
				new_shape.setOp(2);	
	        	new_shape.setNewDot1(startX,startY);
			}
			
		
		}
    	
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && option > 0 && option <= 4) {
		new_shape.setNewDot(currentX,currentY);
		shapes.push_back(new_shape);
    }else if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && isSelect && option != 8 ){
		select();
	}	
}

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0 && option == 7) { // scroll para cima
        scrollDirection = 1;
        display();
    }
    else if (dir < 0 && option == 7) { // scroll para baixo
        scrollDirection = -1;
        display();
    }
    else {
        scrollDirection = 0; // sem interação
    }
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
    glutInitWindowSize(window_w, window_h);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Paint com o OPENGL");
    
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT); 
	
    createMenu();
    
	glutMotionFunc(motion);
    glutDisplayFunc(display); 
	glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMouseWheelFunc(mouseWheel);
    glutMainLoop();
    return 0;
}

