#define _CRT_SECURE_NO_WARNINGS
#include "FirstComeFirstServe.h"
#include "Process.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

void FirstComeFirstServe::FCFS()
{
	std::vector<Process> processes;
	FILE *f = fopen("dane.txt", "rt");
	if (f == NULL) //sprawdzanie czy plik istnieje
	{
		std::cout << "Nie udało się otworzyć pliku" << std::endl;
		return;
	}

	int k = 0; //number of processes

	std::cout<<"FCFS algorithm\n\nProcesses:\n";
	while (!feof(f)) //wczytywanie danych z pliku
	{
		int arr, exec;
		fscanf(f, "%d %d", &arr, &exec);
		std::cout<<"Arrival Time: "<< arr << " Execute time: " << exec << std::endl;
		processes.push_back(Process(0, arr, exec));
		k++;
	}
	fclose(f);

	std::sort(processes.begin(), processes.end(), [](Process a, Process b) {return a.arrivalTime < b.arrivalTime; }); //sortowanie procesów po czasie przybycia, jeśli plik jest stworzony ręcznie

	int curr_time = 0;
	int sum = 0, n = 0; //n-current process iterator, sum - dla wyliczania średniego czasu oczekiwania
	while (!processes[k - 1].done) //pętlia główna
	{
		if (curr_time < processes[n].arrivalTime) //jeśli teraźniejszy czas jest mniejszy od czasu przybycia procesu, to odrazu robimy tak, żeby czas był równy czasowi przybycia
			curr_time = processes[n].arrivalTime;
		
		processes[n].waitingTime = curr_time - processes[n].arrivalTime;

		//for (int i = 0; i < processes[n].execTime; i++) //process execute
		//{
		//	curr_time++;
		//}
		curr_time+= processes[n].execTime;

		processes[n].done = true;
		n++;
	}
	std::cout<<"\nProcess\tWaiting time\n";
	for (int i = 0; i < processes.size(); i++) //wyliczanie średniego czasu oczekiwania
	{
		sum += processes[i].waitingTime;
		std::cout<< "Process " << i << " Waiting time: " << processes[i].waitingTime << std::endl;
	}
	
	std::cout << "Średni czas oczekiwania: " << (double)sum / processes.size() << std::endl;
}