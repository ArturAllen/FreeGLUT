#include <GL/glut.h>
#include <cstdlib>
#include <ctime> 
#include <cmath> 

#define NUM_FLOCOS 200
#define RAIO_DOMO 5.5f
#define ALTURA_MAXIMA_DOMO 3.3f 
#define ALTURA_MINIMA_DOMO
#define GRAVIDADE 0.002f

struct FlocoDeNeve {
    float x, y, z; 
    float velX, velY, velZ; 
};

FlocoDeNeve flocos[NUM_FLOCOS];

void gerarPosicaoDentroDomo(FlocoDeNeve &floco) {
    do {
        floco.x = ((rand() % 200) - 100) / 18.0f; 
        floco.y = ((rand() % 480) - 150) / 100.0f;
        floco.z = ((rand() % 200) - 100) / 18.0f;
    } while (floco.x * floco.x + floco.y * floco.y + floco.z * floco.z > RAIO_DOMO * RAIO_DOMO);

    floco.velX = ((rand() % 100) - 50) / 2000.0f;
    floco.velY = ((rand() % 100) + 10) / 1000.0f;
    floco.velZ = ((rand() % 100) - 50) / 2000.0f;
}

void inicializarNeve() {
    srand(time(0)); 
    for (int i = 0; i < NUM_FLOCOS; i++) {
        gerarPosicaoDentroDomo(flocos[i]);
    }
}

void atualizarNeve() {
    for (int i = 0; i < NUM_FLOCOS; i++) {
        flocos[i].x += flocos[i].velX;
        flocos[i].y += flocos[i].velY; 
        flocos[i].z += flocos[i].velZ;

        flocos[i].velY -= GRAVIDADE;

        if (flocos[i].x * flocos[i].x + flocos[i].y * flocos[i].y + flocos[i].z * flocos[i].z > RAIO_DOMO * RAIO_DOMO || flocos[i].y < ALTURA_MINIMA_DOMO) {
            gerarPosicaoDentroDomo(flocos[i]);
        }
    }
}

void desenharNeve() {
    glColor3f(1.0f, 1.0f, 1.0f); 
    for (int i = 0; i < NUM_FLOCOS; i++) {
        glPushMatrix();
        glTranslatef(flocos[i].x, flocos[i].y, flocos[i].z);
        glutSolidSphere(0.05f, 10, 10); 
        glPopMatrix();
    }
}
