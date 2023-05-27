/*------------------------------ ejemplo.y -------------------------------*/
%token algoritmo dospto id falgoritmo
%token var fvar
%token pyc coma
%token entero real logico 
%token tabla nentero de
%token escribe lee si entonces sino 
%token mientras hacer repetir hasta 
%token blq fblq
%token opasig obool ybool oprel opas opmd
%token nreal pari pard nobool 
%token cierto falso cori cord


%{

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "TablaSimbolos.h"
#include "TablaTipos.h"


using namespace std;

#include "comun.h"

// variables y funciones del A. Léxico
extern int ncol,nlin,findefichero;

TablaSimbolos *tsActual = new TablaSimbolos(NULL);
TablaTipos *tt = new TablaTipos();
Simbolo *simbolo;



extern int yylex();
extern char *yytext;
extern FILE *yyin;


int yyerror(char *s);

// const int ENTERO  = 1,
//           REAL    = 2,
//           BOOLEAN = 3,
//           FUNCION = 4;

string operador, operadorTrad, s1, s2;  // string auxiliares
int tipo1, tipo2;
int numentero;

string nextLine {'\n'};

bool esArray(uint tipo) { return tt->tipos[tipo].clase == TablaTipos::ARRAY; }
uint tipoBase(uint tipo)  { return tt->tipos[tipo].tipoBase; }
uint tamanyoTipo(uint tipo)  { return tt->tipos[tipo].tamanyo; }

int   ASCII_C = 'c',
      ASCII_F = 'f';

int tmp, tmpcnv;
int ctemp {INIT_DIR_TEMP};
int nuevaTemp();

int cvar {INIT_DIR_VAR};
int nuevaVar(string nombreVar, int tamVar);

int etiq1, etiq2;
int cetiq {0};
int nuevaEtiqueta();

uint tam, dir, tipo;
%}

%%


S     : algoritmo dospto id SDec falgoritmo  { 
                                                /* comprobar que después del programa no hay ningún token más */
                                                int tk = yylex();
                                                if (tk != 0) yyerror("");
                                                std::cout << $4.cod + "halt";
                                                // tt->imprimir();
                                                // tsActual->imprimir();
                                             }
      ;


SDec  :  Dec SInstr  { $$.cod = $2.cod; }
      |  SInstr      { $$.cod = $1.cod; }
      ;

Dec   :  var MDVar fvar {} // No hay traducción de las variables que se inicializan
      ;

MDVar :  MDVar DVar  {} // No hay traducción de las variables que se inicializan
      |  DVar        {} // No hay traducción de las variables que se inicializan
      ;

DVar  :  Tipo dospto { $$.tipoH = $1.tipo; $$.tamH = $1.tam; } LId pyc  {}
      ;

LId   :  LId coma id    {  
                           tipo = $0.tipoH;        // tipoH
                           tam = $0.tamH;          // tam
                           s1 = string($3.lexema); // id
                           dir = nuevaVar(s1, tam);// dir

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, $3.nlin, $3.ncol, $3.lexema);
                           
                        }
      |  id             {
                           tipo = $0.tipoH;        // tipoH
                           tam = $0.tamH;          // tam
                           s1 = string($1.lexema); // id
                           dir = nuevaVar(s1, tam);// dir

                           if(!tsActual->newSymb({s1, tipo, dir, tam}))
                              errorSemantico(ERR_YADECL, $1.nlin, $1.ncol, $1.lexema);
                        }
      ;

Tipo  :  entero                  { $$.tipo = ENTERO; $$.tam = 1; }
      |  real                    { $$.tipo = REAL; $$.tam = 1; }
      |  logico                  { $$.tipo = LOGICO; $$.tam = 1; }
      |  tabla nentero de Tipo   { 
                                    numentero = stoi($2.lexema); 
                                    if(numentero <= 0) errorSemantico(ERR_DIM, $1.nlin, $1.ncol, $1.lexema);

                                    $$.tipo = tt->nuevoTipoArray(numentero, $4.tipo); 
                                    $$.tam = $4.tam * numentero; }
      ;

