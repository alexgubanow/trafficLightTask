#include "lightDriver.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

char* lghtIOdev = "/dev/lghtIO";
int openLghtIO();

int lghtIOinit()
{
	printf("Testing connection to LghtIO driver\n");
	int fd = openLghtIO();
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::NoneColor;
	rq.idx = 11;
	if (ioctl(fd, getLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl getLghtByIdx");
	}
	printf("Color of #%d is %s\n", rq.idx, enumToColor(rq.clrT));
	rq.clrT = lghtColor::Grn;
	rq.idx = 13;
	if (ioctl(fd, setLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl setLghtByIdx");
	}
	printf("Color of #%d is %s\n", rq.idx, enumToColor(rq.clrT));
	rq.clrT = lghtColor::NoneColor;
	rq.idx = 13;
	if (ioctl(fd, resetLghtByIdx, &rq.idx) == -1)
	{
		perror("lghtIO ioctl resetLghtByIdx");
	}
	printf("Color of #%d is %s\n", rq.idx, enumToColor(rq.clrT));
	if (ioctl(fd, getLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl getLghtByIdx");
	}
	printf("Color of #%d is %s\n", rq.idx, enumToColor(rq.clrT));
	close(fd);
	return fd;
}

int openLghtIO()
{
	int fd = open(lghtIOdev, O_RDWR);
	if (fd == -1) { perror("lghtIO failed to open"); }
	return fd;
}
lghtColor setLght(lghtColor clr, int idx)
{
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	lghtIO_arg_t rq;
	rq.clrT = clr;
	rq.idx = idx;
	if (ioctl(fd, setLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl setLghtByIdx");
	}
	close(fd);
	return rq.clrT;
}
lghtColor getLght(int idx)
{
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::NoneColor;
	rq.idx = idx;
	if (ioctl(fd, getLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl getLghtByIdx");
	}
	close(fd);
	return rq.clrT;
}
lghtColor resetLght(int idx)
{
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::NoneColor;
	rq.idx = idx;
	if (ioctl(fd, resetLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl resetLghtByIdx");
	}
	close(fd);
	return rq.clrT;
}