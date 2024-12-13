#include <GL/glut.h>
#include "snowman_arms.h"

// Ângulos das articulações
int ombro = 0, cotovelo = 0, mao = 0;

// Desenha um cubo com textura
void desenhaCubo(float tamanho) {
    glutSolidCube(tamanho);
}

// Desenha os braços do boneco de neve
void drawSnowmanArms() {
    glPushMatrix();

    // Braço esquerdo
    glTranslatef(-0.7, 0.5, 0.0); // Posição inicial do ombro esquerdo
    glRotatef(ombro, 0.0, 0.0, 1.0); // Rotação no ombro
    glTranslatef(-0.5, 0.0, 0.0); // Ajuste para o centro do braço superior

    glPushMatrix();
    glScalef(1.0, 0.1, 0.1); // Escala do braço superior
    desenhaCubo(1.0);
    glPopMatrix();

    glTranslatef(-0.5, 0.0, 0.0); // Movimento para o cotovelo
    glRotatef(cotovelo, 0.0, 0.0, 1.0); // Rotação no cotovelo
    glTranslatef(-0.5, 0.0, 0.0); // Ajuste para o centro do braço inferior

    glPushMatrix();
    glScalef(1.0, 0.1, 0.1); // Escala do braço inferior
    desenhaCubo(1.0);
    glPopMatrix();

    glTranslatef(-0.5, 0.0, 0.0); // Movimento para a mão
    glRotatef(mao, 0.0, 0.0, 1.0); // Rotação na mão
    glTranslatef(-0.25, 0.0, 0.0); // Ajuste para o centro da mão

    glPushMatrix();
    glScalef(0.5, 0.2, 0.2); // Escala da mão
    desenhaCubo(1.0);
    glPopMatrix();

    glPopMatrix();

    // Braço direito (espelhado)
    glPushMatrix();
    glTranslatef(0.7, 0.5, 0.0); // Posição inicial do ombro direito
    glRotatef(-ombro, 0.0, 0.0, 1.0); // Rotação no ombro
    glTranslatef(0.5, 0.0, 0.0); // Ajuste para o centro do braço superior

    glPushMatrix();
    glScalef(1.0, 0.1, 0.1); // Escala do braço superior
    desenhaCubo(1.0);
    glPopMatrix();

    glTranslatef(0.5, 0.0, 0.0); // Movimento para o cotovelo
    glRotatef(-cotovelo, 0.0, 0.0, 1.0); // Rotação no cotovelo
    glTranslatef(0.5, 0.0, 0.0); // Ajuste para o centro do braço inferior

    glPushMatrix();
    glScalef(1.0, 0.1, 0.1); // Escala do braço inferior
    desenhaCubo(1.0);
    glPopMatrix();

    glTranslatef(0.5, 0.0, 0.0); // Movimento para a mão
    glRotatef(-mao, 0.0, 0.0, 1.0); // Rotação na mão
    glTranslatef(0.25, 0.0, 0.0); // Ajuste para o centro da mão

    glPushMatrix();
    glScalef(0.5, 0.2, 0.2); // Escala da mão
    desenhaCubo(1.0);
    glPopMatrix();

    glPopMatrix();
}