SInstr:  SInstr { $$.nlin = ctemp; } pyc Instr  { ctemp = $2.nlin; $$.cod = $1.cod + $4.cod;}
      |  { $$.nlin = ctemp; } Instr             { ctemp = $1.nlin; $$.cod = $2.cod; }
      ;

Instr :  escribe Expr                     {  if($2.tipo == LOGICO)
                                             {
                                                tmp = nuevaTemp();
                                                etiq1 = nuevaEtiqueta();
                                                etiq2 = nuevaEtiqueta();
                                                s1 = "mov A " + std::to_string($2.dir) + nextLine +
                                                      "jz L" + std::to_string(etiq1) +  nextLine +     // Si Z (false) salta
                                                      "wrc #" + std::to_string(ASCII_C) + nextLine +   // CASO TRUE
                                                      "jmp L" + std::to_string(etiq2) + nextLine +   // Salta al final
                                                      'L' + std::to_string(etiq1) + "\n" +
                                                      "wrc #" + std::to_string(ASCII_F) + nextLine +   // CASO FALSE
                                                      'L' + std::to_string(etiq2) + "\n";
                                             }
                                             else
                                                s1 = (($2.tipo == ENTERO) ? "wri " : "wrr ") + std::to_string($2.dir) + nextLine;
                                             
                                             $$.cod = $2.cod + s1 + "wrl\n";
                                          }
      |  lee Ref                          {  if(esArray($1.tipo)) errorSemantico(ERR_FALTAN, $2.nlin, $2.ncol, $2.lexema);
                                             if($2.tipo == LOGICO)
                                             {
                                                tmp = nuevaTemp();
                                                s1 =  "rdc A\n";                                      // Lee ASCII
                                                s1 += "eqli #" + std::to_string(ASCII_C)  + nextLine; // Mira si lo leído es C 
                                                s1 += "mov A " + std::to_string(tmp)      + nextLine; // Guarda en variable temporal
                                                s1 += "mov "   + std::to_string($2.dir)   + " A\n";   // Carga saltos en array de Ref
                                                s1 += "addi #" + std::to_string($2.dbase) + nextLine; // Añade dirección base
                                                s1 += "mov "   + std::to_string(tmp)      + " @A\n";  // Muebe variable temporal a A
                                             }  
                                             else
                                             {
                                                operador = (($2.tipo == ENTERO) ? "rdi " : "rdr ");
                                                s1 =  "mov " + std::to_string($2.dir)     + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string($2.dbase) + nextLine; // Añade dirección base
                                                s1 += operador + " @A\n";                             // Lee numero en Ref
                                             }
                                             
                                             $$.cod = $2.cod + s1;
                                             
                                          }
      |  si Expr { if($2.tipo != LOGICO) errorSemantico(ERR_EXP_LOG, $1.nlin, $1.ncol, $1.lexema); }
                  entonces Instr ColaIf   {  etiq1 = nuevaEtiqueta();
                                             etiq2 = nuevaEtiqueta();
                                             $$.cod =    $2.cod;                                      // Ejecuta Expr
                                             $$.cod +=   "mov " + std::to_string($2.dir)  + " A\n";   // Carga Expr
                                             $$.cod +=   "jz L" + std::to_string(etiq1)   + '\n';     // Salta a caso FALSE
                                             $$.cod +=   $5.cod;                                      // Caso TRUE
                                             $$.cod +=   "jmp L" + std::to_string(etiq2)  + '\n';     // Salta al final
                                             $$.cod +=   'L' + std::to_string(etiq1)      + "\n";     // Etiq FALSE
                                             $$.cod +=   $6.cod;                                      // Caso FALSE (sino)
                                             $$.cod +=   'L' + std::to_string(etiq2)      + "\n";     // Etiq final
                                          }
      |  mientras Expr  { if($2.tipo != LOGICO) errorSemantico(ERR_EXP_LOG, $1.nlin, $1.ncol, $1.lexema); }
                         hacer Instr       { etiq1 = nuevaEtiqueta();
                                             etiq2 = nuevaEtiqueta();
                                             $$.cod =    'L'   + std::to_string(etiq1)       + "\n";  // Etiq inicio
                                             $$.cod +=   $2.cod;                                      // Ejecuta Expr
                                             $$.cod +=   "mov "  + std::to_string($2.dir)   + " A\n"; // Carga resultado de Expr
                                             $$.cod +=   "jz L"  + std::to_string(etiq2)    + '\n';   // Si Expr FALSE, salta a final
                                             $$.cod +=   $5.cod;                                      // Ejecuta Instr
                                             $$.cod +=   "jmp L" + std::to_string(etiq1)    + '\n';   // Salta a inicio
                                             $$.cod +=   'L'     + std::to_string(etiq2)    + "\n";   // Etiq final
                                          }
      |  repetir Instr hasta Expr         {  if($4.tipo != LOGICO) errorSemantico(ERR_EXP_LOG, $3.nlin, $3.ncol, $3.lexema);
                                             etiq1 = nuevaEtiqueta();
                                             $$.cod =    'L'      + std::to_string(etiq1)    + "\n";     // Etiq inicio
                                             $$.cod +=   $2.cod;                                         // Ejecutar Instr
                                             $$.cod +=   $4.cod;                                         // Ejecutar Expr
                                             $$.cod +=   "mov "   + std::to_string($4.dir)   + " A\n";   // Carga resultado de Expr
                                             $$.cod +=   "jz L"   + std::to_string(etiq1)    + '\n';     // Si Expr FALSE, salta a inicio
                                          }
      |  Ref opasig Expr                  {  // Puedo asignar real a una variable entera? NO
                                             if(esArray($1.tipo)) errorSemantico(ERR_FALTAN, $1.nlin, $1.ncol, $1.lexema);
                                             if($1.tipo != $3.tipo)
                                             {
                                                if($3.tipo == LOGICO)   // No se puede asignar valor lógico a variables enteras o reales
                                                {
                                                   if($1.tipo == ENTERO) errorSemantico(ERR_EXDER_ENT, $2.nlin, $2.ncol, $2.lexema);
                                                   if($1.tipo == REAL) errorSemantico(ERR_EXDER_RE, $2.nlin, $2.ncol, $2.lexema);
                                                }
                                                // No se puede asignar valores enteros o reales a variable lógica
                                                if($1.tipo == LOGICO) errorSemantico(ERR_EXDER_LOG, $2.nlin, $2.ncol, $2.lexema);

                                                // No se puede asignar valor real a variable entera
                                                if($1.tipo == ENTERO) errorSemantico(ERR_EXDER_ENT, $2.nlin, $2.ncol, $2.lexema);
                                                
                                                tmp = nuevaTemp();
                                                // Variable real -> Expr entero -> ITOR
                                                s1 =  "mov "   + std::to_string($3.dir)   + " A\n";   // Carga resultado entero de Expr
                                                s1 += "itor\n";                                       // ITOR
                                                s1 += "mov A " + std::to_string(tmp)      + '\n';     // Guarda resultado de Expr en temporal
                                                s1 += "mov "   + std::to_string($1.dir)   + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string($1.dbase) + '\n';     // Añade dirección base
                                                s1 += "mov "   + std::to_string(tmp)      + " @A\n";  // Guarda resultado de Expr en Ref
                                             }
                                             else
                                             {
                                                s1 =  "mov "   + std::to_string($1.dir)   + " A\n";   // Carga saltos en array Ref
                                                s1 += "addi #" + std::to_string($1.dbase) + "\n";     // Añade dirección base
                                                s1 += "mov "   + std::to_string($3.dir)   + " @A\n";  // Guarda resultado de Expr en Ref
                                             }
                                             $$.cod = $1.cod + $3.cod + s1;
                                          }
      |  blq { tsActual = new TablaSimbolos(tsActual); } SDec fblq    {
                                                                                    tsActual = tsActual->getAmbitoAnterior(); 
                                                                                    $$.cod = $3.cod; }
      ;

