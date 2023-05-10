

#ifndef _TablaSimbolos_
#define _TablaSimbolos_

#include <string>
#include <vector>

using namespace std;

const unsigned ENTERO = 0,
               REAL   = 1,
               LOGICO = 2;

struct Simbolo {
   Simbolo(string nombre, unsigned tipo, unsigned dir, unsigned tam)
   {
      this->nombre = nombre;
      this->tipo   = tipo;
      this->dir    = dir;
      this->tam    = tam;
   }

   Simbolo(string nombre)
   {
      this->nombre = nombre;
      this->tipo   = 0;
      this->dir    = 0;
      this->tam    = 0;
   }

   string nombre;
   unsigned tipo;
   unsigned dir;
   unsigned tam;
};


class TablaSimbolos {

   private:
   
      bool buscarAmbito(Simbolo s); // ver si está en el ámbito actual

   public:
   
      TablaSimbolos *padre;
      vector<Simbolo> simbolos;
   
      TablaSimbolos(TablaSimbolos *padre);
      TablaSimbolos *getAmbitoAnterior() { return padre; }

      bool newSymb(Simbolo s);
      Simbolo* searchSymb(string nombre);
      void imprimir();
};
   
#endif
