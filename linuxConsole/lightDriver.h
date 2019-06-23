#pragma once
#include "../lghtDriver/lghtIO.h"
int lghtIOinit();
lghtColor setLght(lghtColor clr, int idx);
lghtColor getLght(int idx);
lghtColor resetLght(int idx);