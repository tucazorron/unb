/*
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Estrutura de Dados - 2018/2
Aluno(a): Artur Filgueiras Scheiba Zorron
Matricula: 180013696
Turma: A
Versao do compilador: gcc version 7.3.0 (Ubuntu 7.3.0-27ubuntu1~18.04)
*/

//----------------------------------------------------------------

// bibliotcas incluidas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "naruto.h"

//----------------------------------------------------------------

// torna o jogo todo amarelo
#define BOLDYELLOW "\033[1m\033[33m"

//----------------------------------------------------------------

// funcao main do jogo
int main() {
    printf(BOLDYELLOW);
    menu();
    return 0;
}
