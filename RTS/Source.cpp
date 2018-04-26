#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "RMS.h"

using namespace std;

int main() {
	while (true) {
		RMS rms;
		string filename;
		cout << "Enter Filename: ";
		cin >> filename;
		string line;
		cout << endl << "Input : " << endl;
		ifstream myfile(filename);
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				vector<string> a;
				std::stringstream ss(line);
				std::string item;
				while (std::getline(ss, item, '\t')) {
					a.push_back(item);
				}
				//unsafe
				rms.addTask(Task(a.at(0), stoi(a.at(1)), stoi(a.at(2))));
				cout << line << '\n';
			}
			myfile.close();
		}
		rms.calculatePrioritiesRMS();
		cout << endl << "Priority Table:" << endl;
		rms.responseTimeAnalysis();
		rms.printTasks();
		cout << endl << "Utilization: " << rms.getUtilization() << endl;
		cout << "isLLScheduable: ";
		rms.isLLScheduable(true);
		rms.findBigCycle();
		cout << "major Cycle: " << rms.getbigCycle() << endl;
		cout << "minor Cycle: " << rms.getsmallCycle() << endl << endl;

		//cout << "Scheduele RMS: " << endl;
		//cout << rms.scheduleTasks() << endl;

		cout << endl;
		rms.simpleResponseTimeAnalysis("A", true);
		rms.simpleResponseTimeAnalysis("B", true);
		rms.simpleResponseTimeAnalysis("C",true);

		cout << endl;
		cout << "Scheduele RTA: " << endl;
		rms.calculatePrioritiesRTA();
		rms.responseTimeAnalysis();
		rms.printTasks();
		cout << rms.scheduleTasks() << endl;
	}
	return 0;
}