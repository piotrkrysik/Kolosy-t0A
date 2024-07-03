#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>

struct Instancja
{
    float poleFloat;
    char poleChar;
};

Instancja* alokujTabliceInstancji(int rozmiar,Instancja* wzorcowa)
{
    Instancja* instancyjka = new Instancja[rozmiar+1];
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
        fprintf(plik, "%f;%c\n", tablica[i].poleFloat,tablica[i].poleChar);
    }
    fclose(plik);
}

Instancja* odczytajTabliceZPliku(const char* nazwaPliku,Instancja* wzorcowa)
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

int main()
{
    int rozmiar = 20;
    Instancja* wzorcowa= new Instancja;
    wzorcowa->poleFloat = 12.66;
    wzorcowa->poleChar = 'b';
    Instancja* nowaInstancja = alokujTabliceInstancji(rozmiar, wzorcowa);
    zapiszTabliceDoPliku(nowaInstancja, "rybka.txt");
    Instancja* instancjaZPliku = odczytajTabliceZPliku("rybka.txt", wzorcowa);
    for (int i = 0; i < rozmiar; i++)
    {
        std::cout << nowaInstancja[i].poleFloat << "\n";
        std::cout << nowaInstancja[i].poleChar << "\n";
    }
    for (int i = 0; i < rozmiar; i++)
    {
        std::cout << instancjaZPliku[i].poleFloat << "\n";
        std::cout << instancjaZPliku[i].poleChar << "\n";
    }
    if (nowaInstancja[-1].poleChar==instancjaZPliku[-1].poleChar)
    {
        int inne = 0;
        std::cout << "Taki sam rozmiar" << "\n";
        for (int i = 0; i < ((int)nowaInstancja[-1].poleChar); i++)
        {
            if (nowaInstancja[i].poleFloat != instancjaZPliku[i].poleFloat && nowaInstancja[i].poleChar != instancjaZPliku[i].poleChar)
            {
                std::cout << "\ninne\n";
                inne++;
                if (inne != 0)
                {
                    break;
                }
            }
        }
        if (inne == 0)
        {
            std::cout << "takie same";
        }
    }
    else
    {
        std::cout << "Nie takie same(Inny rozmiar)" << "\n";
    }
    delete wzorcowa;
    wzorcowa = nullptr;
    zwolnijTablice(nowaInstancja);
    zwolnijTablice(instancjaZPliku);
}
