#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>

struct dwaPola
{
    int Pole1;
    double Pole2;
};

dwaPola* alokujTabliceStruktur(int rozmiar, dwaPola instancjaWzorcowa)
{
    dwaPola* tablica = new dwaPola[rozmiar];
    // Kopiowanie instancji wzorcowej do każdego elementu tablicy
    for(int i = 0; i < rozmiar; ++i)
    {
        tablica[i].Pole1 = instancjaWzorcowa.Pole1;
        tablica[i].Pole2 = instancjaWzorcowa.Pole2;
    }

    return tablica;
}

void wypelnij(dwaPola& dp, int Pole1, double Pole2)
{
    dp.Pole1 = Pole1;
    dp.Pole2 = Pole2;
}


void zapiszTabliceDoPliku(dwaPola* tablica, const char* nazwaPliku, int rozmiar)
{
    FILE* plik = fopen(nazwaPliku, "w");
    fprintf(plik, "%d\n", rozmiar);
    for (int i = 0; i < rozmiar; ++i)
    {
        fprintf(plik,"%d;%lf\n", tablica->Pole1, tablica->Pole2);
    }
    fclose(plik);
}

dwaPola* odczytajTablickeZPliczku(const char* nazwaPliczku)
{
    int rozmiar;
    FILE* plik = fopen(nazwaPliczku, "r");
    fscanf(plik, "%d\n", &rozmiar);
    dwaPola* tablickaZPliczku = new dwaPola[rozmiar];
    std::cout << "rozmiar odczytany z pliczku: " << rozmiar << "\n";
    for (int i = 0; i < rozmiar; i++)
    {
        fscanf(plik, "%d; %lf\n", &tablickaZPliczku[i].Pole1, &tablickaZPliczku[i].Pole2);
    }
    fclose(plik);
    return tablickaZPliczku;
}
bool porownajBinarne(const dwaPola* a, const dwaPola* b)
{
    return (memcmp(a, b, sizeof(dwaPola)) == 0);
}


int main()
{
    int rozmiar = 'K';
    dwaPola instancjaWzorcowa{10, 87.93 };
    dwaPola* strukturka = alokujTabliceStruktur(rozmiar, instancjaWzorcowa);
    zapiszTabliceDoPliku(strukturka, "piesek.txt", rozmiar);
    dwaPola* tabliczkaZPliczku = odczytajTablickeZPliczku("piesek.txt");
    std::cout << "Oryginal:\n";
    for (int i = 0; i < rozmiar; ++i) {
        std::cout << "Element " << i << ": Pole1 = " << strukturka[i].Pole1 << ", Pole2 = " << strukturka[i].Pole2 << "\n";
    }
    std::cout << "\nZ pliczku:\n";
    for (int i = 0; i < rozmiar; ++i) {
        std::cout << "Element " << i << ": Pole1 = " << tabliczkaZPliczku[i].Pole1 << ", Pole2 = " << tabliczkaZPliczku[i].Pole2 << "\n";
    }
    if (porownajBinarne(strukturka, tabliczkaZPliczku))
    {
        std::cout << "Takie same" << "\n";
    }
    else
    {
        std::cout << "Nie takie same" << "\n";
    }
    delete[] strukturka;
    delete[] tabliczkaZPliczku;
}
