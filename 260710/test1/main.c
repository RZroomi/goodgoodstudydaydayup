#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

int total;
pthread_mutex_t lock;


void *pthreadA(void *arg)
{
    (void)arg;
    for(int i=0;i<50000;i++)
    {
        pthread_mutex_lock(&lock);
        total++;
        pthread_mutex_unlock(&lock);
        printf("total = %d\n",total);
    }
    return NULL;
}

void *pthreadB(void *arg)
{
    (void)arg;
    for(int i=0;i<50000;i++)
    {
        pthread_mutex_lock(&lock);
        total++;
        pthread_mutex_unlock(&lock);
        printf("total = %d\n",total);
    }
    return NULL;
}

int main()
{
    pthread_t tidA,tidB;
    int ret;
    ret = pthread_create(&tidA,NULL,pthreadA,NULL);
    if(ret<0)
    {
        perror("error");
        return -1;
    }
    ret = pthread_create(&tidB,NULL,pthreadA,NULL);
    if(ret<0)
    {
        perror("error");
        return -1;
    }

    pthread_join(tidA,NULL);
    pthread_join(tidB,NULL);
}   




