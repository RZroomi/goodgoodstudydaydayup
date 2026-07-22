#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

typedef struct
{
	int fd;
	int dev_id;
	int period_ms;
	char dev_name[32];
}DevInfo

int uart_init(const char *dev)
{
    int fd = open(dev, O_RDWR | O_NOCTTY);
    if (fd < 0)
    {
        perror(dev);
        return -1;
    }
    struct termios opt;
    tcgetattr(fd, &opt);
    cfsetispeed(&opt, B9600);
    cfsetospeed(&opt, B9600);
    opt.c_cflag |= CREAD | CLOCAL;
    opt.c_cflag &= ~PARENB & ~CSTOPB & ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_lflag &= ~(ICANON | ECHO | ISIG);
    opt.c_oflag &= ~OPOST;
    tcsetattr(fd, TCSANOW, &opt);
    return fd;
}


void *sensor_collect_pthread(void *arg)
{
	DevInfo *dev=(DevInfo *)arg;
	while(1)
	{
		printf("%f,%f",1.1,5.3)
		usleep(dev.period_ms);
	}
	pthread_exit(NULL);
}


int main(void)
{
	DevInfo dev1,dev2;
	pthread_t tid1,tid2;
	
	dev1.fd =uart_init("/dev/ttyS2");
	dev1.dev_id=1;
	dev1.period_ms=800;
	strcopy(dev1.dev_name,"485-01");
	
	dev2.fd =uart_init("/dev/ttyS3");
	dev2.dev_id=2;
	dev2.period_ms=1000;
	strcopy(dev1.dev_name,"485-02");	
	
	pthread_create(&tid1,NULL,sensor_collect_pthread,&dev1)
	pthread_create(&tid2,NULL,sensor_collect_pthread,&dev2)
	
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	close(dev1.fd);
	close(dev2.fd);
	
	return 0;
}
