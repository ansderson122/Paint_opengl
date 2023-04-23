#include <GL/glut.h>

int option = 0;


void menuCallback(int x) {
   switch(x){
   		case 1:
   			option = 0; //selecionar
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

void createMenu() {
	
	int shapeMenu = glutCreateMenu(processShapeMenu);
	glutAddMenuEntry("Linha", 1);
	glutAddMenuEntry("Retangulo", 2);
	glutAddMenuEntry("Triangulo", 3);
	glutAddMenuEntry("Cicurlo", 4);

	
	
	
	
    int menu = glutCreateMenu(menuCallback);
    glutAddMenuEntry("Selecionar", 1);
    glutAddSubMenu("Formas Geometricas", shapeMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

