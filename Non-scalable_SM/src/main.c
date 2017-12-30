/*
 ============================================================================
 Name        : Non-scalable_FSM
 Author      : Bryan Jarmain
 ============================================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "Non-scalable_SM.h"
#include "rx.h"
#include "tx.h"

int main(void)
{
   rx_init();
   tx_init();
   fsm_init();
   for (;;)
   {
      char* rx = rx_getExpectedRx();
      chomp(rx);
      fsmResult result = fsm_Rx(rx);
      if (result_done == result)
      {
         break;
      }
      printf("\n");
   };
   return EXIT_SUCCESS;
}
