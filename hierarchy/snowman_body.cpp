#include <GL/glut.h>

void drawSnowmanBody() {
    // Corpo (3 partes: base, meio e cabeça)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0.0f, 1.0f, 0.0f);   
    glutSolidSphere(1.0f, 50, 50);  // Base
    glTranslatef(0.0f, 1.5f, 0.0f);
    glutSolidSphere(0.7f, 50, 50); // Meio
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.5f, 50, 50); // Cabeça
    
    glPopMatrix();
}
