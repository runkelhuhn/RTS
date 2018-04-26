#include "Task.h"
#include <iostream>


Task::Task()
{
}

Task::Task(string name, int period, int compTime)
{
	_processName = name;
	_period = period;
	_deadline = period;
	_compTime = compTime;
	timeLeft = period;
	processingLeft = compTime;
	finishedCycle = false;
}


Task::~Task()
{
}

int Task::executeCyclic(int cycleLength, int cpuAvailable)
{
	int cpuLeft = cpuAvailable;
	if (!finishedCycle && cpuAvailable >= _compTime && _compTime <= timeLeft) {
		finishedCycle = true;
		cpuLeft = cpuAvailable - _compTime;
	}
	timeLeft -= cycleLength;
	if (finishedCycle) {
		timeLeft = _period + timeLeft;
		finishedCycle = false;
	}
	if (!finishedCycle && timeLeft <= 0){
		cpuLeft = -1;
	}
	//cout << getTimeLeft() << endl;
	return cpuLeft;
}

//return 0 if tick was used, 1 if not and -1 if error
int Task::executeRMS(int cpuLeft)
{
	timeLeft--;
	if (!finishedCycle && cpuLeft > 0) {
		cpuLeft--;
		processingLeft--;
		if (processingLeft <= 0) {
			finishedCycle = true;
		}
	}

	if (timeLeft <= 0) {
		if (finishedCycle) {
			timeLeft = _period;
			processingLeft = _compTime;
			finishedCycle = false;
		}
		else {
			cpuLeft = -1;
		}
	}
	return cpuLeft;
}
