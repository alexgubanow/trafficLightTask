#pragma once
#include <linux/ioctl.h>
//enum to describe possible colors of each traffic light
typedef enum lghtColor_t { Red, Ylw, Grn }lghtColor;

typedef struct
{

	int idx;
	lghtColor clrT;
} lghtIO_arg_t;

#define getLghtByIdx _IOWR('q', 1, lghtColor *)
#define resetLghtByIdx _IOW('q', 2, int *)
#define setLghtByIdx _IOW('q', 3, lghtIO_arg_t *)
#define removeLghtByIdx _IOW('q', 4, int *)