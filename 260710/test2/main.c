#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

int run_flag = 1;
pthread_mutex_t lock;

int dev_buf[10];


void *pthreadA(void *arg)
{
    (void)arg;
    while(run_flag==1)
    {
        pthread_mutex_lock(&lock);
        for(int i=0;i<5;i++)
        {
            dev_buf[i] = i;
        }
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *pthreadB(void *arg)
{
    (void)arg;
    while(run_flag==1)
    {
        pthread_mutex_lock(&lock);
        for(int i=5;i<10;i++)
        {
            dev_buf[i] = i;
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *read_buf(void *arg)
{
    (void)arg;
    while(run_flag==1)
    {
        for(int i=0;i<10;i++)
        {
            pthread_mutex_lock(&lock);
            printf("buf 分别为%d\n",dev_buf[i]);
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}


int main()
{
    pthread_t tidA,tidB,tidC;
    int ret;

    pthread_mutex_init(&lock, NULL);
    ret = pthread_create(&tidA,NULL,pthreadA,NULL);
    if(ret<0)
    {
        perror("error");
        return -1;
    }
    ret = pthread_create(&tidB,NULL,pthreadB,NULL);
    if(ret<0)
    {
        perror("error");
        return -1;
    }
    ret = pthread_create(&tidC,NULL,read_buf,NULL);
    if(ret<0)
    {
        perror("error");
        return -1;
    }

    sleep(5);
    run_flag = 0;

    pthread_join(tidA,NULL);
    pthread_join(tidB,NULL);
    pthread_join(tidC,NULL);
}   




