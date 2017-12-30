/*
 * cmd.c
 *
 *  Created on: 30 Dec 2017
 *      Author: bryanj
 */
#include <string.h>

void chomp(char *string)
{
   int length = strlen(string);
   for (int pos = 0; pos < length; ++pos)
   {
      if (('\r' == string[pos]) || ('\n' == string[pos]))
      {
         string[pos] = 0;
         break;
      }
   }
}


