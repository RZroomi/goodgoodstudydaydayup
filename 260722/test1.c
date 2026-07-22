#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

#define UART_DEV "/dev/ttyS1"
#define READ_INTERVAL_MS 500
int uart_fd = -1;

int uartinit(const char *dev)
{
	int fd = open(dev,O_RDWR|O_NOCTTY)
	if(fd<0)
	{
		perror("open uart fail");
		return -1;
	}
	struct termios opt;
	tcgetattr(fd,&opt);
	cfsetispeed(&opt, B9600);
    cfsetospeed(&opt, B9600);
    opt.c_cflag |= CREAD | CLOCAL;
    opt.c_cflag &= ~PARENB;
    opt.c_cflag &= ~CSTOPB;
    opt.c_cflag &= ~CSIZE;
    opt.c_cflag |= CS8;
    opt.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    opt.c_oflag &= ~OPOST;
    tcsetattr(fd, TCSANOW, &opt);
    return fd;
}

void *uart_collectpthread(void *arg)
{
	(void)arg;
	char buf[128] ={0};
	while(1)
	{
		int len = read(uart_fd,sizeof(buf)-1);
		if(len>0)
		{
			buf[len]='\0';
			printf("%s\n",buf);
		}
		usleep(1000*READ_INTERVAL_MS)
	}
	pthread_exit(NULL);
}


int main(void)
{
	pthread_t tid;
	uart_fd = uartinit("UART_DEV");
	if(uart_fd <0)
		return -1;
	
	if(pthread_create(&tid,NULL,uart_collectpthread,NULL)!=0)
	{
		perror("error");
		return -1;
	}
	
	char cmd[64];
	while(1)
	{
		fgets(cmd,sizeof(cmd),stdin);
		if(cmd[0]=='q')
			break;
	}
	pthread_join(tid,NULL);
	
	
	return 0;
}

