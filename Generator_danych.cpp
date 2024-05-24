#define _CRT_SECURE_NO_WARNINGS
#include "Generator_danych.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void Generator_danych::generuj_dane(int seed, int size, int min_exec, int max_exec, int min_arr, int max_arr, int memory_capacity, int pages_number, int pages_reference_number) //najpierw czas wykonania, potem czas przybycia
{
	struct Data //dane, które będziemy generować dla procesów
	{
		int arr;
		int exec;
	};
	srand(time(NULL) + static_cast<long long>(seed*seed*3));
	FILE *f = fopen("dane.txt", "wt");
	if (min_arr > max_arr || min_exec > max_exec || min_arr > max_arr || min_exec<0 || max_exec < 0 || size < 0)
	{
		cout << "Błędne dane" << endl;
		throw new std::exception("Błędne dane");
	}
	Data *data = new Data[size];
	for (int i = 0; i < size; i++)
	{
		data[i].arr = rand() % (max_arr - min_arr + 1) + min_arr;
		data[i].exec = rand() % (max_exec - min_exec + 1) + min_exec;
	}
	sort(data, data + size, [](Data a, Data b) {return a.arr < b.arr; });
	for (int i = 0; i < size; i++)
	{
		fprintf(f, "%d %d\n", data[i].arr, data[i].exec); //najpierw czas przybycia, potem czas wykonania
	}
	fclose(f);
	delete[] data;

	//generowanie danych dla stron
	f = fopen("dane_pages.txt", "wt");
	if (f == NULL)
	{
		cout << "Nie udało się otworzyć pliku" << endl;
		return;
	}
	fprintf(f, "%d\n", memory_capacity);
	for (int i = 0; i < pages_number; i++) //generowanie "pages_number" stron
	{
		fprintf(f, "%d\n", rand() % pages_reference_number); //generowanie referencji stron od 0 do pages_reference_number
	}
	fclose(f);
}
// Path: Process.cpp