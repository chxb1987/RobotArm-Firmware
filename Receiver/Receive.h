#ifndef __RECEIVE_H_
#define __RECEIVE_H_

#include "mbed.h"

class Receive
{
	public:
		Receive(PinName pwmin);
		int GetPeriod();
	private:
		InterruptIn receive;
		Timer timer;
		int period;
		void RiseISR();
		void FallISR();
};

#endif

