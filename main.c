#include <GL/glut.h>
#include <stdio.h>
#include "menu/menu.h"

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // limpa o buffer de cor
    glClearColor(1.0, 1.0, 1.0, 1.0); // define a cor de fundo como branco
     // chama a função para desenhar a interface
    glutSwapBuffers(); // troca os buffers (double buffering)
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
    glutMainLoop();
    return 0;
}

