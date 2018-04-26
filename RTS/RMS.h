#pragma once
#include <list>
#include "Task.h"
#include <cmath>

using namespace std;

class RMS
{
public:
	RMS();
	~RMS();
	void addTask(Task task);
	void calculatePrioritiesRMS();
	void calculatePrioritiesRTA();
	float getUtilization();
	bool isLLScheduable(bool print);
	float getResponseTime(Task t, list<Task> hpTasks, float lastResponseTime);
	float getResponseTime(Task t, list<Task> hpTasks);
	bool responseTimeAnalysis();
	bool simpleResponseTimeAnalysis(string taskName, bool print);
	int findBigCycle();
	string scheduleTasks();
	void printTasks();
	int getbigCycle() {
		return bigCycle;
	}
	int getsmallCycle() {
		return smallCycle;
	}
private:
	int bigCycle;
	int smallCycle = 99999;
	list<Task> taskList;
};

