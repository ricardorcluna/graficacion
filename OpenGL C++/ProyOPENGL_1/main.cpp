#include <GL/glut.h>

void dibuja(){
/* "Limpiamos" el frame buffer con
 * el color de "Clear", 
 * en este caso negro. */ 
	glClear(GL_COLOR_BUFFER_BIT);
	
	//BlOQUE DE CODIGO EN OPENGL
	glBegin(GL_POLYGON); //POLIGONO BASICO: TRAINGULO
	    /*glVertex2f(-0.5, 0.5);
	    glVertex2f(0.5, 0.5);
	    glVertex2f(0.5, -0.5);
	    glVertex2f(-0.5, -0.5);*/
	    
	    glVertex2f(1.0, 0.0);
	    glVertex2f(0.0, 1.0);
	    glVertex2f(-1.0, 0.0);
	    glVertex2f(-0.5, -1.0);
	    glVertex2f(0.5, -1.0);
	    
	glEnd();
	glFlush();
}


/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
/* Este ya incializa de forma mapeada, 
con una dimension de 2x2, 
pero por cuadrante de 1x1*/

	glutInit(&argc, argv);
	glutCreateWindow("Primer Ejemplo de OpenGL");
	glutDisplayFunc(dibuja);
	glutMainLoop();
	
	return 0;
}
