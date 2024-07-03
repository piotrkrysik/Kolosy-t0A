#include "instancja.h"
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>

Instancja* alokujTabliceInstancji(int rozmiar, Instancja* wzorcowa)
{
    Instancja* instancyjka = new Instancja[rozmiar + 1];
    instancyjka->poleChar = rozmiar;
    instancyjka++;
    for (int i = 0; i < rozmiar; i++)
    {
        instancyjka[i].poleFloat = wzorcowa->poleFloat;
        instancyjka[i].poleChar = wzorcowa->poleChar;
    }
    return instancyjka;
}

void zwolnijTablice(Instancja* tablica)
{
    delete[](tablica - 1);
    tablica = nullptr;
}

void zapiszTabliceDoPliku(Instancja* tablica, const char* nazwaPliku)
{
    int rozmiar;
    FILE* plik = fopen(nazwaPliku, "w");
    rozmiar = tablica[-1].poleChar;
    fprintf(plik, "%d\n", rozmiar);
    for (int i = 0; i < rozmiar; i++)
    {
        fprintf(plik, "%f;%c\n", tablica[i].poleFloat, tablica[i].poleChar);
    }
    fclose(plik);
}

Instancja* odczytajTabliceZPliku(const char* nazwaPliku, Instancja* wzorcowa)
{
    int rozmiar;
    FILE* plik = fopen(nazwaPliku, "r");
    fscanf(plik, "%d\n", &rozmiar);
    Instancja* tablicka = alokujTabliceInstancji(rozmiar, wzorcowa);
    for (int i = 0; i < rozmiar; i++)
    {
        fscanf(plik, "%f;%c\n", &tablicka[i].poleFloat, &tablicka[i].poleChar);
    }
    return tablicka;
}