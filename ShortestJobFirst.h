#ifndef SHORTESTJOBFIRST_H
#define SHORTESTJOBFIRST_H
#include "Process.h"
#include <vector>
#pragma once
class ShortestJobFirst
{
private:
	static bool isAllDone(std::vector<Process> processes);
public:
	static double SJF();
};


#endif // !SHORTESTJOBFIRST_H