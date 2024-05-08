#include "Process.h"
#include <vector>
Process::Process(int Id, int ArrTime, int ExecTime)
{
	id = Id;
	arrivalTime = ArrTime;
	execTime = ExecTime;
	waitingTime = 0;
}
//ten plik zawiera implementację funkcji klasy Process (w danym przypadku konstruktora)
Process::Process()
{
}

bool Process::isAllDone(std::vector<Process> processes) //funkcja sprawdzająca, czy wszystkie procesy zostały wykonane
{
	for (int i = 0; i < processes.size(); i++)
	{
		if (!processes[i].done)
			return false;
	}
	return true;
}


