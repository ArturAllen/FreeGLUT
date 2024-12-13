#include <GL/glut.h>
#include <cstdlib>
#include <ctime>
#include "scenario_nonstatic.h"

#define NUM_SNOWFLAKES 100

struct Snowflake {
    float x, y, z;
    float speed;
};

Snowflake snowflakes[NUM_SNOWFLAKES];

void initSnowflakes() {
    std::srand(std::time(0));
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        snowflakes[i].x = (std::rand() % 100 - 50) / 5.0f; // X: -10 a 10
        snowflakes[i].y = (std::rand() % 100) / 5.0f + 5.0f; // Y: 5 a 25
        snowflakes[i].z = (std::rand() % 100 - 50) / 5.0f; // Z: -10 a 10
        snowflakes[i].speed = (std::rand() % 50 + 10) / 500.0f; // Velocidade
    }
}

void drawSnowflakes() {
    for (int i = 0; i < NUM_SNOWFLAKES; i++) {
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f); // Branco
        glTranslatef(snowflakes[i].x, snowflakes[i].y, snowflakes[i].z);
        glutSolidSphere(0.05f, 10, 10);
        glPopMatrix();

        // Atualiza a posição Y (queda)
        snowflakes[i].y -= snowflakes[i].speed;

        // Reaparece no topo se ultrapassar o chão
        if (snowflakes[i].y < -1.0f) {
            snowflakes[i].y = 25.0f; // Reaparece no topo
            snowflakes[i].x = (std::rand() % 100 - 50) / 5.0f; // Nova posição X
            snowflakes[i].z = (std::rand() % 100 - 50) / 5.0f; // Nova posição Z
        }
    }
}

void drawNonStaticScenario() {
    drawSnowflakes();
}
