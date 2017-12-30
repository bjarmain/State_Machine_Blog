/*
 * cmd.h
 *
 *  Created on: 29 Dec 2017
 *      Author: bryanj
 */
#ifndef CMD_H_
#define CMD_H_

#define SET_VERBOSE_ERROR_CODES "AT+CMEE=2\n"
#define QUERY_PIN "AT+CPIN?\n"
#define SET_THE_PIN "AT+CPIN=\"1234\"\n"

void chomp(char *string);
#endif /* CMD_H_ */
