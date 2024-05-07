#ifndef PROCESS_H
#define PROCESS_H
#pragma once
class Process
{// тут ініціалізація класу, 
public:
	int id;
	int arrivalTime;
	int execTime;
	int waitingTime;
	bool done = false;
	Process();
	Process(int id, int arrivalTime, int execTime);
};
#endif // !PROCESS_H



