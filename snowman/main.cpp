#include "include/GL/glut.h"
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

GLuint woodTexId;

// Prototipos das funções para neve
void inicializarNeve();
void atualizarNeve();
void desenharNeve();

// Função para desenhar o domo semi-transparente com corte inferior
void desenharDomo() {
    glPushMatrix();

    // Ativar semi-transparência
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Cor e transparência do domo
    glColor4f(1.0f, 1.0f, 1.0f, 0.2f); // Branco semi-transparente

    // Posicionar o domo
    glTranslatef(0.0f, 3.3f, 0.0f); // Ajustar altura para a base do domo

    // Habilitar o plano de corte
    GLdouble planoCorte[] = {0.0, 0.15, 0.0, 0.6}; // Plano que corta apenas 10% inferior do domo
    glClipPlane(GL_CLIP_PLANE0, planoCorte);
    glEnable(GL_CLIP_PLANE0);

    // Criar a parte superior do domo (esfera cortada)
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricDrawStyle(quad, GLU_FILL);
    gluSphere(quad, 5.5f, 50, 50); // Esfera com raio 6.0

    // Desativar o plano de corte
    glDisable(GL_CLIP_PLANE0);

    gluDeleteQuadric(quad);

    // Desativar semi-transparência
    glDisable(GL_BLEND);

    glPopMatrix();
}

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

    configurarLuzSecundaria(0.5);

    // Inicializar neve
    inicializarNeve();

    carregarTextura("textura/wood.png", woodTexId);
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
    drawStaticScenario(woodTexId);  // Elementos estáticos
    drawSnowmanBody();     // Boneco de neve
    drawSnowmanArms(woodTexId);     // Braços do boneco

    // Atualizar e desenhar a neve
    atualizarNeve();
    desenharNeve();

    // Desenhar o domo semi-transparente
    desenharDomo();

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

bool left_arrow_key_pressed = false;
bool right_arrow_key_pressed = false;

int ombro_direito = 0, cotovelo_direito = 0;
int ombro_esquerdo = 0, cotovelo_esquerdo = 0;

void teclado(unsigned char tecla, int x, int y) {
    switch (tecla) {
        case '=':
        case '+':
            zoom += 0.5f; // Aproximar
            break;
        case '-':
            zoom -= 0.5f; // Afastar
            break;
        case 'c':
            if (left_arrow_key_pressed && cotovelo_esquerdo < 120) cotovelo_esquerdo += 5;
            if (right_arrow_key_pressed && cotovelo_direito < 120) cotovelo_direito += 5;

            setBracoEsquerdo(ombro_esquerdo, cotovelo_esquerdo, 0);
            setBracoDireito(ombro_direito, cotovelo_direito, 0);

            break;
        case 'C':
            if (left_arrow_key_pressed && cotovelo_esquerdo > 0) cotovelo_esquerdo -= 5;
            if (right_arrow_key_pressed && cotovelo_direito > 0) cotovelo_direito -= 5;

            setBracoEsquerdo(ombro_esquerdo, cotovelo_esquerdo, 0);
            setBracoDireito(ombro_direito, cotovelo_direito, 0);

            break;
        case 'o':
            if (left_arrow_key_pressed && ombro_esquerdo < 80) ombro_esquerdo += 5;
            if (right_arrow_key_pressed && ombro_direito < 80) ombro_direito += 5;

            setBracoEsquerdo(ombro_esquerdo, cotovelo_esquerdo, 0);
            setBracoDireito(ombro_direito, cotovelo_direito, 0);

            break;
        case 'O':
            if (left_arrow_key_pressed && ombro_esquerdo > -60) ombro_esquerdo -= 5;
            if (right_arrow_key_pressed && ombro_direito > -60) ombro_direito -= 5;

            setBracoEsquerdo(ombro_esquerdo, cotovelo_esquerdo, 0);
            setBracoDireito(ombro_direito, cotovelo_direito, 0);

            break;
        case 27: // Tecla Esc para sair
            exit(0);
    }
    glutPostRedisplay();
}

void arrowKeysDown(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) left_arrow_key_pressed = true;
    if (key == GLUT_KEY_RIGHT) right_arrow_key_pressed = true;
}

void arrowKeysUp(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) left_arrow_key_pressed = false;
    if (key == GLUT_KEY_RIGHT) right_arrow_key_pressed = false;
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

void menu(int option) {
    switch (option){
        case 0: // Forte
            configurarLuzSecundaria(1.0);
            break;
        case 1: // Medio
            configurarLuzSecundaria(0.5);
            break;
        case 2: // Fraco
            configurarLuzSecundaria(0.1);
            break;
        default:
            break;
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
    glutSpecialFunc(arrowKeysDown);
    glutSpecialUpFunc(arrowKeysUp);
    glutMotionFunc(mouseMotion);
    glutMouseFunc(mouseButton);
    glutIdleFunc(display); // Atualizar continuamente
    
    glutCreateMenu(menu);
    glutAddMenuEntry("Forte", 0);
    glutAddMenuEntry("Media", 1);
    glutAddMenuEntry("Fraca", 2);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
