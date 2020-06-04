#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

struct lock_t *spinLock;
static int totalNumber;
static int passNumber = 0;
static int threadNumber;
static int passTo = 0;

void* threadFunction(void* arg){
    int tid = (int)arg;
    while(passNumber < totalNumber){
        lock_acquire(spinLock);
        if(tid == passTo){
            passTo = tid + 1 >= threadNumber ? 0 : tid + 1;
            printf(1, "Pass Number no: %d, Thread %d is passing the token to thread %d\n", ++passNumber, tid, passTo);
        }
        lock_release(spinLock);
        sleep(10);
    }
    exit();
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf(1, "Frisbee needs 2 extra elements!!\n");
    }
    int i = 0;
    int tid[4] = {0, 1, 2, 3};
    threadNumber = atoi(argv[1]);
    totalNumber = atoi(argv[2]);

    lock_init(spinLock);

    for(i = 0; i < threadNumber; i++){
        //Using a array to give the threadID to each threads
        //in order to prevent race condition.
        //printf(1,"currently giving %d\n", tid[i]);
        thread_create(threadFunction, (void*)tid[i]);
    }

    for(i = 0; i < threadNumber; i++){
        wait();
    }
    printf(1, "\nSimulation of Frisbee game has finished, %d rounds were played in total!\n", totalNumber);
    exit();
}