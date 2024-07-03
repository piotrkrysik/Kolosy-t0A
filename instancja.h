#pragma once
struct Instancja
{
    float poleFloat;
    char poleChar;
};

Instancja* alokujTabliceInstancji(int rozmiar, Instancja* wzorcowa);
void zwolnijTablice(Instancja* tablica);
void zapiszTabliceDoPliku(Instancja* tablica, const char* nazwaPliku);
Instancja* odczytajTabliceZPliku(const char* nazwaPliku, Instancja* wzorcowa);
