#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <bitset>
#include <cstdio>

using namespace std;

short* alokujTablice(short size)
{
    static short counter = 0;
    short* tablica = new short[size+1] {};
    tablica[0] = size << 8| counter;
    counter++;
    return (tablica+1);
}

void zapiszTablice(short* tablica, const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "w+b");
    if (plik == nullptr) {
        cerr << "Błąd otwarcia pliku do zapisu\n";
        return;
    }

    // Najpierw zapisujemy rozmiar tablicy i licznik
    short zlaczenie = tablica[-1];
    uint16_t rozmiar = zlaczenie;
    rozmiar >>= 8;
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


void odczytajPlik(const char* nazwaPliku)
{
    FILE* plik = fopen(nazwaPliku, "r+b");
    if (plik == nullptr) {
        cerr << "Błąd otwarcia pliku do odczytu\n";
        return;
    }
    short zlaczenie;
    fread(&zlaczenie, sizeof(short), 1, plik);
    cout << "odczyt zlaczenia z pliku: " << bitset<16>(zlaczenie)<<"\n";
    short czesc1 = (zlaczenie >> 8);
    uint16_t maska = 0x00C8;
    short rozmiar = (czesc1 & maska);
    cout << "rozmiar z pliku: " << bitset<16>(rozmiar) << "\nBez bitsetu z pliku: " << rozmiar << "\n";
    uint16_t licznik = zlaczenie & 0xFF;

    cout << "Rozmiar: " << rozmiar << ", Licznik: " << licznik << endl;
    short* tablica = new short[rozmiar];
    fread(tablica, sizeof(short), rozmiar, plik);

    // Wyświetlamy zawartość tablicy
    for (int i = 0; i < rozmiar; i++)
    {
        cout << tablica[i] << ", ";
    }
    cout << endl;

    delete[] tablica;

    fclose(plik);
}

void odczytajRozmiarILicznik(short* tablica) {
    uint16_t zlaczenie = *(tablica - 1);
    short size = zlaczenie >> 8;
    uint16_t licznik = zlaczenie & 0xFF;
    cout << "Rozmiar: " << size << ", Licznik: " << licznik << endl;
}


int main()
{
    short size = 200;
    short* wskaznikNaTablice = alokujTablice(size);
    short* wskaznikNaTablice1 = alokujTablice(size);
    //cout << "16/8: " << bitset<16>(wskaznikNaTablice1[-1]) << "\n";
    zapiszTablice(wskaznikNaTablice, "faddtek.txt");
    zapiszTablice(wskaznikNaTablice1, "maciek.txt");
    odczytajPlik("faddtek.txt");
    odczytajPlik("maciek.txt");
    delete[](wskaznikNaTablice - 1);
    delete[](wskaznikNaTablice1 - 1);

}
