#pragma once
#include <iostream>
#include <vector>
////////<<<< Interface >>>>////////
class Observer;

class Subject
{
private:
	std::vector<Observer*> observers;
public:
	virtual ~Subject() = default;
	void Attach(Observer* ob) { observers.push_back(ob); }
	void Detach(Observer* ob) {
		auto it = std::find(observers.begin(), observers.end(), ob);
		observers.erase(it);
	}
	void Notify() {
		for (auto ob : observers)
			ob->Update(this);	}
};

class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Update(Subject* changedSubject) = 0;
};


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
			<< subject->GetMinute() << " : " << subject->GetSecond() << std::endl;	}
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
