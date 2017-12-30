/*
 * rx.c
 *
 *  Created on: 29 Dec 2017
 *      Author: bryanj
 */
#include "rx.h"

#include <string.h>
#include "cmd.h"
#include "typedef.h"

static char expectedResponse[128];

typedef struct ExpectedRxFor_struct
{
   char *tx;
   char *rx[2];
} ExpectedRxFor;

static const ExpectedRxFor expectedRxFor[] =
{
  {
    SET_VERBOSE_ERROR_CODES,
    {
      "OK\n",
    },
  },
  {
    QUERY_PIN,
    {
      "+CPIN: SIM PIN\n",
      "+CPIN: READY\n",
    },
  },
  {
    SET_THE_PIN,
    {
      "OK\n",
    },
  },
};

static int cmsState[N_ELEMENTS(expectedRxFor)] =
{
  0
};

static void advanceCmdState(int itemNum)
{
   ++cmsState[itemNum];
   if (N_ELEMENTS(expectedRxFor[itemNum].rx) < cmsState[itemNum])
   {
      cmsState[itemNum] = 0;
   }
}

void rx_init(void)
{
   memset(expectedResponse, 0, sizeof(expectedResponse));
   memset(cmsState, 0, sizeof(cmsState));
}

void rx_setupExpectedRxFor(char *tx)
{
   char *rx = "";
   for (int itemNum = 0; itemNum < N_ELEMENTS(expectedRxFor); ++itemNum)
   {
      if (0 == strcmp(expectedRxFor[itemNum].tx, tx))
      {
         int attempt = cmsState[itemNum];
         rx = expectedRxFor[itemNum].rx[attempt];
         if (0 == rx)
         {
            attempt = 0;
            rx = expectedRxFor[itemNum].rx[attempt];
         }

         advanceCmdState(itemNum);
         break;
      }
   }
   strncpy(expectedResponse, rx, sizeof(expectedResponse));
}

char* rx_getExpectedRx(void)
{
   return expectedResponse;
}
