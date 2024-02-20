// IO
#include <stdio.h>

// Forking
#include <sys/types.h>
#include <unistd.h>

// Exit
#include <stdlib.h>

// Signals
#include <signal.h>

// Boolean
#define true 1
#define false 0
typedef short bool;

// Macros
#define CHILD(pid) pid == 0
#define CHILD_COUNT 10

// Functions' signatures
pid_t safeFork();
void executeChildRoutine(int parentId);
void handle_SIGUSR1(int signal);
void handle_SIGCHLD(int signal);
void handle_SIGUSR2(int signal);

// Tracks children's notifications
int childrenNotifications = 0;

// The parent will create 10 processes, and each process will send a SIGUSR1 signal to the parent
// After all 10 signals were received, the parent notifies the children with the signal SIGUSR2, and they terminate
// After all children have terminated (parent tracks this with the SIGCHLD signal), the parent process terminates too
int main()
{
    // Set up handling of SIGUSR1 signals
    signal(SIGUSR1, handle_SIGUSR1);

    // Set up handling of SIGCHLD signals
    signal(SIGCHLD, handle_SIGCHLD);

    // Memorize own id
    pid_t parentId = getpid();

    // Will hold the children's pids
    pid_t childrenIds[CHILD_COUNT];

    // Spawn children
    for (int i = 0; i < CHILD_COUNT; i++)
    {
        pid_t forkResult = safeFork();

        // If is child, execute children's routine
        if (CHILD(forkResult))
        {
            executeChildRoutine(parentId);

            // Child must have already exited
            printf("ERROR: child hasn't terminated properly\n");
            exit(-1);
        }

        // If is parent, store the child's pid
        childrenIds[i] = forkResult;

        // Wait for child notification
        sleep(1);
    }

    // After spawning all children, parent must wait until all of them have sent a notification
    while (childrenNotifications < CHILD_COUNT)
        sleep(10);

    getchar();
    
    // Afterwards, parent must notify children back
    for (int i = 0; i < CHILD_COUNT; i++)
    {
        // Send the notification
        kill(childrenIds[i], SIGUSR2);

        // Wait for child termination
        sleep(1);
    }

    // Now parent must wait until all children have terminated
    while (childrenNotifications > 0)
        sleep(10);

    // Parent may terminate
    return 0;
}

// This function will handle the notifications of the children
void handle_SIGUSR1(int signal)
{
    printf("Received %d child notification\n", ++childrenNotifications);
}

// This function will handle the exit signals of the children
void handle_SIGCHLD(int signal)
{
    printf("Received %d child exit signal\n", 10 - (--childrenNotifications));
}

// This function will handle the parent's notification to each child, when they must terminate
void handle_SIGUSR2(int signal)
{
    exit(0);
}

// The children's routine
void executeChildRoutine(int parentId)
{
    // Set up handling of parent's notification
    signal(SIGUSR2, handle_SIGUSR2);

    // Notify parent
    kill(parentId, SIGUSR1);

    // Wait indefinitely — when parent notifies, the handler will terminate this process
    while (true)
        sleep(5);
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
        exit(0);
    }

    return forkResult;
}