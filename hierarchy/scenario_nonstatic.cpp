#include <GL/glut.h>
#include <cstdlib> // Para rand()
#include <ctime>   // Para seed do rand()

#define NUM_FLOCOS 200 // Número de flocos de neve

// Estrutura para representar um floco de neve
struct FlocoDeNeve {
    float x, y, z;   // Posição
    float velocidade; // Velocidade de descida
};

// Array para os flocos de neve
FlocoDeNeve flocos[NUM_FLOCOS];

// Inicializa os flocos de neve
void inicializarNeve() {
    srand(time(0)); // Semente para números aleatórios
    for (int i = 0; i < NUM_FLOCOS; i++) {
        flocos[i].x = ((rand() % 200) - 100) / 10.0f; // Aleatório entre -10 e 10
        flocos[i].y = ((rand() % 200) / 10.0f);       // Aleatório entre 0 e 20
        flocos[i].z = ((rand() % 200) - 100) / 10.0f; // Aleatório entre -10 e 10
        flocos[i].velocidade = ((rand() % 50) + 10) / 1000.0f; // Aleatório entre 0.01 e 0.05
    }
}

// Atualiza os flocos de neve
void atualizarNeve() {
    for (int i = 0; i < NUM_FLOCOS; i++) {
        flocos[i].y -= flocos[i].velocidade; // Floco desce
        if (flocos[i].y < -1.5f) {           // Se sair do chão, reinicia no topo
            flocos[i].x = ((rand() % 200) - 100) / 10.0f;
            flocos[i].y = 20.0f;
            flocos[i].z = ((rand() % 200) - 100) / 10.0f;
            flocos[i].velocidade = ((rand() % 50) + 10) / 1000.0f;
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
