
#include <iostream>

#include "TablaTipos.h"

TablaTipos::TablaTipos()
{
  // inicializar con los tipos básicos
  unTipo b {TIPOBASICO, 0, 0};
  
  b.tipoBase = ENTERO;  
  tipos.push_back(b);
  
  b.tipoBase = REAL;    
  tipos.push_back(b);

  b.tipoBase = LOGICO;  
  tipos.push_back(b);
}

unsigned TablaTipos::nuevoTipoArray(unsigned tam, unsigned tbase)
{  
  tipos.push_back({ARRAY, tam, tbase});
  return tipos.size()-1;
}

void TablaTipos::imprimir()
{
  
  cout << "tipo\tclase\ttamaño\ttipoBase\n";
  for (auto i = 0; i < tipos.size(); ++i)
      cout << i << '\t' << tipos[i].clase << " ->\t" << tipos[i].tamanyo << '\t' << tipos[i].tipoBase << endl;
}
