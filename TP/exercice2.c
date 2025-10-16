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

OS_EVENT *S1;
OS_EVENT *S2;


/* Definition of Task Priorities */

#define TASK1_PRIORITY      1
#define TASK2_PRIORITY      2





// Tache 1
void task1(void* pdata)
{
  INT8U err;
  while (1)
  { 

    for(int i=0; i<10; i++){
        IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, (1 << i));
        OSTimeDlyHMSM(0, 0, 0, 500);
    }
    OSSemPend(S1,0,err);
    OSSemPost(S2);
	  OSTimeDlyHMSM(0, 0, 1, 0);
         
  }
}
// Tache 2
void task2(void* pdata)
{
  INT8U err;
  while (1)
  {   
    
    for(int i=10; i>0; i--){
          IOWR_ALTERA_AVALON_PIO_DATA(LEDS_BASE, (1 << i));
          OSTimeDlyHMSM(0, 0, 0, 500);
    }
    OSSemPend(S2,0,err);
    OSSemPost(S1);
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
 S1=OSSemCreate(1);
 OSTaskCreateExt(task2,
                  NULL,
                  (void *)&task2_stk[TASK_STACKSIZE],
                  TASK2_PRIORITY,
                  TASK2_PRIORITY,
                  task2_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);            
  S2=OSSemCreate(1);             

                    
  OSStart();
  return 0;
}




