#include <GL/glut.h>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

GLuint idTextura1;
GLuint idTextura2;
GLuint idTextura3;

float rotX=0, rotY=0, rotZ=0;

void carregarTextura(const char* nomeArquivo, GLuint &id)
{
 int largura, altura, canais;

 unsigned char *dados = stbi_load(nomeArquivo, &largura, &altura, &canais, 0);

 if (!dados)
  exit(1);

 // gerar textura
 glGenTextures(1, &id);
 glBindTexture(GL_TEXTURE_2D, id);

 // configurar parametros da textura
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
 glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

 glTexImage2D(GL_TEXTURE_2D, 0, (canais == 4) ? GL_RGBA : GL_RGB, 
               largura, altura, 0, (canais == 4) ? GL_RGBA : GL_RGB,
               GL_UNSIGNED_BYTE, dados);

 stbi_image_free(dados);
}

void carregarTextura(GLuint *id) {
    
}

void inicializa() {
 glClearColor(0.1, 0.1, 0.1, 1.0);
 glEnable(GL_DEPTH_TEST);
 glEnable(GL_TEXTURE_2D);

//  carregarTextura("texturas/azulejo.jpg
 carregarTextura("texturas/azulejo.jpg", idTextura1);
 carregarTextura("texturas/madeira.png", idTextura2);
 carregarTextura("texturas/madeira.png", idTextura3);
}

void desenhaCubo(float tamanho)
{

    glBindTexture(GL_TEXTURE_2D, idTextura1);
  glBegin(GL_QUADS);
    // face frontal
    glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, -tamanho, tamanho);
    glTexCoord2f(1.0, 0.0); glVertex3f(tamanho, -tamanho, tamanho);
    glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, tamanho, tamanho);
    glTexCoord2f(0.0, 1.0); glVertex3f(-tamanho, tamanho, tamanho);

  // face traseira
  glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 0.0); glVertex3f(tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, tamanho, -tamanho);
  glTexCoord2f(0.0, 1.0); glVertex3f(-tamanho, tamanho, -tamanho);
  glEnd();


  glBindTexture(GL_TEXTURE_2D, idTextura2);
  glBegin(GL_QUADS);
  // face superior
//   glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, tamanho, -tamanho);
//   glTexCoord2f(1.0, 0.0); glVertex3f(tamanho, tamanho, -tamanho);
//   glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, tamanho, tamanho);
//   glTexCoord2f(0.0, 1.0); glVertex3f(-tamanho, tamanho, tamanho);
  glTexCoord2f(1.0, 0.0); glVertex3f(-tamanho, tamanho, -tamanho);
  glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, tamanho, -tamanho);
  glTexCoord2f(0.0, 1.0); glVertex3f(tamanho, tamanho, tamanho);
  glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, tamanho, tamanho);

  // face inferior
  glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 0.0); glVertex3f(tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, -tamanho, tamanho);
  glTexCoord2f(0.0, 1.0); glVertex3f(-tamanho, -tamanho, tamanho);

  // face direita
  glTexCoord2f(0.0, 0.0); glVertex3f(tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 0.0); glVertex3f(tamanho, tamanho, -tamanho);
  glTexCoord2f(1.0, 1.0); glVertex3f(tamanho, tamanho, tamanho);
  glTexCoord2f(0.0, 1.0); glVertex3f(tamanho, -tamanho, tamanho);

  // face esquerda
  glTexCoord2f(0.0, 0.0); glVertex3f(-tamanho, -tamanho, -tamanho);
  glTexCoord2f(1.0, 0.0); glVertex3f(-tamanho, tamanho, -tamanho);
  glTexCoord2f(1.0, 1.0); glVertex3f(-tamanho, tamanho, tamanho);
  glTexCoord2f(0.0, 1.0); glVertex3f(-tamanho, -tamanho, tamanho);

 glEnd();    
}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 glLoadIdentity();
 glTranslatef(0.0, 0.0, -5.0);
 glRotatef(rotX, 1.0, 0.0, 0.0);
 glRotatef(rotY, 0.0, 1.0, 0.0);
 glRotatef(rotZ, 0.0, 0.0, 1.0);

 desenhaCubo(1.0);

 glutSwapBuffers();
}

void animacao(int valor) {
    rotY += 1;
    glutPostRedisplay();

    glutTimerFunc(16, animacao, 0);
}
 
void reshape(int largura, int altura) {
    glViewport(0,0,largura, altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)largura/(GLfloat)altura, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void teclado(unsigned char c, int x, int y) {
    if (c == 'w' || c == 'w') rotX += 5;
    if (c == 'S' || c == 's') rotX -= 5;
}

int main(int argc, char** argv) {
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(800, 600);
 glutCreateWindow("Textura no Cubo");

 inicializa();

 glutDisplayFunc(display);
 glutReshapeFunc(reshape);
 glutTimerFunc(16, animacao, 0); 
 glutKeyboardFunc(teclado);
 glutMainLoop();

 return 0;
}