#include "stdio.h"
#include "unistd.h"
#include "pthread.h"

int run_flag =1;

typedef struct
{
    int num;
    char name[20];
}dev;


void *child_func(void *arg)
{
    dev *d1 = (dev*)arg;
    while(run_flag==1)
    {
        printf("dev的id=%d,name=%s\n",d1->num,d1->name);
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t tid;
    int ret;
    dev d={1,"xixi"};
    
    ret = pthread_create(&tid,NULL,child_func,&d);
    if(ret !=0)
    {
        perror("线程创建失败");
        return -1;
    }

    sleep(3);
    run_flag =0;
    pthread_join(tid,NULL);

}


