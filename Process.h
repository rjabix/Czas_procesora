#ifndef PROCESS_H
#define PROCESS_H
#include <vector>
#pragma once
class Process
{// ten plik zawiera deklarację klasy Process, bez implementacji
public:
	int id;
	int arrivalTime;
	int execTime;
	int waitingTime;
	bool done = false;
	Process();
	Process(int id, int arrivalTime, int execTime);
	static bool isAllDone(std::vector<Process> processes);
};
#endif // !PROCESS_H



