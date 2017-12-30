/*
 * tx.c
 *
 *  Created on: 29 Dec 2017
 *      Author: bryanj
 */

#include "tx.h"

#include <stdio.h>
#include <string.h>

#include "cmd.h"
#include "rx.h"

static void printDataToSend(char* dataToSend)
{
   char txCpy[128];
   strncpy(txCpy, dataToSend, sizeof txCpy);
   chomp(txCpy);
   printf("TX -> %s\n", txCpy);
   txCpy[0] = 0;
}

static void mimeTx(char* dataToSend)
{
   printDataToSend(dataToSend);
   rx_setupExpectedRxFor(dataToSend);
}

void tx_init(void)
{
   /*do nothing*/
}

void tx(char *dataToSend)
{
   mimeTx(dataToSend);
}

