/*
 ============================================================================
 Name        : Non-scalable_SM.c
 Author      : Bryan Jarmain
 ============================================================================
 */
#include "Non-scalable_SM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "tx.h"
#include "typedef.h"

typedef enum ModemStates_enum
{
   state_kickoff,
   state_verboseErrorSet,
   state_checkPin,
   state_needPin,
   state_done,

} ModemStates;
ModemStates state;

typedef struct responseTable_struct
{
   char *string;
   fsmEvent event;
} ResponseTable;

static const ResponseTable responseTable[] =
{
  {
    "OK",
    event_ok
  },
  {
    "+CPIN: SIM PIN",
    event_pinRequired
  },
  {
    "+CPIN: READY",
    event_noPinRequired
  },
};

static fsmEvent strToEvent(char *string)
{
   fsmEvent result = event_none;
   for (int strNum = 0; strNum < N_ELEMENTS(responseTable); ++strNum)
   {
      if (0 == strcmp(string, responseTable[strNum].string))
      {
         result = responseTable[strNum].event;
         break;
      }
   }
   return result;
}

static void handleTimeouts(fsmEvent event, ModemStates *state, int *timeout)
{
   if (state_kickoff != *state)
   {
      if ((event_none == event) || (event_error == event))
      {
         ++*timeout;
         if (*timeout > 3)
         {
            *timeout = 0;
            *state = state_done;
         }
      }
      else
      {
         *timeout = 0;
      }
   }
}

void fsm_init(void)
{
   state = state_kickoff;
}

fsmResult fsm_Rx(char *response)
{
   static int timeout = 0;
   fsmResult result = result_success;
   fsmEvent event = strToEvent(response);
   printf("RX -> %s\n", response);
   handleTimeouts(event, &state, &timeout);
   switch (state)
   {
   case state_kickoff:
      timeout = 0;
      tx(SET_VERBOSE_ERROR_CODES);
      state = state_verboseErrorSet;
      break;
   case state_verboseErrorSet:
      if (event_ok == event)
      {
         tx(QUERY_PIN);
         state = state_checkPin;
      }
      else
      {
         tx(SET_VERBOSE_ERROR_CODES);
      }
      break;
   case state_checkPin:
      if (event_noPinRequired == event)
      {
         state = state_done;
      }
      else if (event_pinRequired == event)
      {
         tx(SET_THE_PIN);
         state = state_needPin;
      }
      else
      {
         state = state_done;
      }

      break;
   case state_needPin:
      if (event_ok == event)
      {
         tx(QUERY_PIN);
         state = state_checkPin;
      }
      break;
   case state_done:
      break;
   }
   if (state_done == state)
   {
      timeout = 0;
      result = result_done;
   }
   return result;
}
