#include "Receive.h"

Receive::Receive(PinName pin)
					:receive(pin)
{
	this->receive.rise(this,&Receive::RiseISR);
	this->receive.fall(this,&Receive::FallISR);
}

void Receive::RiseISR()
{
	this->timer.reset();
	this->timer.start();
}

void Receive::FallISR()
{
	this->timer.stop();
	this->period = this->timer.read_us();
}

int Receive::GetPeriod()
{
	return this->period;
}

