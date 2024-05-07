#include "Process.h"
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


