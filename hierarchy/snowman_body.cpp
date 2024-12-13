#include <GL/glut.h>

void desenharGorro();

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

    glPushMatrix();// olho esquerdo
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.2, 0.2, 0.45);
        glutSolidSphere(0.0625, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// olho direito
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-0.2, 0.2, 0.45);
        glutSolidSphere(0.0625, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix(); // Nariz
        glColor3f(0.929, 0.569, 0.129);
        glTranslatef(0.0, 0.0, 0.45);
        glutSolidCone(0.08, 0.25, 50, 50);
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// boca
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.0, -0.2, 0.48);
        glutSolidSphere(0.05, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// boca
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.18, -0.17, (0.5+0.45)/2);
        glutSolidSphere(0.05, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// boca
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0.3, -0.1, 0.45);
        glutSolidSphere(0.05, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// boca
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-0.18, -0.17, (0.5+0.45)/2);
        glutSolidSphere(0.05, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    glPushMatrix();// boca
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(-0.3, -0.1, 0.45);
        glutSolidSphere(0.05, 50,50); 
        glColor3f(1.0, 1.0, 1.0);
    glPopMatrix();

    desenharGorro();
    
    glPopMatrix();
}

void desenharGorro() {
    glScalef(0.8, 0.8, 0.8);
    glRotatef(-15, 0.1, 0.0, 0.0);
    glPushMatrix();
    // Posicionar o gorro na cabeça do boneco de neve
    glTranslatef(0.0f, 0.30, 0.0f); 

    // Parte vermelha do gorro (cone)
    glColor3f(1.0f, 0.0f, 0.0f); // Vermelho
    GLUquadric* quad = gluNewQuadric();
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluQuadricDrawStyle(quad, GLU_FILL);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(quad, 0.7f, 0.0f, 1.0f, 30, 30); 

    // Parte branca (borda do gorro)
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f); 
    glTranslatef(0.0f, 0.0f, 0.0f);
    glutSolidTorus(0.1f, 0.7f, 20, 20); 
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(0.0f, 0.0f, 1.0f); 
    glutSolidSphere(0.2f, 20, 20); 
    glPopMatrix();

    gluDeleteQuadric(quad);
    glPopMatrix();
}