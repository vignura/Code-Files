// C program to implement cond(), signal()
// and wait() functions
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
 
// Declaration of thread condition variable
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
 
// declaring mutex
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
 
int done = 1;
 
// Thread function
/*void* foo()
{
    pthread_t tid = pthread_self();

    // acquire a lock
    pthread_mutex_lock(&lock);
    if (done == 1) {
 
        // let's wait on condition variable cond1
        done = 2;
        printf("%lu:: Waiting on condition variable cond1\n", tid);
        pthread_cond_wait(&cond1, &lock);
    }
    else {
 
        // Let's signal condition variable cond1
        printf("%lu:: Signaling condition variable cond1\n", tid);
        pthread_cond_signal(&cond1);
    }
 
    // release lock
    pthread_mutex_unlock(&lock);
 
    printf("%lu:: Returning thread\n", tid);
 
    return NULL;
}*/
 
void* waiting_thread()
{
    pthread_t tid = pthread_self();

    // acquire a lock
    pthread_mutex_lock(&lock);
    printf("%s: Waiting on condition variable cond1\n", __func__);
    pthread_cond_wait(&cond1, &lock);
 
    // release lock
    pthread_mutex_unlock(&lock);
    printf("%s: Returning thread\n", __func__);
 
    return NULL;
}
void* signalling_thread()
{
    // Let's signal condition variable cond1
    printf("%s: Signaling condition variable cond1\n", __func__);
    pthread_mutex_lock(&lock);
    int ret = pthread_cond_signal(&cond1);
    if(ret != 0)
    {
        perror("pthread_cond_signal");
    }
    pthread_mutex_unlock(&lock);
    printf("%s: Returning thread\n", __func__);
}

// Driver code
int main()
{
    pthread_t tid1, tid2;
 
    // Create thread 1
    pthread_create(&tid1, NULL, waiting_thread, NULL);
 
    // sleep for 1 sec so that thread 1
    // wou%lu: get a chance to run first
    sleep(1);
 
    // Create thread 2
    pthread_create(&tid2, NULL, signalling_thread, NULL);
 
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
 
    return 0;
}