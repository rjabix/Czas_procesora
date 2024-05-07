#include "Process.h"
Process::Process(int Id, int ArrTime, int ExecTime)
{
	id = Id;
	arrivalTime = ArrTime;
	execTime = ExecTime;
	waitingTime = 0;
}

Process::Process()
{
}


