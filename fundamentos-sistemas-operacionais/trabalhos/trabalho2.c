// IO
#include <stdio.h>

// Forking
#include <sys/types.h>
#include <unistd.h>

// Exit
#include <stdlib.h>

// Signals
#include <signal.h>

// Time
#include <time.h>

// Wait
#include <sys/wait.h>

// Boolean
#define true 1
#define false 0
typedef short bool;

// Macros
#define CHILD(pid) pid == 0
#define CHILD_COUNT 5
#define RANDOM_RANGE(min, max) (rand() % (max - min)) + min
#define SET_RANDOM_SEED() srand(time(NULL))

// Define o tipo do filho
typedef struct
{
    // pid do filho
    pid_t id;

    // Numero aleatorio gerado para o filho
    int time;

    // Tempo no qual o filho foi criado
    time_t spawnTime;
} Child;

// Functions' signatures
void childRoutine();
void setRandomSeed();
void sortChildren(Child children[]);
void handleSIGALRM(int signal);
int compareChildren(const void *a, const void *b);
pid_t safeFork();

// Array que guarda os filhos
Child children[CHILD_COUNT];

// Indice do proximo filho a ser despertado
int nextChildToWake = 0;

int main()
{
    // Gera uma seed pro rand()
    SET_RANDOM_SEED();

    for (int i = 0; i < CHILD_COUNT; i++)
    {
        // Gera o numero aleatorio
        int childTime = RANDOM_RANGE(2, 8);

        // Gera um filho
        pid_t forkResult = safeFork();

        // Registra o tempo em que foi criado
        time_t spawnTime = time(NULL);

        // Verifica se eh o filho: o filho executa a rotina e morre
        if (CHILD(forkResult))
        {
            childRoutine();

            printf("ERRO: o processo ja deveria ter morrido!\n");
            exit(-1);
        }

        // A partir daqui, sabemos que o processo eh o pai

        // Imediatamente parar o filho
        kill(forkResult, SIGSTOP);

        // Guardar o pid e time do filho
        children[i].id = forkResult;
        children[i].time = childTime;
        children[i].spawnTime = spawnTime;

        // Imprimir informacoes
        printf("Iteração i = %d:\n\ttime_i = %d\n\tpid do filho gerado = %d\n", i, childTime, forkResult);
    }

    // Ordena os filhos por ordem de menor time para maior time
    sortChildren(children);

    // Indica o handler para o sinal SIGALRM
    signal(SIGALRM, handleSIGALRM);

    // Prepara o alarme para ressucitar cada um dos filhos
    getchar();
    // O handler do alarme automaticamente inicia o proximo alarme quando este disparar, e faz isso apra cada filho
    alarm(children[0].time);

    // // Prepara o alarme para ressucitar cada um dos filhos
    // for (int i = 0; i < CHILD_COUNT; i++)
    // {
    //   // Pede para o SO nos enviar um SIGALRM daqui a time segundos
    //   alarm(children[i].time);
    // }

    // // Registra quanto tempo o processo pai ja dormiu
    // int timeSlept = 0;

    // // Como os filhos estao em ordem crescente de tempo de espera, basta dormir para cada filho
    // for (int i = 0; i < CHILD_COUNT; i++)
    // {
    //   // Quanto tempo vai dormir nessa iteracao
    //   int sleepTime = children[nextChildToWake].time - timeSlept;

    //   // Dorme
    //   sleep(sleepTime);

    //   // Registra o tempo que dormiu
    //   timeSlept += sleepTime;

    //   // Pede para o filho voltar a executar
    //   kill(children[nextChildToWake++].id, SIGCONT);
    // }

    // Guarda o status dos filhos que terminam
    int childStatus;

    // Espera o fim da execucao de cada filho
    for (int i = 0; i < CHILD_COUNT; i++)
    {
        if (waitpid(children[i].id, &childStatus, 0) == -1)
        {
            printf("Erro ao esperar o fim da execução de um filho.\n");
            exit(-1);
        }

        // Encontrar o turnaround
        time_t childTurnaround = time(NULL) - children[i].spawnTime;

        // Verifica que o filho nao deu erro
        if (!WIFEXITED(childStatus))
        {
            printf("Um dos processos filhos terminou com erro!\n");
            exit(-1);
        }

        // Imprime o turnaround
        printf("Filho %d terminou a execução com turnaround de %ld\n", i, childTurnaround);
    }

    // Informa fim da execucao
    printf("Todos os filhos ja encerraram, terminado processo pai.\n");

    return 0;
}

void childRoutine()
{
    long int i;

    for (long int i = 0; i < 500000000; i++)
        ; /* busy waiting com 100% de CPU – demora cerca de 80s */

    // Imprime seu pid
    printf("Filho de pid %d terminou a execução.\n", getpid());

    exit(0);
}

void handleSIGALRM(int signal)
{
    // Tempo a esperar para acordar o proximo filho
    int alarmTime = 0;

    do
    {
        // Pede para o filho voltar a executar
        kill(children[nextChildToWake++].id, SIGCONT);

        // Verifica se todos os filhos ja foram
        if (nextChildToWake == CHILD_COUNT)
            return;

        // Prepara o alarme do proximo filho
        alarmTime = children[nextChildToWake].time - children[nextChildToWake - 1].time;
    } while (alarmTime == 0);

    alarm(alarmTime);
}

// Forks, checks that fork was successfull, and return true for child and
pid_t safeFork()
{
    // Create child
    pid_t forkResult = fork();

    // Ensure not failed
    if (forkResult == -1)
    {
        printf("Falha ao criar novo processo\n");
        exit(-1);
    }

    return forkResult;
}

void sortChildren(Child children[])
{
    // Usamos o qsort para ordenar os filhos
    qsort(children, CHILD_COUNT, sizeof(Child), compareChildren);
}

int compareChildren(const void *a, const void *b)
{
    return (*(Child *)a).time - (*(Child *)b).time;
}