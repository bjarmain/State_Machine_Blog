/*
 * rx.h
 *
 *  Created on: 29 Dec 2017
 *      Author: bryanj
 */

#ifndef RX_H_
#define RX_H_

void rx_init(void);
void rx_setupExpectedRxFor(char *tx);
char* rx_getExpectedRx(void);

#endif /* RX_H_ */
