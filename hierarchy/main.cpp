#include <GL/glut.h>

#include <cmath>
#include <iostream>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

int ombro = 0, cotovelo = 0;
int yRotation = 0;  // Variable to store rotation angle for the whole model
float cameraAngleX = 0.0f, cameraAngleY = 0.0f, cameraDistance = -5.0f; // Camera position and orientation

float sliderValue = 0, sliderStartX = 0;
bool sliderPressed = false;

int mouseX = 0, mouseY = 0;
bool mousePressed = false;
GLuint texID;

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

void inicializa() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    carregarTextura("textura/madeira.png", texID);
}
void drawCylinder(int segments, float radius, float height) {
    int mode = GL_QUADS;
    
    for (int i = 0; i < segments; i++) {
        glBindTexture(GL_TEXTURE_2D, texID);
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

void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    while (*text) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *text);
        text++;
    }
}

void drawText(float x, float y, std::string text) {
    glRasterPos2f(x, y);

    for (auto c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

}


void drawHUD() {
    // Switch to 2D orthographic mode to render HUD
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);  // Setup orthographic projection

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // // Draw some text for the HUD
    // drawText(0.05f, 0.95f, "Rotation: " + std::to_string(ombro));

    // // You can add more HUD elements here like stats, instructions, etc.
    // // For example, draw another text element
    // drawText(0.05f, 0.90f, "Press 'o' to rotate shoulder");

    // Draw the slider background (track)
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray for the track
    glBegin(GL_QUADS);
        glVertex2f(0.2f, 0.1f);
        glVertex2f(0.8f, 0.1f);
        glVertex2f(0.8f, 0.12f);
        glVertex2f(0.2f, 0.12f);
    glEnd();

    // Draw the slider knob (handle)
    glColor3f(1.0f, 0.0f, 0.0f); // Red color for the knob
    float knobX = 0.2f + (sliderValue * 0.6f); // Map slider value to X position
    glBegin(GL_QUADS);
        glVertex2f(knobX - 0.02f, 0.08f);
        glVertex2f(knobX + 0.02f, 0.08f);
        glVertex2f(knobX + 0.02f, 0.14f);
        glVertex2f(knobX - 0.02f, 0.14f);
    glEnd();

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}


// void display() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();

//     // Apply camera transformations based on mouse-controlled camera
//     glTranslatef(0.0, 0.0, cameraDistance);
//     glRotatef(cameraAngleX, 1.0, 0.0, 0.0);  // Rotate around X-axis (up/down)
//     glRotatef(cameraAngleY, 0.0, 1.0, 0.0);  // Rotate around Y-axis (left/right)

//     // Apply the rotation for the whole model around the vertical axis (y-axis)
//     glPushMatrix();
//         glTranslatef(-1.0, 0.0, 0.0);
//         glRotatef((float)ombro, 0.0, 0.0, 1.0);
//         glTranslatef(1.0, 0.0, 0.0);

//         glPushMatrix();
//             drawCylinder(16, 0.5, 2.0);
//         glPopMatrix();

//         glTranslatef(1.0, 0.0, 0.0);
//         glRotatef((float)cotovelo, 0.0, 0.0, 1.0);
//         glTranslatef(1.0, 0.0, 0.0);

//         glPushMatrix();
//             // glScalef(2.0, 0.4, 1.0);
//             drawCylinder(16, 0.5, 2.0);
//             // glutWireCube(1.0);
//         glPopMatrix();

//     glPopMatrix();

//     drawHUD();

//     glutSwapBuffers();
// }

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Apply camera transformations based on mouse-controlled camera
    glTranslatef( 0.0, -1.5, 0.0);
    glTranslatef(0.0, 0.0, cameraDistance);
    glRotatef(cameraAngleX, 1.0, 0.0, 0.0);  // Rotate around X-axis (up/down)
    glRotatef(cameraAngleY, 0.0, 1.0, 0.0);  // Rotate around Y-axis (left/right)

    // Apply the rotation for the whole model around the vertical axis (y-axis)
    glPushMatrix();
        // Rotate the bottom cylinder (shoulder)
        // glTranslatef(-1.0, 0.0, 0.0);  // Move to the center of the bottom cylinder
        glRotatef((float)ombro, 0.0, 0.0, 1.0);  // Rotate around the Z-axis
        // glTranslatef(1.0, 0.0, 0.0);  // Move back to the original position

        glPushMatrix();
            // Draw the bottom cylinder (shoulder)
            glColor3f(1.0, 1.0, 1.0);
            drawCylinder(16, 0.5, 2.0);
            
            glTranslatef(0,2,-0.625);
            glRotatef(90, 1, 0, 0);
            glPushMatrix();
                glColor3f(0.2, 0.2, 0.2);
                drawCylinder(16, 0.625, 2*0.625); // Join cylinder
            glPopMatrix();
            glColor3f(1.0, 1.0, 1.0);
        glPopMatrix();

        // Translate to the top cylinder (elbow), it will follow the bottom cylinder's rotation
        glTranslatef(0.0, 2.0, 0.0);  // Move to the top of the bottom cylinder

        // Rotate the top cylinder (elbow) independently
        // glRotatef((float)cotovelo, 0.0, 0.0, 1.0);  // Rotate the top cylinder around its own axis
        glRotatef(sliderValue * 180 - 90, 0.0, 0.0, 1.0);  // Rotate the top cylinder around its own axis

        glPushMatrix();
            // Draw the top cylinder (elbow)
            drawCylinder(16, 0.5, 2.0);
        glPopMatrix();

    glPopMatrix();

    // Draw the HUD on top of the 3D scene
    drawHUD();

    glutSwapBuffers();
}


