#define _CRT_SECURE_NO_WARNINGS
#include "ShortestJobFirst.h"
#include "Process.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

double ShortestJobFirst::SJF()
{
	std::vector<Process> processes;
	FILE* f = fopen("dane.txt", "rt");
	if (f == NULL) //sprawdzanie czy plik istnieje
	{
		std::cout << "Nie udało się otworzyć pliku" << std::endl;
		throw new std::exception("Nie udało się otworzyć pliku");
	}

	//std::cout << "SJF algorithm\n\n";
	while (!feof(f)) //wczytywanie danych z pliku
	{
		int arr, exec, i = 0;

		if (fscanf(f, "%d %d", &arr, &exec) != 2) break;					//jeśli nie udało się wczytać danych, to kończymy wczytywanie. fscanf zwraca ilość wczytanych danych, jeśli jest różna od 2, to kończymy wczytywanie (może być \n na końcu pliku)
		processes.push_back(Process(i, arr, exec));
		i++;
	}
	fclose(f);

	std::sort(processes.begin(), processes.end(), 
		[](Process a, Process b) {return a.arrivalTime < b.arrivalTime; }); //sortowanie procesów po czasie przybycia, jeśli plik jest stworzony ręcznie

	int curr_time = 0;
	unsigned long long sum = 0;								//sum - dla wyliczania średniego czasu oczekiwania
	int n = 0;												//n - ilość zakończonych procesów

	while (n<processes.size())			//pętlia główna. .back() zwraca ostatni element z wektora, done - zmienna, która mówi, czy proces się zakończył
	{

		int tmpi = -1, min = INT_MAX;				//indeks procesu o minimalnym czasie pracy

		for (int i = 0; i < processes.size(); i++)	//dodawanie procesow, którzy już nadeszli, do kolejki
		{
			
			if (processes[i].arrivalTime <= curr_time && !processes[i].done) // szukamy najkrótszego procesu
			{
				if (processes[i].execTime < min)
				{
					min = processes[i].execTime;
					tmpi = i;
				}
			}
			else if(processes[i].arrivalTime > curr_time)
				break;
		}

		if(tmpi==-1) //sprawdzian czy i ma włąściwą wartość
		{
			curr_time++;
			continue;
		}

		processes[tmpi].waitingTime = curr_time - processes[tmpi].arrivalTime;
		curr_time += processes[tmpi].execTime; //process execute
		processes[tmpi].done = true;
		n++;
	}

	if (!Process::isAllDone(processes)) throw new std::exception("Error: not all processes were executed"); //sprawdzanie czy wszystkie procesy zostały wykonane
	
	for (int i = 0; i < processes.size(); i++) //wyliczanie średniego czasu oczekiwania
	{
		sum += processes[i].waitingTime;
	}

	return (double)sum / processes.size();
}