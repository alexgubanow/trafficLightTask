#pragma once

/*Handle of termination signal*/
void SIGTERM_Handler(void);
/*Handle of program interrupt signal*/
void SIGINT_Handler(void);
/*Handle of quit signal*/
void SIGQUIT_Handler(void);
/*Handle of kill signal*/
void SIGKILL_Handler(void);
/*Handle of hang-up signal*/
void SIGHUP_Handler(void);
/*Handle of normal exit*/
void mainExit();