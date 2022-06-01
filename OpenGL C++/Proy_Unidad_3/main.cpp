#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <stdlib.h>

int refreshMills = 30; //Inervalo en milisegundos

#define ancho 640
const int alto = 480;
#define profundidad 500

float angulo=0; //Angulo de rotacion
float esc=1;
int posx=0, posy=0, posz=0;
int Ejex=1, Ejey=1, Ejez=1;

unsigned int figura=1;
unsigned int luz=1;
unsigned int movimiento=1;

                  //Ambiente   r  -  g  - b -  a
GLfloat material_ambient[] = {1.0f, 0.3, 0.0, 1.0f};
               //Difuminado     r  - g  - b -  a
GLfloat material_diffuse[] = { 0.8, 0.2, 0.0, 1.0f};
               //Reflejo          r - g  - b - a
GLfloat material_specular[] = {0.3, 0.4, 0.0, 1.0f};
               //Emitir luz    r  - g - b - a
GLfloat material_emission[] = {0.1, 0.0, 0.0, 1.0f};

   //Ambiente de la luz   r - g - b - a
GLfloat luz_ambient[] = { 0.25, 1.0f, 0.0, 0.0 };
//Difuminacion de la luz   r  - g  -  b  - a
GLfloat luz_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
//Reflejo de la luz         r   - g  - b - a
GLfloat luz_specular[] = { 1.0, 1.0, 1.0, 1.0 };
//Posicion de la luz        x  -  y - z  - (Centro)?
GLfloat luz_position[] = { 1.0, 1.0, 1.0, 0.0 };

void ejes();
void luces();
void tecladoNormal(unsigned char tecla, int x, int y);
void tecladoEspecial(int tecla, int x, int y);
void texto(int x, int y, char *palabra);

void moverR();
void moverPX();
void moverPY();
 

void display() {
   glClear(GL_STENCIL_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   

   ejes();
   luces();

 
   glPushMatrix();                

      glTranslatef(posx, 0, 0);
      glTranslatef(0, posy, 0);
      glTranslatef(0, 0, posz);

      glRotatef(angulo, Ejex, 0, 0);
      glRotatef(angulo, 0, Ejey, 0);
      glRotatef(angulo, 0, 0, Ejez);

      glScalef(esc, esc, esc);
      glColor3f(1, 0.3, 0);

      if(luz==1)
         glEnable(GL_LIGHTING);
      switch(figura) {
         case 1: glutSolidTorus(1, 2, 360, 360);break;
         case 2: glutSolidSphere(1, 360, 360);break;
         case 3: glutSolidCone(1, 5, 360, 360);break;
         case 4: glutSolidCube(1);break;
         case 5: glutSolidTetrahedron(); break;
         case 6: glutSolidOctahedron(); break;
         case 7: glutSolidDodecahedron(); break;
         case 8: glutSolidIcosahedron(); break;
         case 9: glutSolidTeapot(1); break;
      }
         glDisable(GL_LIGHTING);
   
   glPopMatrix();                    

   texto(-7, 5,"[F1: TOROIDE] [F2: ESFERA] [F3: CONO] [F4: CUBO]");
   texto(-7,-5,"[F9: PUNTOS] [F10: LINEAS] [F11: RELLENO]");
   texto(4,-5,"[F5: ALTERNAR MOVIMIENTO]");

   glutSwapBuffers();  
 
}

void initGL() {
   // Limpiar o establecer color de fondo
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}


//---------------- ALGORITMO SACADO DE QT PECES ----------------

void moverPY()
{
    int x = 0;
    static int y = 0;
    static bool band = true;
    if(posy < (11 - 1) && band)
    {
        posy = y;
        y += 1;
        if(posy >= (11 - 1)){
            band = false;
         }
    }
    if(!band)
    {
        y -= 1;
        posy = y;
        if(y == (-11 + 1)){
            band = true;
         }
    }
}

void moverPX()
{
    static int x = 0;
    int y = 0;
    static bool band = true;
    if(posx < (11 - 1) && band)
    {
        posx = x;
        x += 1;
        if(posx >= (11 - 1))
            band = false;
    }
    if(!band)
    {
        x -= 1;
        posx = x;
        if(x == (-11 + 1))
            band = true;
    }
}

void moverR()
{
    int x = posx;
    static int y = 0;
    static bool band = true;
    if(posy < (11 - 1) && band)
    {
        posy = y;
        y += 1;
        if(posy >= (11 - 1))
            band = false;
    }
    if(!band)
    {
        y -= 1;
        posy = y;
        if(y == (-11 + 1))
            band = true;
    }
}

//---------------- ALGORITMO SACADO DE QT DE PECES ----------------


void Timer(int value) {
   if (movimiento==1) {
        angulo+=0.3;
        
      if (angulo>=360)
            angulo=0;
   }else{
      angulo=angulo+0.3;


  // ---- REBOTAR FIG EN PANTALLA------

      moverR();  
      moverPX();
      moverPY();

  // ------------------------------------

      if (angulo>=360)
            angulo=0;
   }    
   glutPostRedisplay();
   glutTimerFunc(refreshMills, Timer, 0);
}

//--------------EJES---------------------
void ejes() {
    glColor3f(0.9, 0.9, 0.9);
    
   glBegin(GL_LINES);
   
        glVertex3f(-ancho/2, 0, 0); //EJE -x
        glVertex3f(ancho/2, 0, 0);  //EJE X
        glVertex3f(0, alto/2, 0);  //EJE Y
        glVertex3f(0, -alto/2, 0); //EJE -Y

   glEnd();
}

//-----------------TEXTO EN PANTALLA---------------
void texto(int x, int y, char *palabra) {
    int i;
    
   glColor3f(1,1,1);
   glRasterPos2f(x, y);
   
   for (i = 0; palabra[i]; i++)
       glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, palabra[i]);
}


