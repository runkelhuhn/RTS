#include "RMS.h"
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

RMS::RMS()
{
}


RMS::~RMS()
{
}

void RMS::addTask(Task task)
{
	taskList.push_back(task);
	smallCycle = min(smallCycle, task.getPeriod());
}

void RMS::calculatePrioritiesRMS()
{
	taskList.sort();
	reverse(taskList.begin(), taskList.end());
	int priority = 0;
	for (auto& t : taskList)
	{	
		priority++;
		t.setPriority(priority);
	}
	reverse(taskList.begin(), taskList.end());
}

void RMS::calculatePrioritiesRTA()
{
	list<Task> rTApriorityTasks;
	int listsize = taskList.size();
	for (int i = 1; i <= listsize; i++) {
		list<Task> tasklistClones = taskList;
		bool foundOne = false;
		for (auto& t : taskList)
		{
			tasklistClones.remove(t);
			float tResponseTime = getResponseTime(t, tasklistClones);
			if (tResponseTime <= t.getDeadline())
			{
				cout << t.getName() << "\t" << tResponseTime << endl;
				t.setPriority(i);
				rTApriorityTasks.push_back(t);
				taskList.remove(t);
				foundOne = true;
				break;
			}
			else {
				tasklistClones.push_front(t);
				tasklistClones.sort();
			}
			
		}
		if (!foundOne) {
			cout << "Error" << endl;
		}
	}
	taskList = rTApriorityTasks;
	int p = 0;
	reverse(taskList.begin(), taskList.end());
}

void RMS::printTasks() {
	cout << "Name" << "\t" << "Period" << "\t" << "CompTime" << "\t" << "Priority"  << "\t" << "Response Time" << endl;
	for (auto& t : taskList){
		cout << t.getName() << "\t" << t.getPeriod() << "\t" << t.getcompTime() << "\t\t" << t.getPriority() << "\t\t" << t.getResponseTime() << endl;
	}
}

float RMS::getUtilization()
{
	float U = 0;
	for each (Task t in taskList)
	{
		U += (float)t.getcompTime() / (float)t.getPeriod();
	}
	return U;
}

bool RMS::isLLScheduable(bool print)
{
	float u = getUtilization();
	float n = taskList.size();
	float lhs = n*(pow(2, 1 / n) - 1);
	bool isIt = u <= lhs;
	if (print) {
		cout << u << " <= " << lhs << " -> " << isIt << endl;
	}
	return isIt;
}

float RMS::getResponseTime(Task t, list<Task> hpTasks)
{
	if (hpTasks.size() == 0) {
		return t.getcompTime();
	}
	else {
		Task next = hpTasks.back();
		hpTasks.remove(next);
		float lastResponseTime = getResponseTime(next, hpTasks);
		return getResponseTime(t, hpTasks, lastResponseTime);
	}
}

float RMS::getResponseTime(Task t, list<Task> hpTasks, float lastResponseTime)
{
	float previousCombined = 0;
	for (auto& hpTask : hpTasks)
	{
		previousCombined += ceil(lastResponseTime / hpTask.getPeriod()) + hpTask.getcompTime();
	}
	return t.getcompTime() + previousCombined;
}

bool RMS::responseTimeAnalysis()
{
	bool result = true;
	float lastResponseTime = 0;
	list<Task> higherPriorityTasks;
	for (auto& t : taskList)
	{
		lastResponseTime = getResponseTime(t, higherPriorityTasks, lastResponseTime);
		t.setResponseTime(lastResponseTime);
		higherPriorityTasks.push_back(t);
		if (lastResponseTime > t.getPeriod()) {
			result = false;
		}
	}
	return result;
}

bool RMS::simpleResponseTimeAnalysis(string taskName, bool print)
{
	float responseTime;
	list<Task> higherPriorityTasks;
	for (auto& t : taskList)
	{
		if (taskName == t.getName()) {
			float previousCombined = 0;
			for (auto& hpTask : higherPriorityTasks)
			{
				previousCombined += ceil(hpTask.getDeadline() / hpTask.getPeriod()) + hpTask.getcompTime();
			}
			responseTime = t.getcompTime() + previousCombined;
			if (responseTime > t.getPeriod()) {
				if (print) {
					cout << "Simple Response Time Analysis for Task " << taskName << " failed." << endl;
					cout << "Deadline(" << t.getDeadline() << ") < ResponseTime(" << responseTime << ")" <<  endl;
				}
				return false;
			}
			if (print) {
				cout << "Simple Response Time Analysis for Task " << taskName << " succeded." << endl;
				cout << "Deadline(" << t.getDeadline() << ") >= ResponseTime(" << responseTime << ")" << endl;
			}
			return true;
		}
		higherPriorityTasks.push_back(t);
	}
	cout << "Error: Task with Name " << taskName << " not found!" << endl;
	return false;
}


int ggt(int a, int b)
{
	if (b == 0)
		return a;
	if (a == 0)
		return b;
	else
		return ggt(b, a%b);
}

int kgv(int zahl1, int zahl2)
{
	return (zahl1*zahl2) / ggt(zahl1, zahl2);
}

int RMS::findBigCycle() {
	if (taskList.size() == 0) {
		return 0;
	}
	int lastkgv = taskList.begin()->getPeriod();
	for (auto& t : taskList)
	{
		lastkgv = kgv(lastkgv, t.getPeriod());
	}
	bigCycle = lastkgv;
	return lastkgv;
}

string RMS::scheduleTasks()
{
	string schedule = "|0| ";
	int i;
	for (i = 1; i <= bigCycle; i++) {
		int cpuTick = 1;
		for (auto& t : taskList) {
			int cpuTickBefore = cpuTick;
			cpuTick = t.executeRMS(cpuTick);
			if (cpuTick != cpuTickBefore) {
				schedule = schedule + t.getName();
			}
			if (cpuTick == -1) {
				return "Error at Task " + t.getName() + ": not schedulable, current schedule: " + schedule;
			}
		}
		if (cpuTick == 1) {
			schedule = schedule + "_";
		}
		if (i % smallCycle == 0) {
			schedule = schedule + " |" + to_string(i) + "| ";
		}
	}
	return schedule;
}
