#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>
#include <cstdio>

int** alokujTablice2D(uint16_t wiersze, uint16_t kolumny)
{
    int** tab2D = new int* [wiersze + 1];
    int rozmiar = 0;

    rozmiar = wiersze;
    rozmiar <<= 16;
    rozmiar |= kolumny;

    tab2D[0] = new int{ rozmiar };
    tab2D++;

    for (int i = 0; i < wiersze; i++)
    {
        tab2D[i] = new int[kolumny] {};
    }

    return tab2D;
}

void dealokujTablice2D(int** tablica, uint16_t wiersze)
{
    for (int i = 0; i < wiersze; i++)
    {
        delete[] tablica[i];
    }
    delete[](tablica - 1);
}

void zapiszTablice2DdoPliku(int** tablicka, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "w+b");
    if (plik == nullptr) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return;
    }

    int rozmiar = *tablicka[-1];
    fwrite(&rozmiar, sizeof(int), 1, plik);

    int maska = 0xFFFF;
    int kolumny = rozmiar & maska;
    int wiersze = rozmiar >> 16;

    for (int i = 0; i < wiersze; i++)
    {
        fwrite(tablicka[i], sizeof(int), kolumny, plik);
    }

    fclose(plik);
}

int** odczytajTablice2d(const char* nazwaPliku)
{
    int rozmiar = 0;
    FILE* plik = fopen(nazwaPliku, "r+b");
    if (plik == nullptr) {
        std::cerr << "Nie można otworzyć pliku do odczytu!" << std::endl;
        return nullptr;
    }

    fread(&rozmiar, sizeof(int), 1, plik);
    int maska = 0xFFFF;
    int kolumny = rozmiar & maska;
    int wiersze = rozmiar >> 16;

    int** tab2D = alokujTablice2D(wiersze, kolumny);
    for (int i = 0; i < wiersze; i++)
    {
        fread(tab2D[i], sizeof(int), kolumny, plik);
    }

    fclose(plik);
    return tab2D;
}

int main() {
    uint16_t wiersze = 10;
    uint16_t kolumny = 15;
    int** tablicka = alokujTablice2D(wiersze, kolumny);

    // Wypełnij tablicę przykładowymi danymi do zapisu i odczytu
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            tablicka[i][j] = i * kolumny + j;
        }
    }

    zapiszTablice2DdoPliku(tablicka, "mrowka.txt");
    int** odczytanaTablicka = odczytajTablice2d("mrowka.txt");

    // Wypisz zawartość zapisanej tablicy
    std::cout << "Zapisana tablica:" << std::endl;
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            std::cout << tablicka[i][j] << " ";
        }
        std::cout << std::endl;
    }

    // Wypisz zawartość odczytanej tablicy
    std::cout << "\nOdczytana tablica:" << std::endl;
    for (int i = 0; i < wiersze; i++)
    {
        for (int j = 0; j < kolumny; j++)
        {
            std::cout << odczytanaTablicka[i][j] << " ";
        }
        std::cout << std::endl;
    }

    dealokujTablice2D(tablicka, wiersze);
    dealokujTablice2D(odczytanaTablicka, wiersze);

    return 0;
}
