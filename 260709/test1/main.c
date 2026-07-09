#include "stdio.h"
#include "unistd.h"
#include "pthread.h"


void *child_func(void *arg)
{
    (void)arg;
    printf("我是子线开始干活\n");
    sleep(3);
    printf("子线程不干了C\n");
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret;

    ret = pthread_create(&tid,NULL,child_func,NULL);
    if(ret !=0)
    {
        perror("线程创建失败\n");
        return -1;
    }

    printf("我是主线程我就干一秒\n");
    sleep(1);

    pthread_join(tid,NULL);

    
    printf("都不干了\n");
}


