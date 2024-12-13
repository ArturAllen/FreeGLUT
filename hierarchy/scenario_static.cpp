#include <GL/glut.h>

// Função para desenhar o cenário estático
void drawStaticScenario() {
    // Chão
    glPushMatrix();
    glColor3f(0.9f, 0.9f, 0.9f); // Cor do chão (branco neve)
    glTranslatef(0.0f, -1.0f, 0.0f);
    glScalef(10.0f, 0.1f, 10.0f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Árvore
    glPushMatrix();
    glColor3f(0.5f, 0.25f, 0.0f); // Tronco
    glTranslatef(2.5f, -0.5f, 0.0f);
    glScalef(0.2f, 1.0f, 0.2f);
    glutSolidCube(1.0f);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Cone verde (folhas)
    glTranslatef(2.5f, 0.5f, 0.0f);
    glutSolidCone(1.0f, 2.0f, 50, 50);
    glPopMatrix();
}
