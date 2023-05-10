
#ifndef _TablaTipos_
#define _TablaTipos_

#include <vector>

using namespace std;

#include "TablaSimbolos.h"

const unsigned  TIPOBASICO  = 0,
                ARRAY       = 1;

/*
  el constructor mete en el vector los tipos básicos, ENTERO y REAL
  de manera que las primeras posiciones del vector son siempre los
  tipos básicos, luego para saber si un tipo es básico sólo hay que
  ver si es menor o igual que el último de ellos (en este caso, REAL)
*/



struct unTipo {
  unTipo(unsigned clase, unsigned tamanyo, unsigned tipoBase)
  {
    this->clase = clase;
    this->tamanyo = tamanyo;
    this->tipoBase = tipoBase;
  }
  
  unsigned clase    {0};  // TIPOBASICO o ARRAY
  unsigned tamanyo  {0};
  unsigned tipoBase {0}; 
};

class TablaTipos {

  public:
  
     vector<unTipo> tipos;
     
     TablaTipos();
     unsigned nuevoTipoArray(unsigned tam,unsigned tbase);
     void imprimir();
};

#endif
