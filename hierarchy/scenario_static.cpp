#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GL/glut.h>

// ID da textura para o tronco
GLuint texturaMadeira;

// Carrega a textura de madeira usando stb_image.h
void carregarTexturaMadeira() {
    int largura, altura, canais;
    unsigned char* dados = stbi_load("textura/madeira2.jpg", &largura, &altura, &canais, 0);
    if (!dados) {
        printf("Erro ao carregar a textura madeira2.jpg. Verifique o caminho e o arquivo.\n");
        return;
    }

    glGenTextures(1, &texturaMadeira);
    glBindTexture(GL_TEXTURE_2D, texturaMadeira);

    // Configurações da textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Envia os dados da textura para o OpenGL
    if (canais == 4) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, dados);
    } else {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, largura, altura, 0, GL_RGB, GL_UNSIGNED_BYTE, dados);
    }

    stbi_image_free(dados);
}

// Desenha um cilindro texturizado
void desenhaCilindro(float base, float altura) {
    GLUquadric* quad = gluNewQuadric();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, texturaMadeira);
    gluQuadricTexture(quad, GL_TRUE); // Ativa a textura para o cilindro
    gluQuadricNormals(quad, GLU_SMOOTH);
    gluCylinder(quad, base, base, altura, 50, 50);
    glDisable(GL_TEXTURE_2D);
    gluDeleteQuadric(quad);
}
GLuint texturaChao;

void drawStaticScenario(GLuint texId) {
    // Base do globo de neve (tronco de cone com faces superior e inferior)
    glPushMatrix();
    glColor3f(0.6f, 0.6f, 0.6f); // Cor da base (cinza)
    glTranslatef(0.0f, -1.5f, 0.0f); // Ajuste para posicionar a base no plano
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotação para alinhar ao plano XZ
    GLUquadric* quad = gluNewQuadric();

    // Face inferior
    gluDisk(quad, 0.0f, 6.0f, 50, 50);

    // Tronco de cone
    gluCylinder(quad, 6.0f, 5.0f, 1.5f, 50, 50);

    // Face superior
    glTranslatef(0.0f, 0.0f, 1.5f); // Move para a altura da face superior
    gluDisk(quad, 0.0f, 5.0f, 50, 50);

    gluDeleteQuadric(quad);
    glPopMatrix();

    // Tronco da árvore (cilíndrico com textura)
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, -2.0f); // Ajuste no eixo Y para começar na face superior
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f); // Rotação para alinhar ao eixo Y
    desenhaCilindro(0.3f, 3.0f); // Base maior (0.3) e altura maior (3.0)
    glPopMatrix();

    // Folhas da árvore (cones alinhados ao eixo Y)
    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Verde
    glTranslatef(-2.0f, 1.5f, -2.0f); // Posição inicial do cone inferior
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Rotação para alinhar ao eixo Y
    glutSolidCone(1.5f, 3.0f, 50, 50); // Cone inferior maior
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Verde
    glTranslatef(-2.0f, 3.0f, -2.0f); // Posição inicial do cone do meio
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Rotação para alinhar ao eixo Y
    glutSolidCone(1.2f, 2.25f, 50, 50); // Cone do meio maior
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0f, 0.5f, 0.0f); // Verde
    glTranslatef(-2.0f, 4.2f, -2.0f); // Posição inicial do cone superior
    glRotatef(-90, 1.0f, 0.0f, 0.0f); // Rotação para alinhar ao eixo Y
    glutSolidCone(0.9f, 1.5f, 50, 50); // Cone superior maior
    glPopMatrix();
}


void carregarTextura(const char* nomeArquivo, GLuint &id)
{
    int largura, altura, canais;
    unsigned char *dados = stbi_load(nomeArquivo, &largura, &altura, &canais, 0);

    if (!dados)
        exit(1);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, (canais == 4) ? GL_RGBA : GL_RGB,
                 largura, altura, 0, (canais == 4) ? GL_RGBA : GL_RGB,
                 GL_UNSIGNED_BYTE, dados);

    stbi_image_free(dados);
}