void teclado(unsigned char tecla, int x, int y)
{
    switch (tecla)
    {
        case 'o':
            ombro = (ombro + 5) % 360;
            glutPostRedisplay();
            break;  
        case 'O':
            ombro = (ombro - 5) % 360;
            glutPostRedisplay();
            break;  
        case 'c':
            cotovelo = (cotovelo + 5) % 360;
            glutPostRedisplay();    
            break;  
        case 'C':
            cotovelo = (cotovelo - 5) % 360;
            glutPostRedisplay();
            break;

        case 'y':  // When 'y' is pressed, rotate the whole model around the y-axis
            yRotation = (yRotation + 5) % 360;
            glutPostRedisplay();
            break;

        case '=':
        case '+':
            cameraDistance += 0.2f;  // Zoom in
            if (cameraDistance > -1.0f) cameraDistance = -1.0f;
            if (cameraDistance < -20.0f) cameraDistance = -20.0f;
            glutPostRedisplay();

            break;
        case '-':
            cameraDistance -= 0.2f;  // Zoom out
            if (cameraDistance > -1.0f) cameraDistance = -1.0f;
            if (cameraDistance < -20.0f) cameraDistance = -20.0f;
            glutPostRedisplay();

            break;
        case 27:
            exit(0);
            break;
    }   
}

void reshape(int largura, int altura) {
    glViewport(0, 0, largura, altura);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(65.0, (float)largura / (float)altura, 1.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// // Mouse button press callback function to start/stop camera rotation
// void mouse(int button, int state, int x, int y) {
//     if (button == GLUT_LEFT_BUTTON) {
//         if (state == GLUT_DOWN) {
//             mousePressed = true;
//             mouseX = x;
//             mouseY = y;
//         } else {
//             mousePressed = false;
//         }
//     }
// }

// // Mouse motion callback function for dragging the mouse to rotate the camera
// void motion(int x, int y) {
//     if (mousePressed) {
//         // Calculate the difference between the current and the previous mouse positions
//         float deltaX = x - mouseX;
//         float deltaY = y - mouseY;

//         // Update camera rotation angles
//         cameraAngleY += deltaX * 0.1f;  // Rotate around the Y-axis (horizontal)
//         cameraAngleX += deltaY * 0.1f;  // Rotate around the X-axis (vertical)

//         // Limit the vertical angle to avoid flipping
//         if (cameraAngleX > 90.0f) cameraAngleX = 90.0f;
//         if (cameraAngleX < -90.0f) cameraAngleX = -90.0f;

//         mouseX = x;
//         mouseY = y;

//         glutPostRedisplay();
//     }
// }

// Mouse button press callback function to start/stop slider interaction
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            // Convert mouse coordinates to normalized screen coordinates
            float normX = (float)x / glutGet(GLUT_WINDOW_WIDTH);
            float normY = (glutGet(GLUT_WINDOW_HEIGHT) - (float)y) / glutGet(GLUT_WINDOW_HEIGHT);

            // Check if the click was within the slider range
            if (normX >= 0.2f && normX <= 0.8f && normY >= 0.08 && normY <= 0.14) { // Slider area
                sliderPressed = true;
                sliderStartX = x; // Record the starting mouse position for dragging
            }
            else {
                mousePressed = true;
                mouseX = x;
                mouseY = y;
            }

        } else {
            sliderPressed = false; // Release slider when mouse button is released
            mousePressed = false;
        }
    }
}

// Mouse motion callback function for dragging the slider
void motion(int x, int y) {
    if (sliderPressed) {
        // Calculate how much the mouse has moved horizontally
        float deltaX = (float)(x - sliderStartX) / glutGet(GLUT_WINDOW_WIDTH);

        // Update slider value based on mouse motion (clamped between 0.0 and 1.0)
        sliderValue += deltaX;
        if (sliderValue > 1.0f) sliderValue = 1.0f;
        if (sliderValue < 0.0f) sliderValue = 0.0f;

        sliderStartX = x; // Update the starting mouse position for the next movement

        glutPostRedisplay(); // Redraw the scene to update the slider
    }

    else if (mousePressed) {
        // Calculate the difference between the current and the previous mouse positions
        float deltaX = x - mouseX;
        float deltaY = y - mouseY;

        // Update camera rotation angles
        cameraAngleY += deltaX * 0.1f;  // Rotate around the Y-axis (horizontal)
        cameraAngleX += deltaY * 0.1f;  // Rotate around the X-axis (vertical)

        // Limit the vertical angle to avoid flipping
        if (cameraAngleX > 90.0f) cameraAngleX = 90.0f;
        if (cameraAngleX < -90.0f) cameraAngleX = -90.0f;

        mouseX = x;
        mouseY = y;

        glutPostRedisplay();
    }
}


// Mouse wheel callback to zoom in and out
void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0) {
        cameraDistance += 0.2f;  // Zoom in
    } else {
        cameraDistance -= 0.2f;  // Zoom out
    }

    // Limit the camera distance
    if (cameraDistance > -1.0f) cameraDistance = -1.0f;
    if (cameraDistance < -20.0f) cameraDistance = -20.0f;

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Modelos Hierarquicos");

    inicializa();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(teclado);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    //glutMouseWheelFunc(mouseWheel);

    glutMainLoop();

    return 0;
}
