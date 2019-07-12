#pragma once
#include "stdafx.h"

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

class Observer
{
public:
	virtual ~Observer();
	virtual void Update(Subject* changedSubject) = 0;
};