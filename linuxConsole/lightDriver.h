#pragma once
#include "../lghtDriver/lghtIO.h"

/*Method to test connection with driver*/
int lghtIOinit();
/*setter for light by idx*/
lghtColor setLght(lghtColor clr, int idx);
/*getter for light by idx*/
lghtColor getLght(int idx);
/*retter for light by idx*/
lghtColor resetLght(int idx);