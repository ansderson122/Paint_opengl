#include <GL/glut.h>

int selected = 0;


void menuCallback(int option) {
    switch (option) {
        case 0:
            selected = 0; // vermelho
            break;
        case 1:
            selected = 1; // verde
            break;
        case 2:
            selected = 2; // azul
            break;
    }
}

void processShapeMenu(int option){
	
}

void createMenu() {
	
	int shapeMenu = glutCreateMenu(processShapeMenu);
	glutAddMenuEntry("Lilha", 1);
	glutAddMenuEntry("Retagulo", 2);
	glutAddMenuEntry("Cicurlo", 4);

	
	
	
	
    int menu = glutCreateMenu(menuCallback);
    glutAddSubMenu("Formas Geometricas", shapeMenu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

