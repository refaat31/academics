#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

#define left_fork (LEFT + 1)
#define right_fork (phnum + 1)

#define leftForkIndex (phnum % N)
#define rightForkIndex (phnum+1) %N

//int j=0;
int flag[N] = {0};
char status[][10] = {"EATING", "HUNGRY", "THINKING"};

int state[N] = {1, 1, 1, 1, 1};
int phil[N] = {0, 1, 2, 3, 4};

sem_t mutex;
sem_t S[N];
sem_t forks[N];

void showStatus()
{

    printf("\n");
    for (int k = 0; k < 5; k++)
    {
        if (flag[k] != 0)
            printf("Philosopher %d is %s \t", k + 1, status[state[k]]);
    }
    printf("\n");
    sleep(3);
}


// take up chopsticks
void take_fork(int phnum)
{
    

    if ((phnum + 1) % 2 == 0)
    {
        sem_wait(&forks[rightForkIndex]);
        sem_wait(&forks[leftForkIndex]);
    }
    else
    {
        sem_wait(&forks[leftForkIndex]);
        sem_wait(&forks[rightForkIndex]);
    }

    sem_wait(&mutex);

    // state that hungry, start checking for unoccupied forks
    state[phnum] = HUNGRY;

    showStatus();

    //once the philosopher has the forks, he can start eating

    state[phnum] = EATING;

    sleep(2);

    printf("\nPhilosopher %d takes fork %d and %d\n",
           phnum + 1, left_fork, right_fork);

    showStatus();

    sem_post(&mutex);



    sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("\nPhilosopher %d putting fork %d and %d down\n",
           phnum + 1, left_fork, right_fork);

    showStatus();

    sem_post(&forks[leftForkIndex]);
    sem_post(&forks[rightForkIndex]);
    sem_post(&mutex);
}

void *philospher(void *num)
{

    int j = 0;
    while (j < 3)
    {

        int *i = num;

        sleep(1);

        take_fork(*i);

        sleep(0);

        put_fork(*i);

        printf("\n\n");
        j++;
    }
}

int main()
{

    int i;
    pthread_t thread_id[N];

    struct timeval stop, start;
    gettimeofday(&start, NULL);

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    // initialize the fork semaphores

    for (i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (i = 0; i < N; i++)
    {

        // create philosopher processes
        pthread_create(&thread_id[i], NULL,
                       philospher, &phil[i]);
        gettimeofday(&stop, NULL);

        printf("\nAt %lu micro-seconds Philosopher %d is created and he starts thinking\n",
               ((stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec), i + 1);
        flag[i] = 1;
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}
