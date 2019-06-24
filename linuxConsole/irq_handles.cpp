#include "irq_handles.h"
#include "mLog.h"
/*Handle of termination signal*/
void SIGTERM_Handler(void)
{
	inLog("SIGTERM is received", true);
	exit(0);
}
/*Handle of program interrupt signal*/
void SIGINT_Handler(void)
{
	inLog("SIGINT is received", true);
	exit(0);
}
/*Handle of quit signal*/
void SIGQUIT_Handler(void)
{
	inLog("SIGQUIT is received", true);
	exit(0);
}
/*Handle of kill signal*/
void SIGKILL_Handler(void)
{
	inLog("SIGKILL is received", true);
	exit(1);
}
/*Handle of hang-up signal*/
void SIGHUP_Handler(void)
{
	inLog("SIGHUP is received", true);
	exit(1);
}

/*Handle of normal exit*/
void mainExit()
{
	inLog("Normal exit is preformed", true);
	finishLog();
}