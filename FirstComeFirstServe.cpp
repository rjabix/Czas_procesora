#define _CRT_SECURE_NO_WARNINGS
#include "FirstComeFirstServe.h"
#include "Process.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

double FirstComeFirstServe::FCFS()
{
	std::vector<Process> processes;
	FILE* f = fopen("dane.txt", "rt");
	if (f == NULL) //sprawdzanie czy plik istnieje
	{
		std::cout << "Nie udalo sie otworzyc pliku" << std::endl;
		throw new std::exception("Nie udalo sie otworzyc pliku");
	}

	//std::cout << "FCFS algorithm\n\n";
	while (!feof(f)) //wczytywanie danych z pliku
	{
		int arr, exec;

		if (fscanf(f, "%d %d", &arr, &exec) != 2) break; //jeśli nie udało się wczytać danych, to kończymy wczytywanie. fscanf zwraca ilość wczytanych danych, jeśli jest różna od 2, to kończymy wczytywanie (może być \n na końcu pliku)
		processes.push_back(Process(0, arr, exec));
	}
	fclose(f);

	std::sort(processes.begin(), processes.end(), 
		[](Process a, Process b) {return a.arrivalTime < b.arrivalTime; }); //sortowanie procesów po czasie przybycia, jeśli plik jest stworzony ręcznie

	int curr_time = 0;
	unsigned long long sum = 0, n = 0;												//n-current process iterator, sum - dla wyliczania średniego czasu oczekiwania
	while (!processes.back().done)									//pętlia główna. .back() zwraca ostatni element z wektora, done - zmienna, która mówi, czy proces się zakończył
	{
		if (curr_time < processes[n].arrivalTime)					//jeśli teraźniejszy czas jest mniejszy od czasu przybycia procesu, to odrazu robimy tak, żeby czas był równy czasowi przybycia
			curr_time = processes[n].arrivalTime;

		processes[n].waitingTime = curr_time - processes[n].arrivalTime; //wyliczanie czasu oczekiwania
		curr_time += processes[n].execTime; //process execute
		processes[n].done = true;
		n++;
	}

	for (int i = 0; i < processes.size(); i++) //wyliczanie średniego czasu oczekiwania
	{
		sum += processes[i].waitingTime;
	}

	return (double)sum / processes.size();
}