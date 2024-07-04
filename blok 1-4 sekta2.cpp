#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>
#include <cstdio>

using namespace std;

short* alokujTablice(short size)
{
    if (size <= 0) return nullptr;
    static short counter = 0;
    short* tablica = new short[size+1] {};
    tablica[0] = counter << 8| size;
    counter++;
    return (tablica+1);
}

void dealokujTablice(short* tablica)
{
    delete[](tablica - 1);
    tablica = nullptr;
}

void zapiszTablice(short* tablica, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "w+b");
    if (plik == nullptr || tablica == nullptr) {
        cerr << "Błąd otwarcia pliku do zapisu\n";
        return;
    }

    // Najpierw zapisujemy rozmiar tablicy i licznik
    short zlaczenie = tablica[-1];
    uint16_t rozmiar = zlaczenie;
    short maska = 0xFF;
    rozmiar = rozmiar & maska;
    cout << "zlaczenie: " << bitset<16>(zlaczenie) << "\n";
    cout << "rozmiar: " << bitset<16>(rozmiar) << "\nBez bitsetu: "<<rozmiar << "\n";
    fwrite(&zlaczenie, sizeof(short), 1, plik);
    //Zapisujemy zawartość tablicy
    size_t napisano = fwrite(tablica, sizeof(short), rozmiar, plik);
    if (napisano != rozmiar) {
        cerr << "Błąd zapisu zawartości tablicy do pliku\n";
        fclose(plik);
        return;
    }

    fclose(plik);
}


short* odczytajPlik(const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "r+b");
    if (plik == nullptr) {
        cerr << "Błąd otwarcia pliku do odczytu\n";
        return nullptr;
    }
    short zlaczenie;
    fread(&zlaczenie, sizeof(short), 1, plik);
    cout << "odczyt zlaczenia z pliku: " << bitset<16>(zlaczenie)<<"\n";
    short czesc1 = zlaczenie;
    uint16_t maska = 0xFF;
    short rozmiar = (czesc1 & maska);
    cout << "rozmiar z pliku: " << bitset<16>(rozmiar) << "\nBez bitsetu z pliku: " << rozmiar << "\n";

    cout << "Rozmiar: " << rozmiar << endl;
    short* tablica = alokujTablice(rozmiar);
    fread(tablica, sizeof(short), rozmiar, plik);

    //// Wyświetlamy zawartość tablicy
    //for (int i = 0; i < rozmiar; i++)
    //{
    //    cout << tablica[i] << ", ";
    //}
    //cout << endl;

    //delete[] tablica;

    fclose(plik);

    return tablica;
}

short odczytajRozmiar(short* tablica) {
    uint16_t zlaczenie = *(tablica - 1);
    short size = zlaczenie;
    size = zlaczenie & 0xFF;
    
    return size;
}

bool porownajBinarne(short *a, short* b)
{
    short rozmiarA = odczytajRozmiar(a);
    short rozmiarB = odczytajRozmiar(b);

    std::cout << " Porownanie rozmiarow tablic: " << rozmiarA << " " << rozmiarB;

    if (rozmiarA == rozmiarB) {

        return (memcmp(a, b, rozmiarA * sizeof(short)) == 0);
    }
    else return false;
}

void generujTablice(short* tab)
{
    for (int i = 0; i < odczytajRozmiar(tab); i++) {
        tab[i] = rand() % 100;
    }
}


void odczytajTablice(short* tab)
{
    for (int i = 0; i < odczytajRozmiar(tab); i++) {
        std::cout << " " << tab[i];
    }
}

int main()
{
    srand(time(NULL));

    short size = 20;
    short* wskaznikNaTablice = alokujTablice(size);
    short* wskaznikNaTablice1 = alokujTablice(size+ 10); 
    short* wskaznikNaTablice2 = alokujTablice(size + 20);

    generujTablice(wskaznikNaTablice);
    generujTablice(wskaznikNaTablice1);
    generujTablice(wskaznikNaTablice2);
    std::cout << " Odczytywanie tablic:\n";
    odczytajTablice(wskaznikNaTablice); std::cout << "\n";
    odczytajTablice(wskaznikNaTablice1); std::cout << "\n";
    odczytajTablice(wskaznikNaTablice2); std::cout << "\n";

    //cout << "16/8: " << bitset<16>(wskaznikNaTablice1[-1]) << "\n";
    std::cout << " ZAPIS:\n "; 
    zapiszTablice(wskaznikNaTablice2, "kutek.txt");
    std::cout << " ODCZYT:\n ";
    short* wskaznikNaTablice3 = odczytajPlik("kutek.txt");

    if (porownajBinarne(wskaznikNaTablice3, wskaznikNaTablice2))
    {
        std::cout << "\nTakie same" << "\n";
    }
    else
    {
        std::cout << "Nie takie same" << "\n";
    }

    dealokujTablice(wskaznikNaTablice);
    dealokujTablice(wskaznikNaTablice1);
    dealokujTablice(wskaznikNaTablice2);
    dealokujTablice(wskaznikNaTablice3);
}
