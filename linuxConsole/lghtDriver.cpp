#include "lightDriver.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

char* lghtIOdev = "/dev/lghtIO";
int fd;

int lghtIOinit()
{
	fd = open(lghtIOdev, O_RDWR); 
	if (fd == -1)
	{
		perror("query_apps open");
		return 2;
	}
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::Grn;
	rq.idx = 13;
	if (ioctl(fd, setLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl setLghtByIdx");
	}
	rq.clrT = lghtColor::Red;
	rq.idx = 13;
	if (ioctl(fd, resetLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl resetLghtByIdx");
	}
	if (ioctl(fd, getLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl getLghtByIdx");
	}
	close(fd);
}