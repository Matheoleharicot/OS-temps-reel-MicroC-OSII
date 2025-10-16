#include <stdio.h>
#include "includes.h"
#include <time.h>
#include "system.h"
#include "alt_types.h"
#include "altera_avalon_pio_regs.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_irq.h"
#include <stdlib.h>


/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    task1_stk[TASK_STACKSIZE];
OS_STK    task2_stk[TASK_STACKSIZE];
OS_STK    task3_stk[TASK_STACKSIZE];

OS_EVENT *S1;
OS_EVENT *S2;
OS_EVENT *S3;



/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2
#define TASK3_PRIORITY      3


void FoncU(void);
void FoncV(void);
void FoncW(void);
void FoncX(void);
void FoncY(void);
void FoncZ(void);



// Tache 1
void task1(void *pdata)
{
  INT8U err;
  while(1)
  {
    OSSemPend(S1, 0, &err);
    FoncU();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S2);

    OSSemPend(S1, 0, &err);
    FoncX();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S3);
  }
}

void task2(void *pdata)
{
  INT8U err;
  while(1)
  {
    OSSemPend(S2, 0, &err);
    FoncV();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S3);

    OSSemPend(S2, 0, &err);
    FoncZ();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S1);
  }
}


void task3(void *pdata)
{
  INT8U err;
  while(1)
  {
    OSSemPend(S3, 0, &err);
    FoncW();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S1);

    OSSemPend(S3, 0, &err);
    FoncY();
    OSTimeDlyHMSM(0, 0, 0, 500);
    OSSemPost(S2);
  }
}



int main(void)
{
    INT8U err;
      
    OSInit();  
   
    
  S1=OSSemCreate(1);
  S2=OSSemCreate(1);
  S3=OSSemCreate(1);   
    
  OSTaskCreateExt(task1,
                  NULL,
                  (void *)&task1_stk[TASK_STACKSIZE],
                  TASK1_PRIORITY,
                  TASK1_PRIORITY,
                  task1_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);
 
 OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);            
               
 OSTaskCreateExt(task3,
                  NULL,
                  (void *)&task3_stk[TASK_STACKSIZE],
                  TASK3_PRIORITY,
                  TASK3_PRIORITY,
                  task3_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);     
                    
  OSStart();
  return 0;
}




void FoncU(void)
{
	printf("Je suis la tache U\n");
}

void FoncV(void)
{
	printf("Je suis la tache V\n");
}

void FoncW(void)
{
	printf("Je suis la tache W\n");
}

void FoncX(void)
{
	printf("Je suis la tache X\n");
}

void FoncY(void)
{
	printf("Je suis la tache Y\n");
}

void FoncZ(void)
{
	printf("Je suis la tache Z\n");
}
