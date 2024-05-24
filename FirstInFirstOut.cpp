#define _CRT_SECURE_NO_WARNINGS
#include "FirstInFirstOut.h"
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>

std::tuple<int, int, int>FirstInFirstOut::FIFO() {
	FILE* f = fopen("dane_pages.txt", "rt");

	if (f == NULL) {                                                //sprawdzanie czy plik istnieje
		std::cout << "Nie udało się otworzyć pliku" << std::endl;
		throw new std::exception("Nie udało się otworzyć pliku");
	}

	std::vector<int>reference_string;                               // wektor, który zawiera referencje stron
	int size;   												    // ilość stron w pamięci

	fscanf(f, "%d", &size);                                         // wczytywanie ilości stron
	while (!feof(f)) {                                              // wczytywanie referencji stron
		int page;
		if (fscanf(f, "%d", &page) != 1) break;
		reference_string.push_back(page);
	}
	fclose(f);

	std::vector<int> pages;                                         // tworzenie stosu stron, które są w pamięci
	pages.reserve(size);                                            // rezerwowanie pamięci dla wektora stron
	int PageFaults = 0, PageHits = 0;                               // ilość błędów stron i ilość sukcesów, będą zwracone

	for (int ref_page : reference_string) {                         // pętlia główna. ekwiwalent do (for ref_page in reference_string) w pythonie

		auto it = std::find(pages.begin(), pages.end(), ref_page);  //znajdowanie referencji strony w wektorze stron. Jeśli nie znajdzie, to zwróci pages.end(). W przeciwnym wypadku zwróci iterator na znalezioną stronę. std::find zwraca iterator na znalezioną stronę

		if (it != pages.end())										// jeśli ref_page jest znaleziona w wektorze stron
		{                                    
			PageHits++;                                             // zwiększ ilość sukcesów
		}
		else 
		{
			PageFaults++; 										    // zwiększ ilość błędów stron

			if (pages.size() < size) {							    // jeśli ilość stron w pamięci jest mniejsza od ilości stron w pamięci
				pages.push_back(ref_page); 					        // dodaj stronę
			}
			else {												    // jeśli ilość stron w pamięci jest równa ilości stron w pamięci
				pages.erase(pages.begin()); 					    // usuń pierwszą, najdłuższo nieużywaną stronę
				pages.push_back(ref_page); 					        // dodaj nową stronę na koniec wektora stron
			}
		}
	}
	return std::make_tuple(PageFaults, PageHits, size);				   // zwróć ilość błędów stron i ilość sukcesów oraz n pamięci w posatci krotki
}