#define _CRT_SECURE_NO_WARNINGS
#include "LeastRecentlyUsed.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <tuple>

std::tuple<int, int, int>LeastRecentlyUsed::LRU() {
    FILE *f = fopen("dane_pages.txt", "rt");

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

    std::vector<int> pages;                                         // tworzenie wektora stron, które są w pamięci
    pages.reserve(size);                                            // rezerwowanie pamięci dla wektora stron   
    int PageFaults = 0, PageHits = 0;                               // ilość błędów stron i ilość sukcesów, będą zwracone

    for (int ref_page : reference_string) {                         // pętlia główna. ekwiwalent do (for ref_page in reference_string) w pythonie

        auto it = std::find(pages.begin(), pages.end(), ref_page);  //znajdowanie referencji strony w wektorze stron. Jeśli nie znajdzie, to zwróci pages.end(). W przeciwnym wypadku zwróci iterator na znalezioną stronę. std::find zwraca iterator na znalezioną stronę

        if (it != pages.end()) 
        {                                                           // jeśli ref_page jest znaleziona w wektorze stron
            PageHits++;                                             // zwiększ ilość sukcesów
            pages.erase(it);                                        // usuń tą stronę
            pages.push_back(ref_page);                              // dodaj tą stronę na koniec wektora stron
        }
        else 
        {
            PageFaults++; 										    // zwiększ ilość błędów stron

            if (pages.size() < size) {							    // jeśli ilość stron w pamięci jest mniejsza od ilości stron w pamięci
                pages.push_back(ref_page); 					        // dodaj stronę na koniec wektora stron
            }
            else {												    // jeśli ilość stron w pamięci jest równa ilości stron w pamięci
                pages.erase(pages.begin()); 					    // usuń pierwszą, najdłuższo nieużywaną stronę
                pages.push_back(ref_page); 					        // dodaj nową stronę na koniec wektora stron
            }
        }
    }
	return std::make_tuple(PageFaults, PageHits, size);				   // zwróć ilość błędów stron i ilość sukcesów oraz n pamięci w posatci krotki
}
/*
    Ogólny opis implementacji tego algorytmu LRU:
    1. Jeśli strony nie ma w pamięci, to dodajmy ją do końca wektora stron.
    2. Im bliżej strona w pamięci jest do początku wektora, tym dłużej jest nieużywana.
    3. Jeśli nowej strony nie ma w pamięci i miejsca już nie ma, to wyczyszczamy pierwszą stronę z wektora,
       (to znaczy, że była najwięcej czasu nieużywana), i dodaj nową stronę na koniec wektora. -> (najmniej czasu od ostatniego użycia).
    4. Reszta stron automatycznie się przesuwa w lewo, bliżej do początku.
*/