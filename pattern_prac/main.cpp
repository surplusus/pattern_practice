#include "stdafx.h"

int main()
{
	using namespace std;

	ClockTimer* timer = new ClockTimer;

	DigitalClock digital(timer);
	AnalogClock analogue(timer);

	timer->SetTime(11, 31, 45);
	return 0;
}