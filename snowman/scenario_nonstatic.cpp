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

bool estaForaDoDomo(const FlocoDeNeve &floco);

// Função para gerar uma posição aleatória dentro do domo
void gerarPosicaoDentroDomo(FlocoDeNeve &floco) {
    float theta = ((float)(rand() % 360)) * 2 * M_PI / 360.0f;   // Azimuthal angle (0 to 2π)
    float phi = ((float)(rand() % 180)) - 90.0f;                 // Polar angle (-90 to 90 degrees)
    phi = phi * M_PI / 180.0f;  // Convert phi to radians
    float radius = ((float)rand() / (float)RAND_MAX ) * (float)RAIO_DOMO;  // Random radius between 0 and RAIO_DOMO

    floco.y = radius * sinf(phi) + ALTURA_MAXIMA_DOMO;  // Y position
    floco.x = radius * cosf(phi) * cosf(theta);         // X position
    floco.z = radius * cosf(phi) * sinf(theta);         // Z position

    // Random velocities
    floco.velX = ((rand() % 100) - 50) / 20000.0f;  // Random velocity between -0.025 and 0.025
    floco.velY = ((rand() % 100) + 10) / 10000.0f;  // Random velocity between 0.01 and 0.1
    floco.velZ = ((rand() % 100) - 50) / 20000.0f;  // Random velocity between -0.025 and 0.025
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
        if (estaForaDoDomo(flocos[i]) || flocos[i].y < ALTURA_MINIMA_DOMO) {
            gerarPosicaoDentroDomo(flocos[i]);
        }
    }
}

bool estaForaDoDomo(const FlocoDeNeve &floco) {
    // Adjust the y-coordinate to consider the constant height offset
    float yAjustado = floco.y - ALTURA_MAXIMA_DOMO;
    
    // Calculate the distance squared from the origin (0, 0, 0) to the snowflake's adjusted position
    float distanciaQuadrada = floco.x * floco.x + yAjustado * yAjustado + floco.z * floco.z;

    // If the distance squared is greater than the square of the dome radius, it's outside
    return distanciaQuadrada > (RAIO_DOMO * RAIO_DOMO);
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