#include "instancja.h"
#include <iostream>

int main()
{
    int rozmiar = 20;
    Instancja* wzorcowa = new Instancja;
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
    if (nowaInstancja[-1].poleChar == instancjaZPliku[-1].poleChar)
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
