#include <GL/glut.h>
#include "snowman_body.h"
#include "snowman_arms.h"
#include "scenario_static.h"
#include "scenario_nonstatic.h"

// Inicialização do OpenGL
void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Fundo azul-claro (céu)
    glEnable(GL_DEPTH_TEST);             // Habilita teste de profundidade
    glEnable(GL_LIGHTING);               // Habilita iluminação
    glEnable(GL_LIGHT0);                 // Habilita luz 0

    GLfloat luzAmbiente[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat luzDifusa[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat luzEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat posicaoLuz[] = {2.0f, 5.0f, 5.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    glEnable(GL_COLOR_MATERIAL); // Ativa materiais coloridos
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

// Função para renderizar a cena
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 2.0f, 6.0f,  // Posição da câmera
              0.0f, 0.5f, 0.0f,  // Ponto para onde a câmera está olhando
              0.0f, 1.0f, 0.0f); // Vetor "up"

    drawStaticScenario();   // Chama o cenário estático
    drawSnowmanBody();      // Chama o corpo do boneco de neve
    drawSnowmanArms();      // Chama os braços do boneco de neve
    drawNonStaticScenario(); // Chama os elementos dinâmicos

    glutSwapBuffers();
}

// Função para ajustar o tamanho da janela
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

// Função principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Boneco de Neve - Modularizado");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}
