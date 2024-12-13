#include "include/GL/glut.h"
#include <cstdlib> // Para rand()
#include <ctime>   // Para seed do rand()
#include <cmath>   // Para funções trigonométricas

#define NUM_FLOCOS 200 // Número de flocos de neve
#define RAIO_DOMO 5.5f // Raio do domo
#define ALTURA_MAXIMA_DOMO 3.3f // Altura máxima dentro do domo
#define ALTURA_MINIMA_DOMO -1.5f // Altura mínima dentro do domo
#define GRAVIDADE 0.002f // Gravidade aplicada aos flocos

// Estrutura para representar um floco de neve
struct FlocoDeNeve {
    float x, y, z;   // Posição
    float velX, velY, velZ; // Velocidades nos eixos
};

// Array para os flocos de neve
FlocoDeNeve flocos[NUM_FLOCOS];

// Função para gerar uma posição aleatória dentro do domo
void gerarPosicaoDentroDomo(FlocoDeNeve &floco) {
    // do {
    //     floco.x = ((rand() % 200) - 100) / 18.0f; // Aleatório entre -5.5 e 5.5
    //     floco.y = ((rand() % 480) - 150) / 100.0f; // Aleatório entre -1.5 e 3.3
    //     floco.z = ((rand() % 200) - 100) / 18.0f; // Aleatório entre -5.5 e 5.5
    // } while (floco.x * floco.x + floco.y * floco.y + floco.z * floco.z > RAIO_DOMO * RAIO_DOMO);

    float angle = ((float)(rand() % 360)) * 2 * M_PI / 360.0f;
    float radius = 0.8 * ((float)rand() / (float)RAND_MAX ) * (float)RAIO_DOMO;

    floco.x = cosf(angle) * radius;
    floco.z = sinf(angle) * radius;
    floco.y = ((float)rand() / (float)RAND_MAX ) * 2 * ALTURA_MAXIMA_DOMO;

    floco.velX = ((rand() % 100) - 50) / 20000.0f; // Aleatório entre -0.025 e 0.025
    floco.velY = ((rand() % 100) + 10) / 10000.0f;  // Aleatório entre 0.01 e 0.1
    floco.velZ = ((rand() % 100) - 50) / 20000.0f; // Aleatório entre -0.025 e 0.025
}

// Inicializa os flocos de neve
void inicializarNeve() {
    srand(time(0)); // Semente para números aleatórios
    for (int i = 0; i < NUM_FLOCOS; i++) {
        gerarPosicaoDentroDomo(flocos[i]);
    }
}

// Atualiza os flocos de neve
void atualizarNeve() {
    for (int i = 0; i < NUM_FLOCOS; i++) {
        flocos[i].x += flocos[i].velX; // Atualiza posição no eixo X
        flocos[i].y += flocos[i].velY; // Atualiza posição no eixo Y
        flocos[i].z += flocos[i].velZ; // Atualiza posição no eixo Z

        // Aplicar gravidade no eixo Y
        flocos[i].velY -= GRAVIDADE;

        // // Reposicionar floco se sair dos limites do domo
        // if (flocos[i].x * flocos[i].x + flocos[i].y * flocos[i].y + flocos[i].z * flocos[i].z > RAIO_DOMO * RAIO_DOMO || flocos[i].y < ALTURA_MINIMA_DOMO) {
        //     gerarPosicaoDentroDomo(flocos[i]);
        // }
        // Reposicionar floco se sair dos limites do domo
        if (flocos[i].x * flocos[i].x + flocos[i].z * flocos[i].z > 0.8 * 0.8 * RAIO_DOMO * RAIO_DOMO || flocos[i].y < ALTURA_MINIMA_DOMO) {
            gerarPosicaoDentroDomo(flocos[i]);
        }
    }
}

// Desenha os flocos de neve
void desenharNeve() {
    glColor3f(1.0f, 1.0f, 1.0f); // Cor branca para a neve
    for (int i = 0; i < NUM_FLOCOS; i++) {
        glPushMatrix();
        glTranslatef(flocos[i].x, flocos[i].y, flocos[i].z);
        glutSolidSphere(0.05f, 10, 10); // Cada floco é uma esfera pequena
        glPopMatrix();
    }
}


void configurarLuzSecundaria(float intensidade) {
    GLfloat luzDifusa[] = {intensidade, intensidade, intensidade, 1.0f};
    GLfloat luzEspecular[] = {intensidade, intensidade, intensidade, 1.0f};
    GLfloat posicaoLuz[] = {-2.0f, 2.0f, 5.0f, 1.0f}; // Posição da segunda luz

    glEnable(GL_LIGHT1); // Ativar a segunda luz
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular);
    glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz);
}