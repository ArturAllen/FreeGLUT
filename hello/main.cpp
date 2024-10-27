//g++ -Wall -Iinclude -g main.cpp -o main.exe -Llib -lopengl32 -lglu32 -lfreeglut
#include <GL/glut.h>

#include <iostream>
#include <cmath>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

// Retorna quantidade de segundos desde a inicialização em formato fracionário
// (simplifica controle de animações)
float getElapsedSeconds() {
    return (float)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
}

class Float2 {
    public:
    float x, y;

    Float2() {}
    Float2(float _x, float _y) {
        x = _x;
        y = _y;
    }

    void Rotate(float angle) {
        float newX = x * cosf(angle) - y * sinf(angle);
        float newY = x * sinf(angle) + y * cosf(angle);

        x = newX;
        y = newY;
    }

    void Translate(Float2 t) {
        x += t.x;
        y += t.y;
    }

    void Scale(float factor) {
        x *= factor;
        y *= factor;
    }
};

// Coordenadas do Ponteiro do Mouse na tela
int pointerX = WINDOW_WIDTH/2;
int pointerY = WINDOW_HEIGHT/2;

void drawSquare(float angle) {
    std::vector<Float2> points;
    points.push_back(Float2(-0.5f, -0.5f));
    points.push_back(Float2( 0.0f, -1.0f));
    points.push_back(Float2( 0.5f, -0.5f));
    points.push_back(Float2( 0.5f, 0.5f));
    points.push_back(Float2(-0.5f, 0.5f));

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON); // Polígono convexo
    
    for (auto v : points) {
        // Transformações geométricas
        // A ordem das operações importa
        // A escala e a rotação operam a partir da origem
        v.Rotate(angle);
        v.Scale(100);
        v.Translate(Float2(pointerX, pointerY));

        glVertex2f(v.x, v.y);
    }

    glEnd();
}

void followPointer(int x, int y) {
    pointerX = x;
    pointerY = y;
}

void display() {
    static const float angularVelocity = M_PI; 

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT);
    
    // Chama a função para desenhar um quadrado, passando o ângulo calculado com base no tempo decorrido.
    drawSquare(getElapsedSeconds() * angularVelocity);
    
    glFlush();

    glutPostRedisplay(); // chama a função de display novamente
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
    
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    
    glutCreateWindow("Primeiro exemplo com FreeGLUT");
	
    // Ajusta a origem do sistema de coordenadas para o canto superior esquerdo
    glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
    gluOrtho2D(0,WINDOW_WIDTH, WINDOW_HEIGHT, 0);
    
    glutDisplayFunc(display);
    glutMotionFunc(followPointer); // Chamada quando o mouse se move clicado
    glutPassiveMotionFunc(followPointer); // Chamada quando o mouse se move não clicado
    
    glutMainLoop();
  
    return 0;
}