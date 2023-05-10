
using namespace std;

#include <iostream>
#include "TablaSimbolos.h"

TablaSimbolos::TablaSimbolos(TablaSimbolos *padre)
{
      this->padre = padre;
}

bool TablaSimbolos::buscarAmbito(Simbolo s)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == s.nombre)
          return true;
     return false;
}

bool TablaSimbolos::newSymb(Simbolo s)
{
     if (buscarAmbito(s))  // repetido en el ámbito
       return false;
     simbolos.push_back(s);
     return true;
}

Simbolo* TablaSimbolos::searchSymb(string nombre)
{
     for (unsigned i=0;i<simbolos.size();i++)
       if (simbolos[i].nombre == nombre) return &(simbolos[i]);
       
     if (padre != NULL)
       return padre->searchSymb(nombre);
     else
       return NULL;
}

void TablaSimbolos::imprimir()
{
  cout << "nombre" << '\t' << "tipo" << '\t' << "tam" << '\t' << "dir" << endl;
  for (auto simb: simbolos)
    cout << simb.nombre << '\t' << simb.tipo << '\t' << simb.tam << '\t' << simb.dir << endl;
}
