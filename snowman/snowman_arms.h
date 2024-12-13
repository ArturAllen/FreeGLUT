#ifndef SNOWMAN_ARMS_H
#define SNOWMAN_ARMS_H

extern int ombroEsquerdo, cotoveloEsquerdo, maoEsquerda;
extern int ombroDireito, cotoveloDireito, maoDireita;

void initTextures();
//void carregarTextura();
void drawSnowmanArms(GLuint texId);

void setBracoEsquerdo(int ombro, int cotovelo, int mao);

void setBracoDireito(int ombro, int cotovelo, int mao);

#endif
