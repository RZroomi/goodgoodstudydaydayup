#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"


int run_flag =0;

pthread_mutex_t lock;
pthread_cond_t  cond;


typedef struct ADC
{
    int id;
    int data;
};
struct ADC adc1 = {1,0};
struct ADC adc2 = {2,0};
struct ADC adc3 = {3,0};

void *pthread_write(void *arg)
{
    (void)arg;
    while(run_flag==0)
    {
        for(int i=0;i<3;i++)
        {
            pthread_mutex_lock(&lock);
            sleep(1);//每隔一秒写一次
            adc1.data =i;
            printf("写入一个data\n");
            pthread_cond_signal(&cond);
            pthread_mutex_unlock(&lock);
        }
    }
    return NULL;
}

void *pthread_read(void *arg)
{
    (void)arg;
    while(run_flag==0)
    {
        pthread_mutex_lock(&lock);

        while(adc1.data==0 && run_flag==0)
        {
            pthread_cond_wait(&cond,&lock);
        }

        printf("adc1的ID=%d,adc1的data=%d\n",adc1.id,adc1.data);
        printf("adc2的ID=%d,adc2的data=%d\n",adc2.id,adc2.data);
        printf("adc3的ID=%d,adc3的data=%d\n",adc3.id,adc3.data);

        pthread_mutex_unlock(&lock);

    }
    return NULL;
}

int main()
{
    int ret;
    pthread_t tidA,tidB;

    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_create(&tidA,NULL,pthread_write,NULL);
    if(ret != 0)
    {
       perror("error");
       return -1; 
    }
    pthread_create(&tidB,NULL,pthread_read,NULL);
    if(ret != 0)
    {
       perror("error");
       return -1; 
    }

    sleep(6);
    run_flag=1;

    pthread_join(tidA,NULL);
    pthread_join(tidB,NULL);

    return 0;
}