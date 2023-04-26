
using namespace std;
#include <iostream>
#include "TablaSimbolos.h"

TablaSimbolos::TablaSimbolos(TablaSimbolos *padre)
{
      this->padre = padre;
}

Simbolo *TablaSimbolos::buscarAmbito(string nombre)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == nombre)
          return &(simbolos[i]);
     return NULL;
}

bool TablaSimbolos::nuevoSimbolo(Simbolo s)
{
     if (buscarAmbito(s.nombre)!=NULL)  // repetido en el ámbito
       return false;
     simbolos.push_back(s);
     cout << "Saved simbol: " << s.nombre << ' ' << s.nomtrad << ' ' << s.tipo << '\n';
     return true;
}

Simbolo* TablaSimbolos::buscar(string nombre)
{
     cout << "SEARCHING FOR simbol: " << nombre << '\n';

     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == nombre){
         cout << "FOUND!\n";
         return &(simbolos[i]);
       }
     if (padre != NULL)
       return padre->buscar(nombre);
     else
       return NULL;
}
