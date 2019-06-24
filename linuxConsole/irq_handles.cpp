#include "irq_handles.h"
#include "mLog.h"

void SIGTERM_Handler(void)
{
	inLog("SIGTERM is received", true);
	exit(0);
}
void SIGINT_Handler(void)
{
	inLog("SIGINT is received", true);
	exit(0);
}
void SIGQUIT_Handler(void)
{
	inLog("SIGQUIT is received", true);
	exit(0);
}
void SIGKILL_Handler(void)
{
	inLog("SIGKILL is received", true);
	exit(1);
}
void SIGHUP_Handler(void)
{
	inLog("SIGHUP is received", true);
	exit(1);
}

void mainExit()
{
	inLog("Normal exit is preformed", true);
	finishLog();
}