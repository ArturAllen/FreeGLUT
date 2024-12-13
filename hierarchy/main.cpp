#include <GL/glut.h>
#include "scenario_static.h"
#include "scenario_nonstatic.h"
#include "snowman_body.h"
#include "snowman_arms.h"
#include <cstdlib>
#include <ctime>

// Variáveis globais para controle da câmera
float angulo_x = 0.0f, angulo_y = 0.0f, zoom = -10.0f; // Ângulos e zoom
int last_x = 0, last_y = 0;                            // Última posição do mouse
bool left_button_pressed = false;                      // Estado do botão esquerdo

// Prototipos das funções para neve
void inicializarNeve();
void atualizarNeve();
void desenharNeve();

void inicializa() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f); // Fundo azul-claro (céu)
    glEnable(GL_DEPTH_TEST);              // Ativar teste de profundidade

    // Configuração da iluminação
    GLfloat luzAmbiente[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat luzDifusa[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat luzEspecular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat posicaoLuz[] = {2.0f, 5.0f, 5.0f, 1.0f};

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Ativar materiais coloridos
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

    // Inicializar neve
    inicializarNeve();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Aplicação da câmera
    glTranslatef(0.0f, 0.0f, zoom);    // Ajusta o zoom
    glRotatef(angulo_x, 1.0, 0.0, 0.0); // Rotação em torno do eixo X
    glRotatef(angulo_y, 0.0, 1.0, 0.0); // Rotação em torno do eixo Y

    // Atualiza a posição da luz
    GLfloat posicaoLuz[] = {2.0f, 5.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);

    // Desenhar o cenário
    drawStaticScenario();  // Elementos estáticos
    drawSnowmanBody();     // Boneco de neve
    drawSnowmanArms();     // Braços do boneco

    // Atualizar e desenhar a neve
    atualizarNeve();
    desenharNeve();

    glutSwapBuffers();
}

void reshape(int largura, int altura) {
    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(65.0, (float)largura / (float)altura, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case '+':
            zoom += 0.5f; // Aproximar
            break;
        case '-':
            zoom -= 0.5f; // Afastar
            break;
        case 27: // Tecla Esc para sair
            exit(0);
    }
    glutPostRedisplay();
}

void mouseMotion(int x, int y) {
    if (left_button_pressed) {
        angulo_y += (x - last_x) * 0.2f; // Rotação no eixo Y
        angulo_x += (y - last_y) * 0.2f; // Rotação no eixo X
        glutPostRedisplay();
    }
    last_x = x;
    last_y = y;
}

void mouseButton(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        left_button_pressed = (state == GLUT_DOWN);
        last_x = x;
        last_y = y;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cenário com Neve Descendo");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutIdleFunc(display); // Atualizar continuamente

    glutMainLoop();
    return 0;
}
