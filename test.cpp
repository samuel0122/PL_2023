#include <iostream>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

std::vector<int> vectorInts;
std::vector<std::string> vectorStrings;

struct Simbolo {
    Simbolo(std::string nombre, int tipo, std::string nomtrad)
    {
        this->nombre = nombre;
        this->tipo = tipo;
        this->nomtrad = nomtrad;
    }
    std::string nombre;
    int tipo;
    std::string nomtrad;
};


void rellenarVector()
{
    for(int i = 0; i < 15; i++)
        vectorInts.push_back(i);
    
    for(auto i: vectorInts)
        std::cout << i << " ";
    std::cout << '\n';
}

void printString(std::string s)
{
    std::cout << "Print string: " << s << '\n';
}

void testCharString()
{
    char * palabra1 = "Hola mundo";
    char * palabra2 = "Adiós mundo";

    vectorStrings.emplace_back(palabra1);
    vectorStrings.emplace_back(palabra2);

    for(auto i: vectorStrings)
        std::cout << i << " | ";
    std::cout << '\n';

    std::cout << "Concat: " + std::string(palabra1) + "\n";
    printString(palabra2);

    std::cout << strcmp(palabra1,"Hola mundo") << "; " << strcmp("Hola pedo",palabra1) << '\n';
}

void testStrings()
{
    std::string palabra = "";

    std::cout << "Palabra es vacio: " << (palabra == "") << '\n';
    
    palabra = "main";
    std::cout << "Palabra es vacio: " << (palabra == "") << '\n';
    std::cout << "Palabra es main: " << (palabra == "main") << '\n';
    std::cout << "Palabra es pepe: " << (palabra == "pepe") << '\n';
}

void printSimbolo(Simbolo simb)
{
    std::cout << simb.nombre << " " << simb.tipo << " " << simb.nomtrad << '\n';
}

int main()
{
    rellenarVector();
    vectorInts.clear();
    rellenarVector();

    testStrings();
    testCharString();

    printSimbolo({"Pepe", 2, "PepeTrad"});

    std::string palabra = "";
    std::cout << palabra.empty() << '\n';
    palabra = "PEPE";
    std::cout << palabra.empty() << '\n';

    return 0;
}