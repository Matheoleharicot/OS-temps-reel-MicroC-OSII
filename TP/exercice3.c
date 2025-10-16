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
void task1(void* pdata)
{
  while (1)
  { 
      FoncU();
	  FoncX();
	  OSTimeDlyHMSM(0, 0, 1, 0);
         
  }
}
// Tache 2
void task2(void* pdata)
{
     
    
  while (1)
  {   
    FoncV();
	FoncZ();
	OSTimeDlyHMSM(0, 0, 1, 0);
    
   }
  
}

// Tache 3
      

void task3(void* pdata)
{


  while (1)
  { 
   FoncW();
   FoncY();
   OSTimeDlyHMSM(0, 0, 1, 0);
  }
  
}



int main(void)
{
    INT8U err;
      
    OSInit();  
   
    
   
      
    
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
