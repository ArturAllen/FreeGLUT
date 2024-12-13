#include "include/GL/glut.h"
#include "snowman_arms.h"

#include <cmath>

// Ângulos das articulações
int ombroL = 0, cotoveloL = 0, maoL = 0;
int ombroR = 0, cotoveloR = 0, maoR = 0;

// Desenha um cubo com textura
void desenhaCubo(float tamanho) {
    glutSolidCube(tamanho);
}

void setBracoEsquerdo(int ombro, int cotovelo, int mao) {
    ombroL = ombro; 
    cotoveloL = cotovelo; 
    maoL = mao;
}

void setBracoDireito(int ombro, int cotovelo, int mao) {
    ombroR = ombro; 
    cotoveloR = cotovelo; 
    maoR = mao;
}

void drawCylinder(int segments, float radius, float height) {
    GLUquadric* quad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texturaMadeira);
    gluQuadricTexture(quad, GL_TRUE); // Ativa a textura para o cilindro
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, radius, radius, height, 50, 50);
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}

void drawCylinder(int segments, float radius, float height, GLuint textureID) {
    int mode = GL_QUADS;
    
    for (int i = 0; i < segments; i++) {
        glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(mode);

            float x1 = radius * cosf(2 * M_PI * (float)i / (float)segments);
            float y1 = radius * sinf(2 * M_PI * (float)i / (float)segments);
            
            float x2 = radius * cosf(2 * M_PI * (float)(i+1) / (float)segments);
            float y2 = radius * sinf(2 * M_PI * (float)(i+1) / (float)segments);

            // Texture coordinates for the first vertex
            glTexCoord2f((float)i / (float)segments, 0.0); // Horizontal = i/segments, Vertical = 0 (bottom)
            glVertex3f(x1, 0, y1);

            // Texture coordinates for the second vertex
            glTexCoord2f((float)i / (float)segments, 1.0); // Horizontal = i/segments, Vertical = 1 (top)
            glVertex3f(x1, height, y1);

            // Texture coordinates for the third vertex
            glTexCoord2f((float)(i+1) / (float)segments, 1.0); // Horizontal = (i+1)/segments, Vertical = 1 (top)
            glVertex3f(x2, height, y2);

            // Texture coordinates for the fourth vertex
            glTexCoord2f((float)(i+1) / (float)segments, 0.0); // Horizontal = (i+1)/segments, Vertical = 0 (bottom)
            glVertex3f(x2, 0, y2);

        glEnd();
    }
    
    glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float x1 = radius * cosf(2 * M_PI * (float)i / (float)segments);
            float y1 = radius * sinf(2 * M_PI * (float)i / (float)segments);
            
            glVertex3f(x1, 0, y1);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for (int i = 0; i < segments; i++) {
            float x1 = radius * cosf(2 * M_PI * (float)i / (float)segments);
            float y1 = radius * sinf(2 * M_PI * (float)i / (float)segments);
            
            glVertex3f(x1, height, y1);
        }
    glEnd();
}

void drawSnowmanArms(GLuint texId) {
    glBindTexture(GL_TEXTURE_2D, texId);
    glPushMatrix(); // Braco esquerdo
        
        glTranslatef(0.7, 2.5, 0.0);
        glutSolidSphere(0.325, 50, 50);
        glRotatef(ombroL, 0.0, 0.0, 1.0);
        glPushMatrix();

            glPushMatrix();
                glRotatef(90, 0.0, 1.0, 0.0);
                drawCylinder(16, 0.18, 1.0);
            glPopMatrix();

            glTranslatef(1.0, 0.0, 0.0);
            glRotatef(cotoveloL, 0.0, 0.0, 1.0);
            glPushMatrix();
                glutSolidSphere(0.28, 50, 50);
                
                glPushMatrix();
                    glRotatef(90, 0.0, 1.0, 0.0);
                    drawCylinder(16, 0.18, 1.0);
                glPopMatrix();

                glTranslatef(1.0, 0.0, 0.0);
                glColor3f(0.8, 0.0, 0.0);
                glutSolidSphere(0.325, 50, 50);
                glColor3f(1.0, 1.0, 1.0);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();

    glPushMatrix(); // Braco direito
        
        glTranslatef(-0.7, 2.5, 0.0);
        glRotatef(-ombroR, 0.0, 0.0, 1.0);
        glPushMatrix();
            glutSolidSphere(0.325, 50, 50);

            glPushMatrix();
                glRotatef(-90, 0.0, 1.0, 0.0);
                drawCylinder(16, 0.18, 1.0);
            glPopMatrix();

            glTranslatef(-1.0, 0.0, 0.0);
            glRotatef(-cotoveloR, 0.0, 0.0, 1.0);
            glPushMatrix();
                glutSolidSphere(0.28, 50, 50);
                
                glPushMatrix();
                    glRotatef(-90, 0.0, 1.0, 0.0);
                    drawCylinder(16, 0.18, 1.0);
                glPopMatrix();

                glTranslatef(-1.0, 0.0, 0.0);
                glColor3f(0.8, 0.0, 0.0);
                glutSolidSphere(0.325, 50, 50);
                glColor3f(1.0, 1.0, 1.0);
            glPopMatrix();

        glPopMatrix();
    glPopMatrix();
}
