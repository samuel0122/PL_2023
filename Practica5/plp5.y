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

bool esArray(uint tipo) { return tt->tipos[tipo].clase == TablaTipos::ARRAY; }
uint tipoBase(uint tipo)  { return tt->tipos[tipo].tipoBase; }
uint tamanyoTipo(uint tipo)  { return tt->tipos[tipo].tamanyo; }

int tmp, tmpcnv;
int ctemp {INIT_DIR_TEMP};
int nuevaTemp();

int cvar {INIT_DIR_VAR};
int nuevaVar(string nombreVar, int tamVar);

uint tam, dir, tipo;
%}

%%


S     : algoritmo dospto id SDec falgoritmo  { 
                                                /* comprobar que después del programa no hay ningún token más */
                                                int tk = yylex();
                                                if (tk != 0) yyerror("");
                                                tt->imprimir();
                                                tsActual->imprimir();
                                             }
      ;


SDec  :  Dec SInstr  { $$.cod = $1.cod + $2.cod; }
      |  SInstr      { $$.cod = $1.cod; }
      ;

Dec   :  var MDVar fvar {}
      ;

MDVar :  MDVar DVar  {}
      |  DVar        {}
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
                                    $$.tipo = tt->nuevoTipoArray(numentero, $4.tipo); 
                                    $$.tam = $4.tam * numentero; }
      ;

SInstr:  SInstr { $$.nlin = ctemp; } pyc Instr  { ctemp = $2.nlin; }
      |  { $$.nlin = ctemp; } Instr             { ctemp = $1.nlin; }
      ;

Instr :  escribe Expr                     {}
      |  lee Ref                          {}
      |  si Expr entero Instr             {}
      |  si Expr entero Instr sino Instr  {}
      |  mientras Expr hacer Expr         {}
      |  repetir Instr hasta Expr         {}
      |  Ref opasig Expr                  {  
                                             // Puedo asignar real a una variable entera?
                                          }
      |  blq { tsActual = new TablaSimbolos(tsActual); } SDec fblq    {
                                                                                    tsActual = tsActual->getAmbitoAnterior(); 
                                                                                    $$.cod = $3.cod; }
      ;

