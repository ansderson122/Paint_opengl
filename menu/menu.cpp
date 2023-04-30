#include <GL/glut.h>
#include "menu.h"
int option = 0;


void menuCallback(int x) {
   switch(x){
   		case 1:
   			option = 0; //selecionar
   			break;
   			
   		case 2:
   			option = 5; 
   			break;
   			
   		case 3:
   			option = 6; 
   			break;
   }
  
}

void processShapeMenu(int x){
	 switch (x) {
        case 1:
            option = 1; // Linha
            break;
        case 2:
            option = 2; // Retangulo
            break;
        case 3:
            option = 3; // Triangulo
            break;
        case 4:
        	option = 4;
        	break;
    }
}

void shapeMenu(int x){
	
}

void createMenu() {
	
	int shapeMenu = glutCreateMenu(processShapeMenu);
	glutAddMenuEntry("Linha", 1);
	glutAddMenuEntry("Retangulo", 2);
	glutAddMenuEntry("Triangulo", 3);
	glutAddMenuEntry("Cicurlo", 4);

	
    int menu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Selecionar", 1);
    glutAddSubMenu("Formas Geometricas", shapeMenu);
    glutAddMenuEntry("Transladar", 2); 
	glutAddMenuEntry("Rotacionar", 3); 
	glutAddMenuEntry("Escalar", 4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

