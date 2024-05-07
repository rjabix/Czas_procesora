#define _CRT_SECURE_NO_WARNINGS
#include "Generator_danych.h"
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

void Generator_danych::generuj_dane(int size, int min_exec, int max_exec, int min_arr, int max_arr) //najpierw czas wykonania, potem czas przybycia
{
	struct Data
	{
		int arr;
		int exec;
	};
	srand(time(NULL));
	FILE *f = fopen("dane.txt", "wt");
	if (min_arr > max_arr || min_exec > max_exec || min_arr > max_arr || min_exec<0 || max_exec < 0 || size < 0)
	{
		cout << "Błędne dane" << endl;
		return;
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
}
// Path: Process.cpp