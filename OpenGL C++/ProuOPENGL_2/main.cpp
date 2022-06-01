#include <GL/glut.h>

#define ancho 400

const int alto = 400; 

#define profundidad 300

void dibuja(); //Prototipo para avisar al compilador que
               // despues de main esta su implementacion



/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	
/* Este ya incializa de forma mapeada, 
con una dimension de 2x2, 
pero por cuadrante de 1x1*/

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_SINGLE ); // | Operador a nivel de bit  - // || Operador Logico
	
/* Definimos una ventana de medidas ANCHO x ALTO
 * como ventana de visualizacion */
	glutInitWindowSize (ancho, alto);
	
	glutInitWindowPosition (100, 100);
	glutInitWindowSize (ancho, alto);
	glutCreateWindow("Sistema Cartesiano en Opengl");
	
	//Proyeccion Ortografica
	glOrtho(-(ancho/2), ancho/2, -(alto/2), alto/2, -profundidad, profundidad);
	
	glClearColor(1,1,1,0); //Color para el fondo de la plano, Los colores van de 0-1
	
	glutDisplayFunc(dibuja);
	
	glutMainLoop();

	return 0;
}

void dibuja()
{ 
/* "Limpiamos" el frame buffer con
 * el color de "Clear", 
 * en este caso negro. */ 
	glClear(GL_COLOR_BUFFER_BIT);
	
	//DIBUJAR EJE CARTESIANO
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES); 

		glVertex3f(-ancho/2, 0.0, 0.0);

		glVertex3f(ancho/2, 1.0, 0.0);

		glVertex3f(0.0, alto/2, 0.0);

		glVertex3f(0.0, -alto/2, 0.0);
		
	glEnd();
	
	//DIBUJA EL TRIANGULO
	glColor3f(1,0,0);
	glBegin(GL_POLYGON); 
	    glColor3f(0.0, 0.5, 0.5);
		glVertex3f(0.0, 100.0, 0.0);
		
		glColor3f(0.0, 0.3, 0.4);
		glVertex3f(150.0, -150.0, 0.0);
		
		glColor3f(0.0, 0.1, 0.2);
		glVertex3f(-150.0, -150.0, 0.0);
		
	glEnd();
	
	glFlush();
} 
