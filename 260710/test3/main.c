#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "pthread.h"

int cmd_cache = 0;
int exit_flag = 0;

pthread_mutex_t lock;
pthread_cond_t cond;

void *pthreadA(void *arg)
{
    (void)arg;
    while(1)
    {
        pthread_mutex_lock(&lock);
        while(cmd_cache == 0 && exit_flag==0)
        {
            pthread_cond_wait(&cond,&lock);
        }

        if(exit_flag ==1)
        {
            pthread_mutex_unlock(&lock);
            break;
        }

        printf("消费者处理指令：%d\n", cmd_cache);

        cmd_cache = 0;
        pthread_mutex_unlock(&lock);
    }


    return NULL;
}



int main(void)
{
    int ret;
    pthread_t tidA;
    pthread_mutex_init(&lock,NULL);

    ret = pthread_create(&tidA,NULL,pthreadA,NULL);

    if(ret!=0)
    {
        perror("error");
        return -1;
    }

    for(int i=1;i<=3;i++)
    {
        sleep(2);
        pthread_mutex_lock(&lock);
        cmd_cache =i;
        printf("生产者放入指令：%d\n", cmd_cache);
        pthread_mutex_unlock(&lock);
        pthread_cond_signal(&cond);

    }

    pthread_mutex_lock(&lock);
    exit_flag = 1;
    pthread_mutex_unlock(&lock);

    pthread_cond_signal(&cond);
    pthread_join(tidA,NULL);


    return 0;
}