Expr  :  Expr obool Econj  {  
                              $$.tipo = LOGICO; 
                              if($1.tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, $2.nlin, $2.ncol, $2.lexema);
                              if($3.tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, $2.nlin, $2.ncol, $2.lexema);
                              // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                              tmp = nuevaTemp(); $$.dir = tmp;
                              $$.cod = $1.cod + $3.cod + 
                                       "mov " + std::to_string($1.dir) + " A\n" +
                                       "ori " + std::to_string($3.dir) + '\n' +
                                       "mov A " + std::to_string(tmp) + '\n';
                           } 
      |  Econj             {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Econj :  Econj ybool Ecomp {  
                              $$.tipo = LOGICO; 
                              if($1.tipo != LOGICO) errorSemantico(ERR_EXIZQ_LOG, $2.nlin, $2.ncol, $2.lexema);
                              if($3.tipo != LOGICO) errorSemantico(ERR_EXDER_LOG, $2.nlin, $2.ncol, $2.lexema);
                              // TODO: operadores '||' y '&&' deben tener operandos booleanos?  (enteros)
                              tmp = nuevaTemp(); $$.dir = tmp;
                              $$.cod = $1.cod + $3.cod + 
                                       "mov " + std::to_string($1.dir) + " A\n" +
                                       "andi " + std::to_string($3.dir) + '\n' +
                                       "mov A " + std::to_string(tmp) + '\n';
                           }
      |  Ecomp             {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Ecomp :  Esimple oprel Esimple   {  
                                    // TODO 
                                    tmp = nuevaTemp(); $$.dir = tmp;
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
                                          operadorTrad + ' ' + std::to_string($3.dir) + '\n' +
                                          "mov A " + std::to_string(tmp) + '\n';
                                    
                                    $$.tipo = tipo1;  // Tipo el que hayan sido ambos
                                 }
                                 else
                                 {
                                    operadorTrad = (operador == "+") ? "addr" : "subr";

                                    if(tipo1 == ENTERO)  // Entero opas Real
                                    {
                                       s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                             "itor\n" +
                                             operadorTrad + ' ' + std::to_string($3.dir) + '\n' +
                                             "mov A " + std::to_string(tmp) + '\n';
                                    }
                                    else  // Real opas Entero
                                    {
                                       tmpcnv = nuevaTemp();
                                       s2 = "mov " + std::to_string($3.dir) + " A\n" +  //Carga Entero
                                             "itor\n" +                 // itor
                                             "mov A " + std::to_string(tmpcnv) + '\n' +   // Guarda el convertido
                                             "mov " + std::to_string($1.dir) + " A\n" +                   // Carga Real
                                             operadorTrad + ' ' + std::to_string(tmpcnv) + '\n' +  // Opera con Entero convertido
                                             "mov A " + std::to_string(tmp) + '\n';             // Guarda resultado
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
                                    operadorTrad = (operador == "+") ? "addi" : "subi";
                                 else
                                    operadorTrad = (operador == "+") ? "addr" : "subr";
                                 
                                 s2 = "mov #0 A\n" +     // Carga 0
                                       operadorTrad + ' ' + std::to_string($2.dir) + '\n' +  // Opera con Term
                                       "mov A " + std::to_string(tmp) + '\n';                // Guarda resultado
                                 
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
                                       operadorTrad + ' ' + std::to_string($3.dir) + '\n' +
                                       "mov A " + std::to_string(tmp) + '\n';
                                 
                                 $$.tipo = tipo1;  // Tipo el que hayan sido ambos
                              }
                              else
                              {
                                 operadorTrad = (operador == "*") ? "mulr" : "divr";

                                 if(tipo1 == ENTERO)  // Entero opmd Real
                                 {
                                    s2 = "mov " + std::to_string($1.dir) + " A\n" +
                                          "itor\n" +
                                          operadorTrad + ' ' + std::to_string($3.dir) + '\n' +
                                          "mov A " + std::to_string(tmp) + '\n';
                                 }
                                 else  // Real opmd Entero
                                 {
                                    tmpcnv = nuevaTemp();
                                    s2 = "mov " + std::to_string($3.dir) + " A\n" +  //Carga Entero
                                          "itor\n" +                 // itor
                                          "mov A " + std::to_string(tmpcnv) + '\n' +   // Guarda el convertido
                                          "mov " + std::to_string($1.dir) + " A\n" +                   // Carga Real
                                          operadorTrad + ' ' + std::to_string(tmpcnv) + '\n' +  // Opera con Entero convertido
                                          "mov A " + std::to_string(tmp) + '\n';             // Guarda resultado
                                 }

                                 $$.tipo = REAL;   // Tipo será real por itor
                              }

                              $$.cod = $1.cod + $3.cod + s2;
                           }
      |  Factor            {  $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; }
      ;

Factor:  Ref            {  
                           if(esArray($1.tipo)) errorSemantico(ERR_FALTAN, $1.nlin, $1.ncol, $1.lexema);
                           $$.tipo = $1.tipo; $$.cod = $1.cod; $$.dir = $1.dir; 
                        }
      |  nentero        {  
                           $$.tipo = ENTERO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #" + string($1.lexema) + ' ' + std::to_string(tmp) + '\n'; 
                        }
      |  nreal          {  
                           $$.tipo = REAL; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov $" + string($1.lexema) + ' ' + std::to_string(tmp) + '\n'; 
                        }
      |  pari Expr pard {  $$.tipo = $2.tipo; $$.cod = $2.cod; $$.dir = $2.dir; }
      |  nobool Factor  {
                           tipo1 = $2.tipo;
                           if(tipo1 != LOGICO) errorSemantico(ERR_EXDER_LOG, $1.nlin, $1.ncol, $1.lexema);
                           $$.tipo = tipo1; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = $2.cod + 
                                    "mov " + std::to_string($2.dir) + "A\n" +
                                    "noti" +
                                    "mov A " + std::to_string(tmp) + '\n';
                        }
      |  cierto         {
                           $$.tipo = LOGICO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #1 " + std::to_string(tmp) + '\n'; 
                        }
      |  falso          {
                           $$.tipo = LOGICO; 
                           tmp = nuevaTemp(); $$.dir = tmp;
                           $$.cod = "mov #0 " + std::to_string(tmp) + '\n'; 
                        }
      ;

Ref   :  id                      {  
                                    simbolo = tsActual->searchSymb($1.lexema);
                                    if(simbolo == NULL) 
                                       errorSemantico(ERR_NODECL, $1.nlin, $1.ncol, $1.lexema);
                                    tmp = nuevaTemp(); $$.dir = tmp;
                                    $$.cod = "mov #0 " + std::to_string(tmp);
                                    $$.tipo = simbolo->tipo;
                                    $$.dbase = simbolo->dir; 
                                 }
      |  Ref cori { if(!esArray($1.tipo)) errorSemantico(ERR_SOBRAN, $2.nlin, $2.ncol, $2.lexema); } 
               Esimple cord   {  
                                 if($4.tipo != ENTERO) errorSemantico(ERR_INDICE_ENTERO, $4.nlin, $4.ncol, $4.lexema); 
                                 $$.tipo = tipoBase($1.tipo);
                                 $$.dbase = $1.dbase;
                                 tmp = nuevaTemp(); $$.dir = tmp;
                                 $$.cod = $1.cod + $4.cod + 
                                          "mov " + std::to_string($1.dir) + " A\n" +
                                          "muli #" + std::to_string(tamanyoTipo($1.tipo)) + '\n' +
                                          "addi " + std::to_string($4.dir) + 
                                          "mov A " + std::to_string(tmp) + '\n';
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
