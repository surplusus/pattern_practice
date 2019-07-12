#pragma once
#include "stdafx.h"

////////<<<< Observer >>>>////////
class DigitalClock : public Observer
{
private:
	ClockTimer* subject;
public:
	DigitalClock(ClockTimer* clock) : subject(clock) { subject->Attach(this); }
	virtual ~DigitalClock() { subject->Detach(this); }
	void Update(Subject* changedSubject) override {
		if (changedSubject == subject)
			Draw();	}
public:
	void Draw() {
		std::cout << "The Time is " << subject->GetHour() << " : "
			<< subject->GetMinute() << " : " << subject->GetSecond() << std::endl;	}
};

class AnalogClock : public Observer
{
private:
	ClockTimer* subject;
public:
	AnalogClock(ClockTimer* clock) : subject(clock) { subject->Attach(this); }
	virtual ~AnalogClock() { subject->Detach(this); }
	void Update(Subject* changedSubject) override {
		if (changedSubject == subject)
			Draw();
	}
public:
	void Draw() {
		std::cout << "The Time is " << subject->GetHour() << " : "
			<< subject->GetMinute() << " : " << subject->GetSecond() << std::endl;
	}
};


////////<<<< Subject >>>>////////
class ClockTimer : public Subject
{
private:
	int hour;
	int minute;
	int second;
public:
	void SetTime(int hr, int min, int sec) {
		hour = hr;	minute = min; second = sec;
		Notify();
	}
	int GetHour() const { return hour; }
	int GetMinute() const { return minute; }
	int GetSecond() const { return second; }
};
