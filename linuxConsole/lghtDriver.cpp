#include "lightDriver.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
/*path to device file*/
char* lghtIOdev = "/dev/lghtIO";
/*Method of getting file descriptor of device, by opening its file*/
int openLghtIO();
/*Method to test connection with driver*/
int lghtIOinit()
{
	printf("Testing connection to LghtIO driver\n");
	int fd = openLghtIO();
	if (fd < 0) { return fd; }
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

/*Method of getting file descriptor of device, by opening its file*/
int openLghtIO()
{
	int fd = open(lghtIOdev, O_RDWR);
	if (fd == -1) { perror("lghtIO failed to open"); }
	return fd;
}
/*setter for light by idx*/
lghtColor setLght(lghtColor clr, int idx)
{
	//get file descriptor by opening
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	//setup request with given values
	lghtIO_arg_t rq;
	rq.clrT = clr;
	rq.idx = idx;
	//push request to device
	if (ioctl(fd, setLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl setLghtByIdx");
	}
	//close device file
	close(fd);
	return rq.clrT;
}
/*getter for light by idx*/
lghtColor getLght(int idx)
{
	//get file descriptor by opening
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	//setup request with given values
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::NoneColor;
	rq.idx = idx;
	if (ioctl(fd, getLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl getLghtByIdx");
	}
	//close device file
	close(fd);
	return rq.clrT;
}
/*retter for light by idx*/
lghtColor resetLght(int idx)
{
	int fd = openLghtIO();
	if (fd == -1) { return lghtColor::NoneColor; }
	//setup request with given values
	lghtIO_arg_t rq;
	rq.clrT = lghtColor::NoneColor;
	rq.idx = idx;
	if (ioctl(fd, resetLghtByIdx, &rq) == -1)
	{
		perror("lghtIO ioctl resetLghtByIdx");
	}
	//close device file
	close(fd);
	return rq.clrT;
}