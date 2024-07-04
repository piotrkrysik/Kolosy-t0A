#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>

struct tablicaDynamiczna
{
    int* tablica;
    int rozmiar;
};

tablicaDynamiczna utworzStrukture(int size){
     tablicaDynamiczna tabDyn;
     tabDyn.rozmiar = size;
     tabDyn.tablica = new int[size] {};
     return tabDyn;
}

void zwolnijStrukture(tablicaDynamiczna& tabDyn)
{
    delete[] tabDyn.tablica;
    tabDyn.tablica = nullptr;
}

void zapiszTablice(tablicaDynamiczna& tab, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "w");
    if (plik == nullptr) {
        std::cerr << "Blad otwarcia pliku do zapisu!" << std::endl;
        exit(1);
    }
    fprintf(plik, "%d\n", tab.rozmiar);
    for (int i = 0; i < tab.rozmiar; i++)
    {
        fprintf(plik, "%d;", tab.tablica[i]);
    }
    fclose(plik);
}
    
tablicaDynamiczna odczytajTabliceZPliku(const char* nazwaPliku)
{
    int rozmiar;
    FILE* plik = fopen(nazwaPliku, "r");
    if (plik == nullptr) {
        std::cerr << "Blad otwarcia pliku do odczytu!" << std::endl;
        exit(1);
    }
    if (fscanf(plik, "%d\n", &rozmiar) != 1) {
        std::cerr << "Blad odczytu rozmiaru tablicy!" << std::endl;
        fclose(plik);
        exit(1);
    }
    std::cout << "rozmiar: " << rozmiar<<"\n";
    tablicaDynamiczna tabDynn = utworzStrukture(rozmiar);
    for (int i = 0; i < rozmiar; i++) {
        if (fscanf(plik, "%d;", &tabDynn.tablica[i]) != 1) {
            std::cerr << "Blad odczytu elementu tablicy na pozycji " << i << "!" << std::endl;
            fclose(plik);
            zwolnijStrukture(tabDynn);
            exit(1);
        }
    }

    fclose(plik);
    return tabDynn;
}

bool porownajTablice(const tablicaDynamiczna& tab1, const tablicaDynamiczna& tab2) {
    if (tab1.rozmiar != tab2.rozmiar) {
        return false;
    }

    for (int i = 0; i < tab1.rozmiar; i++) {
        if (tab1.tablica[i] != tab2.tablica[i]) {
            return false;
        }
    }

    return true;
}

int main()
{
    int size = 20;
    tablicaDynamiczna mojaTablica = utworzStrukture(size);

    // Wydrukowanie zawartości tablicy
    for (int i = 0; i < size; i++) {
        std::cout << mojaTablica.tablica[i] << " ";
    }
    std::cout << std::endl;

    zapiszTablice(mojaTablica, "kotek.txt");
    tablicaDynamiczna odczytanaTablica = odczytajTabliceZPliku("kotek.txt");

    for (int i = 0; i < odczytanaTablica.rozmiar; i++) {
        std::cout << odczytanaTablica.tablica[i] << " ";
    }
    std::cout << std::endl;
    if (porownajTablice(mojaTablica, odczytanaTablica)) {
        std::cout << "Tablice sa identyczne." << std::endl;
    }
    else {
        std::cout << "Tablice nie sa identyczne." << std::endl;
    }
    zwolnijStrukture(mojaTablica);
    zwolnijStrukture(odczytanaTablica);

}