void tecladoNormal(unsigned char tecla, int x, int y) {
    switch(tecla) {
        case 's':
        case 'S':
        case 27: exit(0);break; //SALIR
        case 'x':
        case 'X': Ejex =1; Ejey = Ejez = 0; break; //Cambiar eje de rotacion por 'X'
        case 'y':
        case 'Y': Ejey =1; Ejex = Ejez = 0; break; //Cambiar eje de rotacion por 'Y'
        case 'z':
        case 'Z': Ejez =1; Ejex = Ejey = 0; break; //Cambiar eje de rotacion por 'Z'
        case 'c':
        case 'C': Ejez = Ejex = Ejey = 1; break; //Poner 1 en todo 'X','Y','Z'
        case '1': figura=1;break; //Camabios de Figuras
        case '2': figura=2;break;
        case '3': figura=3;break;
        case '4': figura=4;break;
        case '5': figura=5; break;
        case '6': figura=6;break; 
        case '7': figura=7;break;
        case '8': figura=8;break;
        case '9': figura=9;break;
   
    glutPostRedisplay();
  }
}

void tecladoEspecial(int tecla, int x, int y) {
    switch(tecla) {
        case GLUT_KEY_UP : posy++;break; //Posicion y ++
        case GLUT_KEY_DOWN : posy--;break; //Posicion y --
        case GLUT_KEY_RIGHT : posx++;break; //Posicion x ++
        case GLUT_KEY_LEFT : posx--;break;  //Posicion x --
        case GLUT_KEY_F6 : posz++;break;  //Posicion z ++
        case GLUT_KEY_F7 : posz--;break;  //Posicion z --
        case GLUT_KEY_PAGE_UP : esc*=1.01;break;   //Escalar ++
        case GLUT_KEY_PAGE_DOWN : esc*=0.99;break;  //Escalar --
        case GLUT_KEY_F5 : if(movimiento==0) movimiento=1; else movimiento=0;break;  //Cambio de Animacion
        case GLUT_KEY_F9 : luz=0; glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);  glPointSize(3); break; //Puntos
        case GLUT_KEY_F10 : luz=0; glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); glLineWidth(2);break;  //Lineas
        case GLUT_KEY_F11 : luz=1; glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);break;  //Relleno
   }
   
   glutPostRedisplay();
}

 
void redimensionado(int anchop, int altop) {
    glViewport(0,0,anchop,altop);
    glMatrixMode(GL_PROJECTION); //Aplica operaciones de matriz posteriores a la pila de matriz de proyección.
    glLoadIdentity();


   //fovy = El ángulo del campo de visión, en grados, en la dirección y

      /*aspect = La relación de aspecto que determina el campo de visión en la dirección x. 
         La relación de aspecto es la relación de x (ancho) a y (altura) */

         //zNear = La distancia desde el espectador hasta el plano de recorte cercano (siempre positivo)

            //zFar = La distancia desde el espectador hasta el plano de recorte lejano (siempre positivo)
    gluPerspective(60.0f,(GLfloat)ancho/(GLfloat)alto,0.1,profundidad*2);

   /*eyex: La posición del punto del ojo x.
    *eyey:La posición del punto del ojo y.
    *eyez: La posición del punto del ojo z.
    *centerx: La posición del punto de referencia x.
    *centery: La posición del punto de referencia y.
    *centerz: La posición del punto de referencia z.
    *upx: La dirección del vector hacia arriba x.
    *upy: La dirección del vector hacia arriba y.
    *upz: La dirección del vector hacia arriba z.*/
    gluLookAt(0,0,/*profundidad/1.2*/ 10,0,0,0,0,1,0);

    //La función glMatrixMode especifica qué matriz es la matriz actual
    glMatrixMode(GL_MODELVIEW); //Aplica operaciones matriciales posteriores a la pila matricial modelview.s
    
    glLoadIdentity();
}


//-------- LUCES --------------------------------
void luces() {

   // ------------- CARACTERISTICAS DEL MATERIAL ------------------------

   //DETALLES ARRIBA
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);

    //Tambien existe emision para dar la sensacion de que el material emite luz
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);

                                          //Rango: [0 - 128]
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0f); //BRILLO

   // ------------- CARACTERISTICAS DEL MATERIAL ------------------------



   // ------------- CARACTERISTICAS DEL BRILLO ------------------------ 
    glLightfv(GL_LIGHT0, GL_AMBIENT, luz_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luz_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luz_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, luz_position);
   // ------------- CARACTERISTICAS DEL BRILLO ------------------------
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
}
 
int main(int argc, char** argv) {
   glutInit(&argc, argv);          // Inicializa glut
   glutInitDisplayMode(GLUT_STENCIL | GLUT_DOUBLE | GLUT_DEPTH);  // Abilita el modo double buffered

   glutInitWindowSize(ancho, alto);   // Dimensiones del window
   glutInitWindowPosition(100, 100); // Posicion del Window

   glutCreateWindow("Proy Unidad 3");  // Crear Window


   glutDisplayFunc(display);        //Funcion para el display
   glutReshapeFunc(redimensionado);      //Funcion de la redimensionado
   glutTimerFunc(0, Timer, 0);     //Funcion de llamada del timer

   glutKeyboardFunc(tecladoNormal);  //Funciones del Teclado
   glutSpecialFunc(tecladoEspecial);


   initGL();                       // Incializacion propia de OPENGL

   glutMainLoop();                 // Enter the infinite event-processing loop
   return 0;
}
