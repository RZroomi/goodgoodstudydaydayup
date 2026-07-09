#include "stdio.h"
#include "unistd.h"
#include "pthread.h"


void *pthreadA(void *arg)
{
    (void)arg;
    for(int i=0;i<3;i++)
    {
        printf("我是线程A,第%d次打印\n",i);
        sleep(1);
    }
    return NULL;
}

void *pthreadB(void *arg)
{
    (void)arg;
    for(int i=0;i<3;i++)
    {
        printf("我是线程B,第%d次打印\n",i);
        sleep(1);
    }
    sleep(1);
    return NULL;
}

int main(void)
{
    pthread_t tidA,tidB;
    int ret;

    ret = pthread_create(&tidA,NULL,pthreadA,NULL);
    if(ret !=0)
    {
        perror("线程A创建失败\n");
        return -1;
    }

    ret = pthread_create(&tidB,NULL,pthreadB,NULL);
    if(ret !=0)
    {
        perror("线程B创建失败\n");
        return -1;
    }

    pthread_join(tidA,NULL);
    pthread_join(tidB,NULL);

}


