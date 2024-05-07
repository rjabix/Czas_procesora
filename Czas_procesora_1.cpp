// Czas_procesora_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include "Process.h"
#include "Generator_danych.h"
#include "FirstComeFirstServe.h"
#include "ShortestJobFirst.h"

using namespace std;

int main()
{
	//Process *p1 = new Process(1, 2, 3);
	//cout << p1->execTime;
	// 
	Generator_danych::generuj_dane(150, 1, 10, 1, 50); //generowanie danych do pliku dane.txt.zakomentować, jeśli nie ma potrzeby generowania danych

	FILE* f = fopen("dane.txt", "rt");
	if (f == NULL) //sprawdzanie czy plik istnieje
	{
		cout << "Nie udało się otworzyć pliku" << endl;
		return 0;
	}
	int k = 0;
	while (!feof(f)) //wczytywanie danych z pliku
	{
		int arr, exec;

		if (fscanf(f, "%d %d", &arr, &exec) != 2) break; //jeśli nie udało się wczytać danych, to kończymy wczytywanie. fscanf zwraca ilość wczytanych danych, jeśli jest różna od 2, to kończymy wczytywanie (może być \n na końcu pliku)

		cout << "Procces " << k << " Arrival Time: " << arr << " Execute time: " << exec << endl;
		k++;
	}
	fclose(f);
	cout<<"\n\n";

	double FCFS = FirstComeFirstServe::FCFS(); //First Come First Serve

	cout << "\nPress any key to continue...";
	getchar(); //zaczekać nacisniecie klawisza

	double SJF = ShortestJobFirst::SJF(); //Shortest Job First
	cout<< "\nPress any key to continue...";
	getchar(); //zaczekać nacisniecie klawisza
	cout<<"Różnica czasów oczekiwania: "<<FCFS-SJF<<endl;
}