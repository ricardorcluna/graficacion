#include <GL/glut.h>
#define ancho 500
const int alto = 500;
#define profundidad 400

void dibuja();
void ejes();
void tecladoNormal(unsigned char tecla, int x, int y);
void tecladoEspecial(int tecla, int x, int y);
void texto(int x, int y, char *palabra);

int posx=0, posy=0; //  Tx, Ty
int angulo=35; // Angulo
float esc=1;  // Escape
unsigned int figura=1;
float colorr=1, colorg=0, colorb=0; // RGB

int main(int argc, char** argv) {
glutInit(&argc, argv); 
glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
glutInitWindowPosition(100, 0);
glutInitWindowSize(ancho, alto);
glutCreateWindow("Figuras GLUT");
glOrtho(-(ancho/2), (ancho/2), -(alto/2), (alto/2), -profundidad, profundidad);
glClearColor(1, 1, 1, 0); // Limpiar con el color Blanco
glutDisplayFunc(dibuja); // Usa la funcion dibuja, esta no necesita parentesis
glutKeyboardFunc(tecladoNormal);
glutSpecialFunc(tecladoEspecial); // Ciclo infinito hasta que el usuario decida terminarlo
glutMainLoop();

return 0;
}

void dibuja() {
glClear(GL_COLOR_BUFFER_BIT);
ejes();
glPushMatrix(); // Pila de Matrices, y mete los elementos en la pila que se van a utilizar

   glScalef(esc, esc, esc);
   glPointSize(4.0);
   glTranslatef(posx, posy, 0); 
   glRotatef(angulo, 1, 1, 1);
   glRotatef(45, 1, 1, 1);
    
   glColor3f(colorr, colorg, colorb);   
   switch(figura) {  // Figuras Alambricas
      case 1: glutWireTorus(20, 80, 18, 18);break;
      case 2: glutWireSphere(100, 18, 18);break;
      case 3: glutWireCone(50, 200, 18, 18);break;  // Cono
      case 4: glutWireCube(100);break; // Cubo
      case 5: glutWireTeapot(100); break;
      case 6: glutWireOctahedron(); break;
      case 7: glutWireIcosahedron(); break;
   }
glPopMatrix();
texto(-ancho/2+10,alto/2-20,"[F1: Toroide] [F2: Esfera] [F3: Cono] [F4: Cubo] [F5: TeaPot] [F6: Octa] [F7: Ico]");
glutSwapBuffers();
}

void ejes() {
glColor3f(0.9, 0.9, 0.9);
glBegin(GL_LINES);
   glVertex3f(-ancho/2, 0, 0);
   glVertex3f(ancho/2, 0, 0);
   glVertex3f(0, alto/2, 0);
   glVertex3f(0, -alto/2, 0);
glEnd();
}

void tecladoNormal(unsigned char tecla, int x, int y) {
    switch(tecla) { //Agregar Esclacion
	    case 's':
		case 'S':
		case 27: exit(0);break; // 27 = esc
		case 'g': angulo--;break;                // sentido -
		case 'G': /*angulo++;*/ for(int i = 0; i < 100; i++){angulo++;}break; // 'G' rotacion
	}
	glutPostRedisplay();
}

void tecladoEspecial(int tecla, int x, int y) {
    switch(tecla) {
	    case GLUT_KEY_UP : posy++;break;
		case GLUT_KEY_DOWN : posy--;break;
		case GLUT_KEY_RIGHT : posx++;break;
		case GLUT_KEY_LEFT : posx--;break;
		case GLUT_KEY_PAGE_UP : esc=esc*1.01;break;
		case GLUT_KEY_PAGE_DOWN : esc=esc*0.99;break;
		case GLUT_KEY_F1 : figura=1;colorr=1,colorg=0;colorb=0;break;
		case GLUT_KEY_F2 : figura=2;colorr=0,colorg=1;colorb=0;break;
		case GLUT_KEY_F3 : figura=3;colorr=0,colorg=0;colorb=1;break;
		case GLUT_KEY_F4 : figura=4;colorr=0.749,colorg=0.541;colorb=0.125;break;
		case GLUT_KEY_F5 : figura=5;colorr=0.8,colorg=0.6;colorb=0.2; break;
		case GLUT_KEY_F6 : figura=6;colorr=1.6,colorg=1.2;colorb=0.4; break;
		case GLUT_KEY_F7 : figura=6;colorr=1.498,colorg=1.082;colorb=0.25; break;
	}
	glutPostRedisplay();
}

void texto(int x, int y, char *palabra) {
    int i;
	glColor3f(0,0,0);
	glRasterPos2f(x, y);  // Simular el movimiento del Cursos gotoXY
	for (i = 0; palabra[i]; i++)
	    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, palabra[i]);
}