ColaIf:  sino Instr  { $$.cod = $2.cod;   }
      |              { $$.cod = "";       }
      ;

Expr  :  Expr obool Econj  {  
                              $$.tipo = LOGICO; 
                              if($1.tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, $2.nlin, $2.ncol, $2.lexema);
                              if($3.tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, $2.nlin, $2.ncol, $2.lexema);

                              tmp = nuevaTemp(); $$.dir = tmp;
                              $$.cod +=   $1.cod   + $3.cod;
                              $$.cod +=   "mov "   + std::to_string($1.dir)   + " A\n";
                              $$.cod +=   "ori "   + std::to_string($3.dir)   + '\n';
                              $$.cod +=   "mov A " + std::to_string(tmp)      + '\n';
                           } 
      |  Econj             {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Econj :  Econj ybool Ecomp {  
                              $$.tipo = LOGICO; 
                              if($1.tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, $2.nlin, $2.ncol, $2.lexema);
                              if($3.tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, $2.nlin, $2.ncol, $2.lexema);

                              tmp = nuevaTemp(); $$.dir = tmp;
                              $$.cod +=   $1.cod   + $3.cod;
                              $$.cod +=   "mov "   + std::to_string($1.dir)   + " A\n";
                              $$.cod +=   "andi "  + std::to_string($3.dir)   + '\n';
                              $$.cod +=   "mov A " + std::to_string(tmp)      + '\n';
                           }
      |  Ecomp             {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Ecomp :  Esimple oprel Esimple   {  tipo1 = $1.tipo;
                                    tipo2 = $3.tipo;
                                    if($1.tipo == LOGICO) errorSemantico(ERR_EXIZQ_RE, $2.nlin, $2.ncol, $2.lexema);
                                    if($3.tipo == LOGICO) errorSemantico(ERR_EXDER_RE, $2.nlin, $2.ncol, $2.lexema);
                                    $$.tipo = LOGICO; 

                                    tmp = nuevaTemp(); $$.dir = tmp;
                                    operador = string($2.lexema);
                                    if(operador == "=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "eqli" : "eqlr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "eqlr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "eqlr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<>")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "neqi" : "neqr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "neqr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "neqr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "lssi" : "lssr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 < tipo2)
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "lssr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 > tipo1)
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   string("itor\n")+
                                                   "gtrr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == "<=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "leqi" : "leqr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 <= tipo2)
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   "itor\n" +
                                                   "leqr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 >= tipo1)
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   "itor\n" +
                                                   "geqr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == ">")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "gtri" : "gtrr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 > tipo2)
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   "itor\n" +
                                                   "gtrr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 < tipo1)
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   "itor\n" +
                                                   "lssr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }
                                    else if(operador == ">=")
                                    {
                                       if(tipo1 == tipo2)
                                       {
                                          operador = (tipo1 == ENTERO) ? "geqi" : "geqr";
                                          s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                operador + ' ' + std::to_string($3.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                       else
                                       {
                                          if(tipo1 == ENTERO)  // ITOR tipo1 (tipo1 > tipo2)
                                             s1 = "mov " + std::to_string($1.dir) + " A\n" +
                                                   "itor\n" +
                                                   "geqr " + std::to_string($3.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                          else  // ITOR tipo2 (tipo2 < tipo1)
                                             s1 = "mov " + std::to_string($3.dir) + " A\n" +
                                                   "itor\n" +
                                                   "leqr " + std::to_string($1.dir) + nextLine +
                                                   "mov A " + std::to_string(tmp) + nextLine;
                                       }
                                    }

                                    $$.cod = $1.cod + $3.cod + s1;
                                 }
      |  Esimple                 {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Esimple  :  Esimple opas Term {   
                                 tipo1 = $1.tipo;
                                 tipo2 = $3.tipo;
                                 if(tipo1 == LOGICO) errorSemantico(ERR_EXIZQ_RE, $2.nlin, $2.ncol, $2.lexema);
                                 if(tipo2 == LOGICO) errorSemantico(ERR_EXDER_RE, $2.nlin, $2.ncol, $2.lexema);
                                 // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                                 tmp = nuevaTemp(); $$.dir = tmp;
                                 operador = string($2.lexema);

                                 if(tipo1 == tipo2)
                                 {  // No hace falta convertir tipos
                                    if(tipo1 == ENTERO)
                                       operadorTrad = (operador == "+") ? "addi" : "subi";
                                    else
                                       operadorTrad = (operador == "+") ? "addr" : "subr";
                                    
                                    s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                          operadorTrad + ' ' + std::to_string($3.dir) + nextLine +
                                          "mov A " + std::to_string(tmp) + nextLine;
                                    
                                    $$.tipo = tipo1;  // Tipo el que hayan sido ambos
                                 }
                                 else
                                 {
                                    operadorTrad = (operador == "+") ? "addr" : "subr";

                                    if(tipo1 == ENTERO)  // Entero opas Real
                                    {
                                       s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                             string("itor\n")+
                                             operadorTrad + ' ' + std::to_string($3.dir) + nextLine +
                                             "mov A " + std::to_string(tmp) + nextLine;
                                    }
                                    else  // Real opas Entero
                                    {
                                       tmpcnv = nuevaTemp();
                                       s2 = "mov " + std::to_string($3.dir) + " A\n" +  //Carga Entero
                                             string("itor\n")+                 // itor
                                             "mov A " + std::to_string(tmpcnv) + nextLine +   // Guarda el convertido
                                             "mov " + std::to_string($1.dir) + " A\n" +                   // Carga Real
                                             operadorTrad + ' ' + std::to_string(tmpcnv) + nextLine +  // Opera con Entero convertido
                                             "mov A " + std::to_string(tmp) + nextLine;             // Guarda resultado
                                    }

                                    $$.tipo = REAL;   // Tipo será real por itor
                                 }

                                 $$.cod = $1.cod + $3.cod + s2;
                              }
         |  Term              {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
         |  opas Term         {  
                                 tipo1 = $2.tipo;
                                 if(tipo1 == LOGICO) errorSemantico(ERR_EXDER_RE, $1.nlin, $1.ncol, $1.lexema);
                                 tmp = nuevaTemp(); $$.dir = tmp;

                                 if(tipo1 == ENTERO)
                                 {
                                    operadorTrad = (operador == "+") ? "addi" : "subi";
                                    s2 = "mov #0 A\n" +     // Carga 0
                                       operadorTrad + ' ' + std::to_string($2.dir) + nextLine +  // Opera con Term
                                       "mov A " + std::to_string(tmp) + nextLine;                // Guarda resultado
                                 }
                                 else
                                 {
                                    operadorTrad = (operador == "+") ? "addr" : "subr";
                                    s2 = "mov $0 A\n" +     // Carga 0
                                       operadorTrad + ' ' + std::to_string($2.dir) + nextLine +  // Opera con Term
                                       "mov A " + std::to_string(tmp) + nextLine;                // Guarda resultado
                                 }
                                 
                                 
                                 
                                 $$.tipo = tipo1;
                                 $$.cod = $2.cod + s2;
                              }
         ;

Term  :  Term opmd Factor  {
                              tipo1 = $1.tipo;
                              tipo2 = $3.tipo;
                              if(tipo1 == LOGICO) errorSemantico(ERR_EXIZQ_RE, $2.nlin, $2.ncol, $2.lexema);
                              if(tipo2 == LOGICO) errorSemantico(ERR_EXDER_RE, $2.nlin, $2.ncol, $2.lexema);
                              // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                              tmp = nuevaTemp(); $$.dir = tmp;
                              operador = string($2.lexema);

                              if(tipo1 == tipo2)
                              {  // No hace falta convertir tipos
                                 if(tipo1 == ENTERO)
                                    operadorTrad = (operador == "*") ? "muli" : "divi";
                                 else
                                    operadorTrad = (operador == "*") ? "mulr" : "divr";
                                 
                                 s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                       operadorTrad + ' ' + std::to_string($3.dir) + nextLine +
                                       "mov A " + std::to_string(tmp) + nextLine;
                                 
                                 $$.tipo = tipo1;  // Tipo el que hayan sido ambos
                              }
                              else
                              {
                                 operadorTrad = (operador == "*") ? "mulr" : "divr";

                                 if(tipo1 == ENTERO)  // Entero opmd Real
                                 {
                                    s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                          string("itor\n")+
                                          operadorTrad + ' ' + std::to_string($3.dir) + nextLine +
                                          "mov A " + std::to_string(tmp) + nextLine;
                                 }
                                 else  // Real opmd Entero
                                 {
                                    tmpcnv = nuevaTemp();
                                    s2 = "mov " + std::to_string($3.dir) + " A\n" +  //Carga Entero
                                          string("itor\n")+                 // itor
                                          "mov A " + std::to_string(tmpcnv) + nextLine +   // Guarda el convertido
                                          "mov " + std::to_string($1.dir) + " A\n" +                   // Carga Real
                                          operadorTrad + ' ' + std::to_string(tmpcnv) + nextLine +  // Opera con Entero convertido
                                          "mov A " + std::to_string(tmp) + nextLine;             // Guarda resultado
                                 }

                                 $$.tipo = REAL;   // Tipo será real por itor
                              }

                              $$.cod = $1.cod + $3.cod + s2;
                           }
      |  Factor            {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Factor:  Ref            {  
                           if(esArray($1.tipo)) errorSemantico(ERR_FALTAN, $1.nlin, $1.ncol, $1.lexema);
                           $$.tipo = $1.tipo;
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = $1.cod + 
                                    "mov " + std::to_string($1.dir) + " A\n"+
                                    string("addi #") + std::to_string($1.dbase) + nextLine +
                                    "mov @A " + std::to_string(tmp) + nextLine;
                        }
      |  nentero        {  
                           $$.tipo = ENTERO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #" + string($1.lexema) + ' ' + std::to_string(tmp) + nextLine; 
                        }
      |  nreal          {  
                           $$.tipo = REAL; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov $" + string($1.lexema) + ' ' + std::to_string(tmp) + nextLine; 
                        }
      |  pari Expr pard {  $$.tipo = $2.tipo; $$.cod = $2.cod; $$.dir = $2.dir; }
      |  nobool Factor  {
                           tipo1 = $2.tipo;
                           if(tipo1 != LOGICO) errorSemantico(ERR_EXDER_LOG, $1.nlin, $1.ncol, $1.lexema);
                           $$.tipo = tipo1; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = $2.cod + 
                                    "mov " + std::to_string($2.dir) + "A\n" +
                                    "noti\n" +
                                    "mov A " + std::to_string(tmp) + nextLine;
                        }
      |  cierto         {
                           $$.tipo = LOGICO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #1 " + std::to_string(tmp) + nextLine; 
                        }
      |  falso          {
                           $$.tipo = LOGICO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #0 " + std::to_string(tmp) + nextLine; 
                        }
      ;

Ref   :  id                      {  
                                    simbolo = tsActual->searchSymb($1.lexema);
                                    if(simbolo == NULL) 
                                       errorSemantico(ERR_NODECL, $1.nlin, $1.ncol, $1.lexema);
                                    tmp = nuevaTemp(); $$.dir = tmp;
                                    $$.cod = "mov #0 " + std::to_string(tmp) + nextLine;
                                    // $$.cod = "mov #0 " + std::to_string(tmp) + nextLine;
                                    $$.tipo = simbolo->tipo;
                                    $$.dbase = simbolo->dir; 
                                    $$.esArray = esArray(simbolo->tipo);
                                    $$.nlin = $1.nlin; $$.ncol = $1.ncol;
                                 }
      |  Ref cori { if(!esArray($1.tipo))
                     {
                        if($1.esArray) errorSemantico(ERR_SOBRAN, $2.nlin, $2.ncol, $2.lexema);
                        else           errorSemantico(ERR_SOBRAN, $1.nlin, $1.ncol, $1.lexema);
                     }  
                  }  Esimple cord   {  
                                       if($4.tipo != ENTERO) errorSemantico(ERR_INDICE_ENTERO, $4.nlin, $4.ncol, $4.lexema); 
                                       $$.tipo = tipoBase($1.tipo);
                                       $$.dbase = $1.dbase;
                                       $$.esArray = $1.esArray;
                                       tmp = nuevaTemp(); $$.dir = tmp;
                                       $$.cod = $1.cod + $4.cod + 
                                                "mov " + std::to_string($1.dir) + " A\n" +
                                                "muli #" + std::to_string(tamanyoTipo($1.tipo)) + nextLine +
                                                "addi " + std::to_string($4.dir) + nextLine +
                                                "mov A " + std::to_string(tmp) + nextLine;
                                       $$.lexema = $5.lexema; $$.nlin = $5.nlin; $$.ncol = $5.ncol;   /* Por si luego tengo que lanzar error */
                                    }
      ;

%%
int nuevaTemp(void)
{
   if (ctemp > MAX_DIR_TEMP)
      errorSemantico (ERR_MAXTMP, 0, 0, NULL);
   
   int tempReservado = ctemp;
   ++ctemp;
   
   return tempReservado;
}

int nuevaVar(string nombreVar, int tamVar)
{
   if (cvar + tamVar - 1 > MAX_DIR_VAR)
      errorSemantico (ERR_NOCABE, 0, 0, nombreVar.c_str());
   
   int tempReservado = cvar;
   cvar += tamVar;
   
   return tempReservado;
}


int nuevaEtiqueta()
{
   cetiq++;
   
   return cetiq;
}

void errorSemantico(int nerror,int nlin,int ncol,const char *s)
{
   fprintf(stderr,"Error semantico (%d,%d): ", nlin,ncol);
   switch(nerror) {
         case ERR_YADECL:        fprintf(stderr,"variable '%s' ya declarada\n",s);
            break;
         case ERR_NODECL:        fprintf(stderr,"variable '%s' no declarada\n",s);
            break;
         case ERR_DIM:           fprintf(stderr,"la dimension debe ser mayor que cero\n");
            break;
         case ERR_FALTAN:        fprintf(stderr,"faltan indices\n");
            break;
         case ERR_SOBRAN:        fprintf(stderr,"sobran indices\n");
            break;
         case ERR_INDICE_ENTERO: fprintf(stderr,"la expresion entre corchetes debe ser de tipo entero\n");
            break;
         case ERR_EXP_LOG:       fprintf(stderr,"la expresion debe ser de tipo logico\n");
            break;
         case ERR_EXDER_LOG:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo logico\n",s);
            break;
         case ERR_EXDER_ENT:     fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo entero\n",s);
            break;
         case ERR_EXDER_RE:      fprintf(stderr,"la expresion a la derecha de '%s' debe ser de tipo real o entero\n",s);
            break;        
         case ERR_EXIZQ_LOG:     fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo logico\n",s);
            break;       
         case ERR_EXIZQ_RE:      fprintf(stderr,"la expresion a la izquierda de '%s' debe ser de tipo real o entero\n",s);
            break;       
         case ERR_NOCABE:        fprintf(stderr,"la variable '%s' ya no cabe en memoria\n",s);
            break;
         case ERR_MAXTMP:        fprintf(stderr,"no hay espacio para variables temporales\n");
            break;
   }
   exit(-1);
}

void msgError(int nerror,int nlin,int ncol,const char *s)
{
    switch (nerror) {
         case ERRLEXICO:   fprintf(stderr,"Error lexico (%d,%d): caracter '%s' incorrecto\n",nlin,ncol,s);
            break;
         case ERRSINT:     fprintf(stderr,"Error sintactico (%d,%d): en '%s'\n",nlin,ncol,s);
            break;
         case ERREOF:      fprintf(stderr,"Error sintactico: fin de fichero inesperado\n");
            break;
     }

     exit(1);
}

int yyerror(char *s)
{
    if (findefichero) 
    {
       msgError(ERREOF,0,0,"");
    }
    else
    {  
       msgError(ERRSINT,nlin,ncol-strlen(yytext),yytext);
    }
    exit(-1);
    return -1;
}

int main(int argc,char *argv[])
{
    FILE *fent;
    if (argc==2)
    {
        fent = fopen(argv[1],"rt");
        if (fent)
        {
            yyin = fent;
            yyparse();
            fclose(fent);
        }
        else
            fprintf(stderr,"No puedo abrir el fichero\n");
    }
    else
        fprintf(stderr,"Uso: ejemplo <nombre de fichero>\n");
}
