#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;
class ApplyKey;
class InputKey;
class Status;
class Mediator;
class Colleague;
class Time;

////////<<<< Interface >>>>////////

class Colleague
{
protected:
	string _name;
private:
	ApplyKey *_mediator;
public:
	explicit Colleague(ApplyKey *mediator, string name)
	{
		_mediator = mediator;
		_name = name;
	}
	virtual ~Colleague() = default;
	void changed();
	virtual void Start() = 0;
	virtual void End() = 0;
};


class Mediator {
public:
	virtual ~Mediator() = default;
	virtual void HandleEvent(int numColleague) = 0;
	virtual void ColleagueChanged(Colleague *changedColleague) = 0;
};


////////<<<< Colleague >>>>////////


class Time : public Colleague {
private:
	system_clock _time;
	time_point<system_clock> _gamestart;
	time_point<system_clock> _startPeriod;
	time_point<system_clock> _endPeriod;
	duration<double> _deltaTime;
public:
	explicit Time(ApplyKey *mediator, string name) : Colleague(mediator, name) {
		_gamestart = _time.now();	_startPeriod = _time.now();	}
public:
	int DeltaTime() {	// return delta time 
		int count = 0;
		nanoseconds sec(0ns);
		while (count < 10) {
			_endPeriod = _time.now();
			_deltaTime = _endPeriod - _startPeriod;
			sec += duration_cast<nanoseconds>(_deltaTime);
			if (sec.count() > 1.0)	{
				sec.zero(); count++;
				cout << "  마리오 동작 " << count << "초 진행중" << endl;	}
		}
		return static_cast<int>(_deltaTime.count());	}
	void Start() { 
		_startPeriod = _time.now(); 
		cout << "  마리오 동작 중" << endl;
		DeltaTime();
		changed(); }	// set base period for delta time
	void End() { 
		cout << "  마리오 동작 끝" << endl;
		}
	int NowTime() {		// now time from start
		_endPeriod = _time.now();
		duration<double> deltaTime = _endPeriod - _gamestart;
		return static_cast<int>(deltaTime.count());	}
};

class InputKey : public Colleague
{
private:
	bool _isActive = false;
public:
	explicit InputKey(ApplyKey *mediator, string name) : Colleague(mediator, name) {}
	void Start() {
		cout << "  마리오 " << _name << " 시작" << endl;
		_isActive = true;
		changed();
	}
	void End() {
		cout << "  마리오 " << _name << " 끝" << endl;
		_isActive = false;
	}
};

class Status : public Colleague
{
private:
	bool _isActive = false;
public:
	explicit Status(ApplyKey *mediator, string name) : Colleague(mediator, name) {}
	void Start() {
		cout << "  마리오 " << _name << " 시작" << endl;
		_isActive = true;
	}
	void End() {
		cout << "  마리오 " << _name << " 끝" << endl;
		_isActive = false;
	}
};

class ApplyKey : public Mediator
{
private:
	Colleague *_colleagues[5];
public:
	enum Colleagues { KEY = 0, JUMP, LEFT, RIGHT, DIE, TIME };
	ApplyKey() {
		_colleagues[DIE] = new Status(this, "DIE");
		_colleagues[JUMP] = new Status(this, "JUMP");
		_colleagues[LEFT] = new Status(this, "LEFT");
		_colleagues[RIGHT] = new Status(this, "RIGHT");
		_colleagues[KEY] = new InputKey(this, "KEY");
		_colleagues[TIME] = new Time(this, "TIME");
	}
	virtual ~ApplyKey() {
		for (int i = 0; i < 5; i++)
			delete _colleagues[i];
	}
	virtual void HandleEvent(int numColleague) {
		Colleagues num = static_cast<Colleagues>(numColleague);
		_colleagues[num]->changed();
	}
	virtual void ColleagueChanged(Colleague *changedColleague)
	{
		if (changedColleague == _colleagues[DIE])
		{
			_colleagues[DIE]->End();
			cout << "으양 주금!  모~ 다메다요~~" << endl;
		}
		else if (changedColleague == _colleagues[JUMP])
		{
			_colleagues[JUMP]->Start();
			_colleagues[TIME]->Start();
			_colleagues[JUMP]->End();
			HandleEvent(KEY);
		}
		else if (changedColleague == _colleagues[LEFT])
		{
			_colleagues[JUMP]->Start();
			_colleagues[TIME]->Start();
			_colleagues[JUMP]->End();
			HandleEvent(KEY);
		}
		else if (changedColleague == _colleagues[RIGHT])
		{
			_colleagues[JUMP]->Start();
			_colleagues[TIME]->Start();
			_colleagues[JUMP]->End();
			HandleEvent(KEY);
		}
		else if (changedColleague == _colleagues[TIME])
		{
			_colleagues[TIME]->End();
		}
	}
};

void Colleague::changed()
{
	_mediator->ColleagueChanged(this);
}