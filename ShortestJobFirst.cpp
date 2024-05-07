﻿#define _CRT_SECURE_NO_WARNINGS
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
		return 0;
	}

	std::cout << "SJF algorithm\n\n";
	while (!feof(f)) //wczytywanie danych z pliku
	{
		int arr, exec, i = 0;

		if (fscanf(f, "%d %d", &arr, &exec) != 2) break; //jeśli nie udało się wczytać danych, to kończymy wczytywanie. fscanf zwraca ilość wczytanych danych, jeśli jest różna od 2, to kończymy wczytywanie (może być \n na końcu pliku)
		processes.push_back(Process(i, arr, exec));
		i++;
	}
	fclose(f);

	std::sort(processes.begin(), processes.end(), [](Process a, Process b) {return a.arrivalTime < b.arrivalTime; }); //sortowanie procesów po czasie przybycia, jeśli plik jest stworzony ręcznie

	int curr_time = 0;
	int sum = 0, n = 0; //n-current process iterator, sum - dla wyliczania średniego czasu oczekiwania
	
	while (!isAllDone(processes)) //pętlia główna. .back() zwraca ostatni element z wektora, done - zmienna, która mówi, czy proces się zakończył
	{
		if (curr_time < processes[n].arrivalTime) //jeśli teraźniejszy czas jest mniejszy od czasu przybycia procesu, to odrazu robimy tak, żeby czas był równy czasowi przybycia
			curr_time = processes[n].arrivalTime;

		int tmpi = -1, min = INT_MAX; //indeks procesu o minimalnym czasie pracy

		for (int i = 0; i < processes.size(); i++) //dodawanie procesow, którzy już nadeszli, do kolejki
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
			n++;
			continue;
		}

		processes[tmpi].waitingTime = curr_time - processes[tmpi].arrivalTime;
		curr_time += processes[tmpi].execTime; //process execute
		processes[tmpi].done = true;
		n++;
	}

	std::cout << "\nProcess\tWaiting time\n";
	for (int i = 0; i < processes.size(); i++) //wyliczanie średniego czasu oczekiwania
	{
		sum += processes[i].waitingTime;
		std::cout << "Process " << i << " Waiting time: " << processes[i].waitingTime << std::endl; //zakomentować jeśli nie chcemy wyświetlać czasu oczekiwania każdego elementu
	}

	std::cout << "Średni czas oczekiwania: " << (double)sum / processes.size() << std::endl;
	return (double)sum / processes.size();
}

bool ShortestJobFirst::isAllDone(std::vector<Process> processes) //funkcja sprawdzająca, czy wszystkie procesy zostały wykonane
{
	for (int i = 0; i < processes.size(); i++)
	{
		if (!processes[i].done)
			return false;
	}
	return true;
}