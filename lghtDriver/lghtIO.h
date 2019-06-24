#pragma once
#include <linux/ioctl.h>
//enum to describe possible colors of each traffic light
typedef enum lghtColor_t { Red, Ylw, Grn, NoneColor = 987 }lghtColor;

typedef struct
{
	int idx;
	lghtColor clrT;
} lghtIO_arg_t;

#define getLghtByIdx _IOWR('q', 1, lghtColor *)
#define resetLghtByIdx _IOWR('q', 2, lghtColor *)
#define setLghtByIdx _IOW('q', 3, lghtIO_arg_t *)
#define removeLghtByIdx _IOW('q', 4, int *)

static char* enumToColor(lghtColor targetColor)
{
	switch (targetColor)
	{
	case Grn:
		return (char*)"Green";
	case Ylw:
		return (char*)"Yellow";
	case Red:
		return (char*)"Red";
	default:
		return (char*)"WrongCode";
	}
}