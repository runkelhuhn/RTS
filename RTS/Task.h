#pragma once
#include <string>

using namespace std;



class Task
{
public:
	Task();
	Task(string, int, int);
	~Task();

	void setPeriod(int period) {
		_period = period;
	}
	int getPeriod() {
		return _period;
	}

	void setDeadline(int deadline) {
		_deadline = deadline;
	}
	int getDeadline() {
		return _deadline;
	}

	void setcompTime(int compTime) {
		_compTime = compTime;
	}
	int getcompTime() {
		return _compTime;
	}

	void setProcessName(string processName) {
		_processName = processName;
	}

	void setPriority(int priority) {
		_priority = priority;
	}
	int getPriority() {
		return _priority;
	}

	int getTimeLeft() {
		return timeLeft;
	}
	
	string getName() {
		return _processName;
	}

	void setResponseTime(float rTime) {
		responseTime = rTime;
	}
	float getResponseTime() {
		return responseTime;
	}

	int executeCyclic(int cycleLength, int cpuAvailable);
	int executeRMS(int cpuLeft);

	friend inline bool operator==(const Task& lhs, const Task& rhs) {
		return (lhs.timeLeft == rhs.timeLeft);
	}
	friend inline bool operator!=(const Task& lhs, const Task& rhs) { return !operator==(lhs, rhs); }
	friend inline bool operator< (const Task& lhs, const Task& rhs) { return (lhs.timeLeft < rhs.timeLeft); }
	friend inline bool operator> (const Task& lhs, const Task& rhs) { return  operator< (rhs, lhs); }
	friend inline bool operator<=(const Task& lhs, const Task& rhs) { return !operator> (lhs, rhs); }
	friend inline bool operator>=(const Task& lhs, const Task& rhs) { return !operator< (lhs, rhs); }
private:
	int _compTime;
	string _processName;
	int _period;
	int _deadline;
	int _priority;

	bool finishedCycle;
	int timeLeft;
	int processingLeft;
	float responseTime;
};

