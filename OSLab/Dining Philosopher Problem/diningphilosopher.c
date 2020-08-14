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

//int j=0;
int flag[N] = {0};
char status[][10] = {"EATING", "HUNGRY", "THINKING"};

int state[N]={1,1,1,1,1};
int phil[N] = { 0, 1, 2, 3, 4 };

sem_t mutex;
sem_t S[N];

void showStatus()
{

        printf("\n");
        for(int k=0; k<5; k++)
        {
            if(flag[k]!=0)
                printf("Philosopher %d is %s \t", k+1, status[state[k]]);
        }
        printf("\n");
        sleep(3);
}


void test(int phnum)
{
    if (state[phnum] == HUNGRY
        && state[LEFT] != EATING
        && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;

        sleep(2);

        printf("\nPhilosopher %d takes fork %d and %d\n",
                      phnum + 1, LEFT + 1, phnum + 1);

        showStatus();

        // sem_post(&S[phnum]) has no effect
        // during takefork
        // used to wake up hungry philosophers
        // during putfork
        sem_post(&S[phnum]);
    }
}

// take up chopsticks
void take_fork(int phnum)
{

    sem_wait(&mutex);

    // state that hungry
    state[phnum] = HUNGRY;

    showStatus();

    // eat if neighbours are not eating
    test(phnum);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);

    sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("\nPhilosopher %d putting fork %d and %d down\n",
           phnum + 1, LEFT + 1, phnum + 1);

    showStatus();

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* philospher(void* num)
{

    int j = 0;
    while (j<3) {

        int* i = num;

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

    for (i = 0; i < N; i++) {

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
