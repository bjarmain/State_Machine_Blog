/*
 * Non-scalable_SM.h
 *
 *  Created on: 29 Dec 2017
 *      Author: bryanj
 */

#ifndef NON_SCALABLE_SM_H_
#define NON_SCALABLE_SM_H_

typedef enum fsmResult_enum
{
   result_success,
   result_done,
   result_error,
} fsmResult;

typedef enum fsmEvent_enum
{
   event_none,
   event_ok,
   event_error,
   event_pinRequired,
   event_noPinRequired,
} fsmEvent;

void fsm_init(void);
fsmResult fsm_Rx(char *response);


#endif /* NON_SCALABLE_SM_H_ */
