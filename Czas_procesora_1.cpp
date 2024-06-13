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
	int replays = 1, size = 150, min_exec = 1, max_exec = 10, min_arr = 0, max_arr = 50, memory_capacity = 5, pages_number = 15, pages_reference_number = 10; //znaczenia standartowe
	cout << "Podaj ilosc testow(1): ";
	cin >> replays;
	cout << "Wykorzystac standartowe wartosci? (y/n): ";
	char ans; cin >> ans;
	if (ans == 'n' || ans == 'N') {
		cout << "Podaj ilosc procesow(150): ";
		cin >> size;
		cout << "Podaj minimalny czas wykonania(1): ";
		cin >> min_exec;
		cout << "Podaj maksymalny czas wykonania(10): ";
		cin >> max_exec;
		cout << "Podaj minimalny czas przybycia(1): ";
		cin >> min_arr;
		cout << "Podaj maksymalny czas przybycia(50): ";
		cin >> max_arr;
		cout << "Podaj pojemnosc pamieci(5): ";
		cin >> memory_capacity;
		cout << "Podaj ogolna ilosc stron(15): ";
		cin >> pages_number;
		cout << "Podaj ilosc roznych referencji stron(10): ";
		cin >> pages_reference_number;
	}
	FILE* fout_czas = fopen("wyniki.csv", "wt");
	FILE* fout_pages = fopen("wyniki_zastepowania.csv", "wt");	//"wt" jeśli chcemy tylko rezultaty tego testu, "at" jeśli chcemy dodać
	if (fout_czas == NULL || fout_pages == NULL) throw new exception("Unable to open to out files.");

	for (int i = 0; i < replays; i++) {

		Generator_danych::generuj_dane(i, size, min_exec, max_exec, min_arr, max_arr, memory_capacity, pages_number, pages_reference_number); //generowanie danych do pliku dane.txt.zakomentować, jeśli nie ma potrzeby generowania danych



		//--------------------ALGORYTMY SYMULACJI CZASU PROCESORA--------------------



		map<string, double> results{
			  {"FCFS", 0.0},
			  {"LCFS", 0.0},
			  {"SJF", 0.0}
		};

		results["FCFS"] = FirstComeFirstServe::FCFS(); //First Come First Serve

		results["LCFS"] = LastComeFirstServe::LCFS(); //Last Come First Serve

		results["SJF"] = ShortestJobFirst::SJF(); //Shortest Job First

		/*
		cout << "Algorytmy symulacji czasu procesora: \n\n\tFCFS:\nŚredni czas oczekiwania = " << results["FCFS"] << endl;
		cout << "\n\tLCFS:\nŚredni czas oczekiwania = " << results["LCFS"] << endl;
		cout << "\n\tSJF:\nŚredni czas oczekiwania = " << results["SJF"] << endl;
		cout << "\nRóżnica czasów oczekiwania FCFS - SJF: " << results["FCFS"] - results["SJF"] << endl;
		cout << "Różnica czasów oczekiwania LCFS - SJF: " << results["LCFS"] - results["SJF"] << endl;
		cout << "Różnica czasów oczekiwania FCFS - LCFS: " << results["FCFS"] - results["LCFS"] << endl;
		*/

		fprintf(fout_czas, "%d,%f,%f,%f,%f,%f,%f\n", size, results["FCFS"], results["LCFS"], results["SJF"], results["FCFS"] - results["SJF"], results["LCFS"] - results["SJF"], results["FCFS"] - results["LCFS"]);
		//ilosc danych, FCFS, LCFS, SJF, różnica FCFS-SJF, różnica LCFS-SJF, różnica FCFS-LCFS



		//--------------------ALGORYTMY ZASTĘPOWANIA STRON--------------------



		auto replacement_results = LeastRecentlyUsed::LRU(); //Least Recently Used
		//cout << "Algorytmy zastępowania stron: \n\n\tLRU:\nIllość błędów = " << get<0>(replacement_results) << "\nSuccess rate = " << (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100 << "%\n";

		fout_pages = fopen("wyniki_zastepowania.csv", "at"); //zapisanie wyników do pliku
		fprintf(fout_pages, "%d,%d,%d,%f",
			get<2>(replacement_results), get<1>(replacement_results), get<0>(replacement_results) + get<1>(replacement_results), (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100);
		//memory_size, page hits, number of pages, success rate	

		replacement_results = FirstInFirstOut::FIFO(); //First In First Out
		//cout << "Algorytmy zastępowania stron: \n\n\tFIFO:\nIllość błędów = " << get<0>(replacement_results) << "\nSuccess rate = " << (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100 << "%\n";
		fprintf(fout_pages, ",%d,%d,%d,%f\n",
			get<2>(replacement_results), get<1>(replacement_results), get<0>(replacement_results) + get<1>(replacement_results), (double)get<1>(replacement_results) / (get<0>(replacement_results) + get<1>(replacement_results)) * 100);
		//memory_size, page hits, number of pages, success rate
	}
	fclose(fout_czas);
	fclose(fout_pages);
}