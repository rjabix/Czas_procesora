// Czas_procesora_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <map>
#include <tuple>
#include "Generator_danych.h"
//import algorytmów do symulacja czasu procesora
#include "Process.h"
#include "FirstComeFirstServe.h"
#include "ShortestJobFirst.h"
#include "LastComeFirstServe.h"
//import algorytmów do algorytmów zastępowania stron
#include "LeastRecentlyUsed.h"
#include "FirstInFirstOut.h"

using namespace std;

int main()
{
	Generator_danych::generuj_dane(150, 1, 10, 1, 50, 5, 15, 10); //generowanie danych do pliku dane.txt.zakomentować, jeśli nie ma potrzeby generowania danych

	FILE* f = fopen("dane.txt", "rt");
	if (f == NULL) //sprawdzanie czy plik istnieje
	{
		cout << "Nie udało się otworzyć pliku" << endl;
		return 0;
	}

	int k = 0;
	while (!feof(f)) //wczytywanie danych z pliku dane.txt
	{
		int arr, exec;

		if (fscanf(f, "%d %d", &arr, &exec) != 2) break; //jeśli nie udało się wczytać danych, to kończymy wczytywanie. fscanf zwraca ilość wczytanych danych, jeśli jest różna od 2, to kończymy wczytywanie (może być \n na końcu pliku)

		cout << "Procces " << k << " Arrival Time: " << arr << " Execute time: " << exec << endl;
		k++;
	}
	fclose(f);
	cout << "\n\n";


	//--------------------ALGORYTMY SYMULACJI CZASU PROCESORA--------------------



	map<string, double> results{
		  {"FCFS", 0.0},
		  {"LCFS", 0.0},
		  {"SJF", 0.0}
	};

	results["FCFS"] = FirstComeFirstServe::FCFS(); //First Come First Serve

	cout << "\nPress any key to continue...";
	//getchar(); //zaczekać nacisniecie klawisza

	results["LCFS"] = LastComeFirstServe::LCFS(); //Last Come First Serve
	cout<< "\nPress any key to continue...";

	results["SJF"]= ShortestJobFirst::SJF(); //Shortest Job First

	cout << "\nPress any key to continue...";
	//getchar();

	cout << "\nRóżnica czasów oczekiwania FCFS - SJF: " << results["FCFS"] - results["SJF"] << endl;
	cout << "Różnica czasów oczekiwania LCFS - SJF: " << results["LCFS"] - results["SJF"] << endl;
	cout << "Różnica czasów oczekiwania FCFS - LCFS: " << results["FCFS"] - results["LCFS"] << endl;

	f = fopen("wyniki.csv", "at"); //zapisanie wyników do pliku
    fprintf(f, "%d,%f,%f,%f,%f,%f,%f\n", k, results["FCFS"], results["LCFS"], results["SJF"], results["FCFS"] - results["SJF"], results["LCFS"] - results["SJF"], results["FCFS"] - results["LCFS"]);
	fclose(f); //illosc danych, FCFS, LCFS, SJF, różnica FCFS-SJF, różnica LCFS-SJF, różnica FCFS-LCFS



	//--------------------ALGORYTMY ZASTĘPOWANIA STRON--------------------



	auto replacement_results = LeastRecentlyUsed::LRU(); //Least Recently Used
	cout << "Algorytmy zastępowania stron: \n\n\tLRU:\nIllość błędów = " << get<0>(replacement_results) <<"\nSuccess rate = " << (double) get<1>(replacement_results)/(get<0>(replacement_results)+get<1>(replacement_results)) *100 <<"%\n";
	
	f = fopen("wyniki_zastepowania.csv", "at"); //zapisanie wyników do pliku
	fprintf(f, "%d,%d,%d,%f", 
		get<2>(replacement_results), get<1>(replacement_results), get<0>(replacement_results) + get<1>(replacement_results), (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100);
		//page hits, number of pages, success rate	

	replacement_results = FirstInFirstOut::FIFO(); //First In First Out
	cout << "Algorytmy zastępowania stron: \n\n\tLRU:\nIllość błędów = " << get<0>(replacement_results) << "\nSuccess rate = " << (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100 << "%\n";
	fprintf(f, ",%d,%d,%d,%f\n", 
		get<2>(replacement_results), get<1>(replacement_results), get<0>(replacement_results) + get<1>(replacement_results), (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100);
		//page hits, number of pages, success rate
	fclose(f);
}