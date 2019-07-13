#pragma once
#include <iostream>
#include <vector>

class Observer;
class Monster;
class AnalogClock;
class SoundEffect;
class Subject;
using namespace std;

////////<<<< Interface >>>>////////
class Observer
{
public:
	virtual ~Observer() = default;
	virtual void Update(Subject* changedSubject) = 0;
};


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
			ob->Update(this);
	}
};


////////<<<< Subject >>>>////////
class SoundEffect : public Subject
{
public:
	void PlaySound() {
		cout << "노래가 흘러나오는중" << endl;
		Notify();
	}
};


////////<<<< Observer >>>>////////
class Monster : public Observer
{
private:
	SoundEffect* subject;
public:
	Monster(SoundEffect* clock) : subject(clock) { subject->Attach(this); }
	virtual ~Monster() { subject->Detach(this); }
	void Update(Subject* changedSubject) override {
		if (changedSubject == subject)
			Draw();
	}
public:
	void Draw() {
		cout << "몬스터 등장" << endl;
	}
};
