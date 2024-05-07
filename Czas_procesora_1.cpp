// Czas_procesora_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Process.h"
#include "Generator_danych.h"
#include "FirstComeFirstServe.h"

using namespace std;

int main()
{
    //Process *p1 = new Process(1, 2, 3);
    //cout << p1->execTime;
    // 
    //Generator_danych::generuj_dane(10, 1, 10, 1, 10);

    FirstComeFirstServe::FCFS(); //First Come First Serve
    cout<< "\nPress any key to continue...";
    getchar(); //zaczekać nacisniecie klawisza
}